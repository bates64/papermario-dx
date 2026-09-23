use std::collections::HashMap;

use crate::elf::{Elf32, ElfError, STT_FUNC, STT_NOTYPE, STT_SECTION, SHN_UNDEF, R_MIPS_32, Symbol};
use crate::opcode::{
    CASE_GROUP_OPS, CASE_OPS, CLAMP_OPS, EXEC_OPS, FINALLY_FORBIDDEN_OPS, IF_OPS, Opcode,
    RANGE_IF_OPS, command_display_name, function_arg_index, integer_math_float_variant,
};
use crate::pattern::SymbolPattern;

const BYTECODE_SIZE: usize = 4;
const EVT_OP_INTERNAL_FETCH: u8 = 0x00;

const MAX_NUM_LABELS: usize = 16;
const MAX_LABEL_NAME_LEN: usize = 64;
const MAX_LOOP_DEPTH: usize = 8;
const MAX_SWITCH_DEPTH: usize = 8;

const EVT_LOCAL_VAR_CUTOFF: i32 = -20000000;
const EVT_FIXED_CUTOFF: i32 = -220000000;
const EVT_FIXED_OFFSET: i32 = 230000000;
const EVT_FIXED_END: i32 = -240000000;
const EVT_LIMIT: i32 = -270000000;
const EVT_ARG_INT_MARKER: i32 = EVT_LIMIT - 1;
const EVT_ARG_FLOAT_MARKER: i32 = EVT_LIMIT - 2;

const EVT_MEM_U8: i32 = 0;
const EVT_MEM_F32: i32 = 6;

#[derive(Debug)]
pub enum ValidateError {
    Elf(String),
    Validation(String),
}

impl std::fmt::Display for ValidateError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            ValidateError::Elf(s) => write!(f, "{s}"),
            ValidateError::Validation(s) => write!(f, "{s}"),
        }
    }
}

impl From<ElfError> for ValidateError {
    fn from(e: ElfError) -> Self {
        ValidateError::Elf(e.0)
    }
}

type VResult<T> = Result<T, ValidateError>;

fn verr(msg: impl Into<String>) -> ValidateError {
    ValidateError::Validation(msg.into())
}

#[derive(Clone, PartialEq, Eq, Hash, Debug)]
enum LabelValue {
    Number(i32),
    Str(String),
}

fn format_label(label: &LabelValue) -> String {
    match label {
        LabelValue::Number(n) => n.to_string(),
        LabelValue::Str(s) => format!("\"{s}\""),
    }
}

struct ScriptSymbol {
    symbol: Symbol,
    section_index: usize,
    source_path: Option<String>,
}

fn format_script_symbol(script: &ScriptSymbol) -> String {
    match &script.source_path {
        Some(p) => format!("{p}: {}", script.symbol.name),
        None => script.symbol.name.clone(),
    }
}

fn format_script_site(script: &ScriptSymbol, op_pos: usize, line: Option<u16>) -> String {
    let script_pos = format!("{}+0x{:X}", script.symbol.name, op_pos * 4);
    match (&script.source_path, line) {
        (Some(p), Some(l)) if l != 0 => format!("{p}:{l}: {script_pos}"),
        (Some(p), _) => format!("{p}: {script_pos}"),
        (None, Some(l)) if l != 0 => format!("{script_pos} (source line {l})"),
        (None, _) => script_pos,
    }
}

fn signed_word(data: &[u8], offset: usize) -> i32 {
    i32::from_be_bytes([data[offset], data[offset + 1], data[offset + 2], data[offset + 3]])
}

fn unsigned_word(data: &[u8], offset: usize) -> u32 {
    u32::from_be_bytes([data[offset], data[offset + 1], data[offset + 2], data[offset + 3]])
}

fn word_at(data: &[u8], word_index: usize) -> i32 {
    signed_word(data, word_index * BYTECODE_SIZE)
}

fn opcode_from_raw_cmd(raw_cmd: u32) -> u8 {
    ((raw_cmd >> 24) & 0xFF) as u8
}
fn argc_from_raw_cmd(raw_cmd: u32) -> u8 {
    ((raw_cmd >> 16) & 0xFF) as u8
}
fn line_from_raw_cmd(raw_cmd: u32) -> u16 {
    (raw_cmd & 0xFFFF) as u16
}

fn is_label_initial_byte(ch: u8) -> bool {
    ch == b'_' || ch.is_ascii_alphabetic()
}
fn is_label_byte(ch: u8) -> bool {
    is_label_initial_byte(ch) || ch.is_ascii_digit()
}

fn read_label_name(data: &[u8], offset: i64) -> Option<String> {
    if offset < 0 || offset as usize >= data.len() {
        return None;
    }
    let offset = offset as usize;
    if !is_label_initial_byte(data[offset]) {
        return None;
    }
    let end = data.len().min(offset + MAX_LABEL_NAME_LEN);
    let mut chars = vec![data[offset]];
    for &ch in &data[offset + 1..end] {
        if ch == 0 {
            return String::from_utf8(chars).ok();
        }
        if !is_label_byte(ch) {
            return None;
        }
        chars.push(ch);
    }
    None
}

fn is_fixed_literal(value: i32) -> bool {
    (EVT_FIXED_END..=EVT_FIXED_CUTOFF).contains(&value)
}
fn is_plain_int_literal(value: i32) -> bool {
    value > EVT_LOCAL_VAR_CUTOFF
}
fn is_encoded_evt_expression(value: i32) -> bool {
    value > EVT_LIMIT && value <= EVT_LOCAL_VAR_CUTOFF
}
fn literal_as_float(value: i32) -> Option<f64> {
    if is_fixed_literal(value) {
        Some((value as f64 + EVT_FIXED_OFFSET as f64) / 1024.0)
    } else if is_plain_int_literal(value) {
        Some(value as f64)
    } else {
        None
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum BlockKind {
    If,
    Else,
    Loop,
    Lerp,
    Switch,
    Thread,
    ChildThread,
}

impl BlockKind {
    fn label(self) -> &'static str {
        match self {
            BlockKind::If => "if",
            BlockKind::Else => "else",
            BlockKind::Loop => "loop",
            BlockKind::Lerp => "lerp",
            BlockKind::Switch => "switch",
            BlockKind::Thread => "thread",
            BlockKind::ChildThread => "child_thread",
        }
    }
}

struct Block {
    kind: BlockKind,
    start_pos: usize,
}

#[derive(Clone, Copy)]
struct CaseGroup {
    opcode: Opcode,
    start_pos: usize,
}

#[derive(Clone, Copy, PartialEq, Eq)]
enum ScopeKind {
    Root,
    Thread,
    ChildThread,
}

struct LabelScope {
    #[allow(dead_code)]
    kind: ScopeKind,
    stack_base: usize,
    labels: HashMap<LabelValue, usize>,
    case_group_stack: Vec<Option<CaseGroup>>,
    finally_pos: Option<usize>,
}

struct GotoRef {
    op_pos: usize,
    label: LabelValue,
    scope_index: usize,
}

struct ScriptWalkContext<'a> {
    script: &'a ScriptSymbol,
    stack: Vec<Block>,
    gotos: Vec<GotoRef>,
    /// Every label scope ever entered, kept permanently (mirrors Python
    /// holding a live reference to the scope object even after the
    /// thread/child_thread block that owned it closes): a Goto's target
    /// scope may still gain Labels right up until that block ends, and
    /// the final Goto/Label check happens once, after the whole script
    /// has been walked.
    all_scopes: Vec<LabelScope>,
    /// Indices into all_scopes; last is the active scope.
    scope_stack: Vec<usize>,
    current_line: Option<u16>,
}

impl<'a> ScriptWalkContext<'a> {
    fn new(script: &'a ScriptSymbol) -> Self {
        let root = LabelScope {
            kind: ScopeKind::Root,
            stack_base: 0,
            labels: HashMap::new(),
            case_group_stack: Vec::new(),
            finally_pos: None,
        };
        ScriptWalkContext {
            script,
            stack: Vec::new(),
            gotos: Vec::new(),
            all_scopes: vec![root],
            scope_stack: vec![0],
            current_line: None,
        }
    }

    fn error_at(&self, op_pos: usize, message: impl AsRef<str>) -> ValidateError {
        verr(format!(
            "{}: {}",
            format_script_site(self.script, op_pos, self.current_line),
            message.as_ref()
        ))
    }

    fn push(&mut self, kind: BlockKind, op_pos: usize) {
        self.stack.push(Block { kind, start_pos: op_pos });
    }
    fn pop(&mut self) -> Block {
        self.stack.pop().unwrap()
    }
    fn top_is(&self, kind: BlockKind) -> bool {
        matches!(self.stack.last(), Some(b) if b.kind == kind)
    }
    fn top_is_any(&self, kinds: &[BlockKind]) -> bool {
        matches!(self.stack.last(), Some(b) if kinds.contains(&b.kind))
    }

    fn current_scope_idx(&self) -> usize {
        *self.scope_stack.last().unwrap()
    }
    fn current_scope(&self) -> &LabelScope {
        &self.all_scopes[self.current_scope_idx()]
    }
    fn current_scope_mut(&mut self) -> &mut LabelScope {
        let idx = self.current_scope_idx();
        &mut self.all_scopes[idx]
    }

    fn current_scope_blocks(&self) -> &[Block] {
        &self.stack[self.current_scope().stack_base..]
    }
    fn contains(&self, kind: BlockKind) -> bool {
        self.current_scope_blocks().iter().any(|b| b.kind == kind)
    }
    fn scope_is_at_top_level(&self) -> bool {
        self.stack.len() == self.current_scope().stack_base
    }

    fn enter_finally(&mut self, op_pos: usize) -> VResult<()> {
        if let Some(prev) = self.current_scope().finally_pos {
            return Err(self.error_at(
                op_pos,
                format!("duplicate Finally in scope; previous Finally at +0x{:X}", prev * 4),
            ));
        }
        if !self.scope_is_at_top_level() {
            return Err(self.error_at(op_pos, "Finally must be top-level in its script or thread scope"));
        }
        self.current_scope_mut().finally_pos = Some(op_pos);
        Ok(())
    }

    fn check_finally_command_allowed(&self, op_pos: usize, opcode: Opcode) -> VResult<()> {
        let finally_pos = self.current_scope().finally_pos;
        if finally_pos.is_none() || opcode == Opcode::EVT_OP_FINALLY {
            return Ok(());
        }
        if opcode == Opcode::EVT_OP_RETURN {
            return Err(self.error_at(op_pos, "Return is not allowed inside Finally; use the terminator command"));
        }
        if FINALLY_FORBIDDEN_OPS.contains(&opcode) {
            return Err(self.error_at(op_pos, format!("{} is not allowed inside Finally", command_display_name(opcode))));
        }
        Ok(())
    }

    fn enter_if(&mut self, op_pos: usize) {
        self.push(BlockKind::If, op_pos);
    }
    fn enter_else(&mut self, op_pos: usize) -> VResult<()> {
        if !self.top_is(BlockKind::If) {
            return Err(self.error_at(op_pos, "Else without matching If"));
        }
        let start_pos = self.stack.last().unwrap().start_pos;
        *self.stack.last_mut().unwrap() = Block { kind: BlockKind::Else, start_pos };
        Ok(())
    }
    fn exit_if(&mut self, op_pos: usize) -> VResult<()> {
        if !self.top_is_any(&[BlockKind::If, BlockKind::Else]) {
            return Err(self.error_at(op_pos, "EndIf without matching If"));
        }
        self.pop();
        Ok(())
    }

    fn enter_loop_like(&mut self, op_pos: usize, kind: BlockKind, command: &str) -> VResult<()> {
        let loop_depth = self
            .current_scope_blocks()
            .iter()
            .filter(|b| matches!(b.kind, BlockKind::Loop | BlockKind::Lerp))
            .count()
            + 1;
        if loop_depth > MAX_LOOP_DEPTH {
            return Err(self.error_at(
                op_pos,
                format!("{command} nesting depth {loop_depth} exceeds runtime limit of {MAX_LOOP_DEPTH}"),
            ));
        }
        self.push(kind, op_pos);
        Ok(())
    }
    fn enter_loop(&mut self, op_pos: usize) -> VResult<()> {
        self.enter_loop_like(op_pos, BlockKind::Loop, "Loop")
    }
    fn exit_loop(&mut self, op_pos: usize) -> VResult<()> {
        if !self.top_is(BlockKind::Loop) {
            return Err(self.error_at(op_pos, "EndLoop without matching Loop"));
        }
        self.pop();
        Ok(())
    }
    fn enter_lerp(&mut self, op_pos: usize) -> VResult<()> {
        if self.contains(BlockKind::Lerp) {
            return Err(self.error_at(op_pos, "nested Lerp is not allowed"));
        }
        self.enter_loop_like(op_pos, BlockKind::Lerp, "Lerp")
    }
    fn exit_lerp(&mut self, op_pos: usize) -> VResult<()> {
        if !self.top_is(BlockKind::Lerp) {
            return Err(self.error_at(op_pos, "EndLerp without matching Lerp"));
        }
        self.pop();
        Ok(())
    }

    fn nearest_loop_kind(&self) -> Option<BlockKind> {
        self.current_scope_blocks()
            .iter()
            .rev()
            .find(|b| matches!(b.kind, BlockKind::Loop | BlockKind::Lerp))
            .map(|b| b.kind)
    }
    fn check_break_loop(&self, op_pos: usize) -> VResult<()> {
        if self.nearest_loop_kind().is_none() {
            return Err(self.error_at(op_pos, "BreakLoop outside Loop or Lerp"));
        }
        Ok(())
    }
    fn check_continue_loop(&self, op_pos: usize) -> VResult<()> {
        match self.nearest_loop_kind() {
            None => Err(self.error_at(op_pos, "ContinueLoop outside Loop")),
            Some(BlockKind::Lerp) => Err(self.error_at(op_pos, "ContinueLoop is not allowed inside Lerp")),
            _ => Ok(()),
        }
    }
    fn check_retry_loop(&self, op_pos: usize) -> VResult<()> {
        match self.nearest_loop_kind() {
            None => Err(self.error_at(op_pos, "RetryLoop outside Loop")),
            Some(BlockKind::Lerp) => Err(self.error_at(op_pos, "RetryLoop is not allowed inside Lerp")),
            _ => Ok(()),
        }
    }

    fn enter_switch(&mut self, op_pos: usize) -> VResult<()> {
        let switch_depth = self.current_scope_blocks().iter().filter(|b| b.kind == BlockKind::Switch).count() + 1;
        if switch_depth > MAX_SWITCH_DEPTH {
            return Err(self.error_at(
                op_pos,
                format!("Switch nesting depth {switch_depth} exceeds runtime limit of {MAX_SWITCH_DEPTH}"),
            ));
        }
        self.push(BlockKind::Switch, op_pos);
        self.current_scope_mut().case_group_stack.push(None);
        Ok(())
    }
    fn exit_switch(&mut self, op_pos: usize) -> VResult<()> {
        if !self.top_is(BlockKind::Switch) {
            return Err(self.error_at(op_pos, "EndSwitch without matching Switch"));
        }
        self.check_no_open_case_group(op_pos, "EndSwitch")?;
        self.pop();
        self.current_scope_mut().case_group_stack.pop();
        Ok(())
    }
    fn check_inside_switch(&self, op_pos: usize, name: &str) -> VResult<()> {
        if !self.contains(BlockKind::Switch) {
            return Err(self.error_at(op_pos, format!("{name} outside Switch")));
        }
        Ok(())
    }
    fn active_case_group(&self) -> Option<CaseGroup> {
        *self.current_scope().case_group_stack.last()?
    }
    fn check_no_open_case_group(&self, op_pos: usize, name: &str) -> VResult<()> {
        if let Some(group) = self.active_case_group() {
            return Err(self.error_at(
                op_pos,
                format!(
                    "{name} reached before EndCaseGroup for {} group opened at +0x{:X}",
                    group.opcode.name(),
                    group.start_pos * 4
                ),
            ));
        }
        Ok(())
    }
    fn enter_case(&mut self, op_pos: usize, opcode: Opcode) -> VResult<()> {
        self.check_inside_switch(op_pos, opcode.name())?;
        if CASE_GROUP_OPS.contains(&opcode) {
            match self.active_case_group() {
                None => {
                    let last = self.current_scope_mut().case_group_stack.last_mut().unwrap();
                    *last = Some(CaseGroup { opcode, start_pos: op_pos });
                }
                Some(group) if group.opcode != opcode => {
                    return Err(self.error_at(
                        op_pos,
                        format!(
                            "{} cannot continue {} group opened at +0x{:X}",
                            opcode.name(),
                            group.opcode.name(),
                            group.start_pos * 4
                        ),
                    ));
                }
                _ => {}
            }
        } else {
            self.check_no_open_case_group(op_pos, opcode.name())?;
        }
        Ok(())
    }
    fn end_case_group(&mut self, op_pos: usize) -> VResult<()> {
        self.check_inside_switch(op_pos, "EVT_OP_END_CASE_GROUP")?;
        if self.active_case_group().is_none() {
            return Err(self.error_at(op_pos, "EndCaseGroup without active CaseOrEq/CaseAndEq group"));
        }
        let last = self.current_scope_mut().case_group_stack.last_mut().unwrap();
        *last = None;
        Ok(())
    }

    fn enter_thread(&mut self, op_pos: usize) {
        self.push(BlockKind::Thread, op_pos);
        self.all_scopes.push(LabelScope {
            kind: ScopeKind::Thread,
            stack_base: self.stack.len(),
            labels: HashMap::new(),
            case_group_stack: Vec::new(),
            finally_pos: None,
        });
        self.scope_stack.push(self.all_scopes.len() - 1);
    }
    fn exit_thread(&mut self, op_pos: usize) -> VResult<()> {
        if !self.top_is(BlockKind::Thread) {
            return Err(self.error_at(op_pos, "EndThread without matching Thread"));
        }
        self.pop();
        self.scope_stack.pop();
        Ok(())
    }
    fn enter_child_thread(&mut self, op_pos: usize) {
        self.push(BlockKind::ChildThread, op_pos);
        self.all_scopes.push(LabelScope {
            kind: ScopeKind::ChildThread,
            stack_base: self.stack.len(),
            labels: HashMap::new(),
            case_group_stack: Vec::new(),
            finally_pos: None,
        });
        self.scope_stack.push(self.all_scopes.len() - 1);
    }
    fn exit_child_thread(&mut self, op_pos: usize) -> VResult<()> {
        if !self.top_is(BlockKind::ChildThread) {
            return Err(self.error_at(op_pos, "EndChildThread without matching ChildThread"));
        }
        self.pop();
        self.scope_stack.pop();
        Ok(())
    }

    fn define_label(&mut self, op_pos: usize, label: LabelValue) -> VResult<()> {
        let prev = self.current_scope().labels.get(&label).copied();
        if let Some(prev) = prev {
            return Err(self.error_at(
                op_pos,
                format!("duplicate Label({}) previously defined at +0x{:X}", format_label(&label), prev * 4),
            ));
        }
        self.current_scope_mut().labels.insert(label, op_pos);
        let count = self.current_scope().labels.len();
        if count > MAX_NUM_LABELS {
            return Err(self.error_at(
                op_pos,
                format!("Label count {count} exceeds runtime limit of {MAX_NUM_LABELS} in this thread scope"),
            ));
        }
        Ok(())
    }

    fn define_goto(&mut self, op_pos: usize, label: LabelValue) {
        self.gotos.push(GotoRef { op_pos, label, scope_index: self.current_scope_idx() });
    }
}

fn decode_label_value(
    elf: &Elf32,
    script: &ScriptSymbol,
    value_word_index: usize,
    raw_value: i32,
    raw_bits: u32,
    op_pos: usize,
    line: Option<u16>,
    opname: &str,
) -> VResult<LabelValue> {
    let reloc_offset = script.symbol.value + (value_word_index * BYTECODE_SIZE) as u32;
    let relocation = elf.relocation_at(script.section_index, reloc_offset).copied();

    if let Some(relocation) = relocation {
        let reloc_symbol = elf.symbol_for_relocation(&relocation)?.clone();
        if relocation.r#type != R_MIPS_32 {
            return Err(verr(format!(
                "{}: {opname} uses unsupported relocation type {}",
                format_script_site(script, op_pos, line),
                relocation.r#type
            )));
        }
        if reloc_symbol.shndx == SHN_UNDEF {
            return Err(verr(format!(
                "{}: {opname} uses unresolved string label relocation",
                format_script_site(script, op_pos, line)
            )));
        }
        if reloc_symbol.shndx as usize >= elf.sections.len() {
            return Err(ValidateError::Elf(format!(
                "{}: invalid section index {}",
                reloc_symbol.name, reloc_symbol.shndx
            )));
        }

        let target_data = elf.section_data(reloc_symbol.shndx as usize);
        let label_name = read_label_name(target_data, reloc_symbol.value as i64 + raw_bits as i64);
        return match label_name {
            Some(name) => Ok(LabelValue::Str(name)),
            None => Err(verr(format!(
                "{}: {opname} does not point to a valid label string",
                format_script_site(script, op_pos, line)
            ))),
        };
    }

    if raw_value > EVT_LOCAL_VAR_CUTOFF {
        return Ok(LabelValue::Number(raw_value));
    }

    if raw_value <= EVT_LIMIT {
        return Err(verr(format!(
            "{}: {opname} uses raw pointer-like value 0x{raw_bits:08X}",
            format_script_site(script, op_pos, line)
        )));
    }

    Err(verr(format!(
        "{}: {opname} value {raw_value} is not a constant label",
        format_script_site(script, op_pos, line)
    )))
}

fn validate_argc(script: &ScriptSymbol, op_pos: usize, opcode: Opcode, argc: u8, line: Option<u16>) -> VResult<()> {
    if opcode == Opcode::EVT_OP_CALL {
        if argc < 1 {
            return Err(verr(format!(
                "{}: EVT_OP_CALL has no function argument",
                format_script_site(script, op_pos, line)
            )));
        }
        return Ok(());
    }

    if !opcode.is_variadic() {
        if argc != opcode.argc_min() {
            return Err(verr(format!(
                "{}: {} has argc {argc}, expected {}",
                format_script_site(script, op_pos, line),
                opcode.name(),
                opcode.argc_min()
            )));
        }
        return Ok(());
    }

    if argc < opcode.argc_min() {
        return Err(verr(format!(
            "{}: {} has argc {argc}, expected at least {}",
            format_script_site(script, op_pos, line),
            opcode.name(),
            opcode.argc_min()
        )));
    }
    if argc > opcode.argc_max() {
        return Err(verr(format!(
            "{}: {} has argc {argc}, expected at most {}",
            format_script_site(script, op_pos, line),
            opcode.name(),
            opcode.argc_max()
        )));
    }
    Ok(())
}

fn validate_exec_arg_stream(
    script: &ScriptSymbol,
    op_pos: usize,
    opcode: Opcode,
    args: &[i32],
    line: Option<u16>,
) -> VResult<()> {
    if !EXEC_OPS.contains(&opcode) {
        return Ok(());
    }
    let mut i = opcode.argc_min() as usize;
    while i < args.len() {
        let marker_name = match args[i] {
            v if v == EVT_ARG_INT_MARKER => Some("ARG_INT"),
            v if v == EVT_ARG_FLOAT_MARKER => Some("ARG_FLOAT"),
            _ => None,
        };
        let Some(marker_name) = marker_name else {
            i += 1;
            continue;
        };
        if i + 1 >= args.len() {
            return Err(verr(format!(
                "{}: {} {marker_name} marker at arg {i} has no value",
                format_script_site(script, op_pos, line),
                opcode.name()
            )));
        }
        i += 2;
    }
    Ok(())
}

fn validate_range_bound_types(
    script: &ScriptSymbol,
    op_pos: usize,
    opcode: Opcode,
    args: &[i32],
    line: Option<u16>,
) -> VResult<()> {
    if !RANGE_IF_OPS.contains(&opcode) {
        return Ok(());
    }
    let min_value = args[1];
    let max_value = args[2];
    let min_is_float = is_fixed_literal(min_value);
    let max_is_float = is_fixed_literal(max_value);
    if min_is_float == max_is_float {
        return Ok(());
    }

    let min_is_dynamic = is_encoded_evt_expression(min_value) && !min_is_float;
    let max_is_dynamic = is_encoded_evt_expression(max_value) && !max_is_float;
    if min_is_dynamic || max_is_dynamic {
        return Ok(());
    }

    Err(verr(format!(
        "{}: {} min/max bounds mix Float and integer literals",
        format_script_site(script, op_pos, line),
        opcode.name()
    )))
}

fn validate_integer_math_arg_types(
    script: &ScriptSymbol,
    op_pos: usize,
    opcode: Opcode,
    args: &[i32],
    line: Option<u16>,
) -> VResult<()> {
    let Some(float_variant) = integer_math_float_variant(opcode) else {
        return Ok(());
    };
    for (i, &value) in args.iter().enumerate().skip(1) {
        if is_fixed_literal(value) {
            return Err(verr(format!(
                "{}: {} arg {i} uses Float literal; use {float_variant}",
                format_script_site(script, op_pos, line),
                opcode.name()
            )));
        }
    }
    Ok(())
}

fn validate_clamp_literal_bounds(
    script: &ScriptSymbol,
    op_pos: usize,
    opcode: Opcode,
    args: &[i32],
    line: Option<u16>,
) -> VResult<()> {
    if !CLAMP_OPS.contains(&opcode) {
        return Ok(());
    }
    let (min_index, max_index) = if args.len() == 3 { (1, 2) } else { (2, 3) };
    let (Some(min_value), Some(max_value)) = (literal_as_float(args[min_index]), literal_as_float(args[max_index]))
    else {
        return Ok(());
    };
    if min_value > max_value {
        return Err(verr(format!(
            "{}: {} min bound is greater than max bound",
            format_script_site(script, op_pos, line),
            opcode.name()
        )));
    }
    Ok(())
}

fn validate_lerp_duration(
    script: &ScriptSymbol,
    op_pos: usize,
    opcode: Opcode,
    args: &[i32],
    line: Option<u16>,
) -> VResult<()> {
    if opcode != Opcode::EVT_OP_LERP {
        return Ok(());
    }
    let Some(duration) = literal_as_float(args[3]) else {
        return Ok(());
    };
    if duration < 0.0 {
        return Err(verr(format!("{}: Lerp duration must be >= 0", format_script_site(script, op_pos, line))));
    }
    Ok(())
}

fn validate_mem_type(
    elf: &Elf32,
    script: &ScriptSymbol,
    op_pos: usize,
    arg_pos: usize,
    args: &[i32],
    opcode: Opcode,
    line: Option<u16>,
) -> VResult<()> {
    if opcode != Opcode::EVT_OP_MEM_GET && opcode != Opcode::EVT_OP_MEM_SET {
        return Ok(());
    }
    let relocation = elf.relocation_at(script.section_index, script.symbol.value + (arg_pos * BYTECODE_SIZE) as u32);
    if relocation.is_some() {
        return Err(verr(format!(
            "{}: {} memory type must be a literal EVT_MEM_* value",
            format_script_site(script, op_pos, line),
            opcode.name()
        )));
    }
    let mem_type = args[0];
    if (EVT_MEM_U8..=EVT_MEM_F32).contains(&mem_type) {
        return Ok(());
    }
    if is_encoded_evt_expression(mem_type) {
        return Err(verr(format!(
            "{}: {} memory type is an EVT expression; expected a literal EVT_MEM_* value",
            format_script_site(script, op_pos, line),
            opcode.name()
        )));
    }
    Err(verr(format!(
        "{}: {} has unknown memory type {mem_type}; expected EVT_MEM_U8 through EVT_MEM_F32",
        format_script_site(script, op_pos, line),
        opcode.name()
    )))
}

fn validate_function_arg(
    elf: &Elf32,
    script: &ScriptSymbol,
    op_pos: usize,
    arg_pos: usize,
    raw_args: &[u32],
    opcode: Opcode,
    line: Option<u16>,
) -> VResult<()> {
    let Some(func_arg_index) = function_arg_index(opcode) else {
        return Ok(());
    };
    let relocation = elf
        .relocation_at(script.section_index, script.symbol.value + ((arg_pos + func_arg_index) * BYTECODE_SIZE) as u32)
        .copied();
    let Some(relocation) = relocation else {
        return Err(verr(format!(
            "{}: {} function argument at arg {func_arg_index} is not relocation-backed",
            format_script_site(script, op_pos, line),
            opcode.name()
        )));
    };
    if relocation.r#type != R_MIPS_32 {
        return Err(verr(format!(
            "{}: {} function argument uses unsupported relocation type {}",
            format_script_site(script, op_pos, line),
            opcode.name(),
            relocation.r#type
        )));
    }

    let reloc_symbol = elf.symbol_for_relocation(&relocation)?.clone();
    if reloc_symbol.r#type() == STT_SECTION {
        let target_value = reloc_symbol.value.wrapping_add(raw_args[func_arg_index]);
        for symbol in &elf.symbols {
            if symbol.r#type() != STT_FUNC || symbol.shndx != reloc_symbol.shndx {
                continue;
            }
            if symbol.value <= target_value && target_value < symbol.value + symbol.size {
                return Ok(());
            }
        }
        return Err(verr(format!(
            "{}: {} function argument points to non-function location in {}",
            format_script_site(script, op_pos, line),
            opcode.name(),
            reloc_symbol.name
        )));
    }

    if reloc_symbol.r#type() != STT_NOTYPE && reloc_symbol.r#type() != STT_FUNC {
        return Err(verr(format!(
            "{}: {} function argument points to non-function symbol {}",
            format_script_site(script, op_pos, line),
            opcode.name(),
            reloc_symbol.name
        )));
    }
    Ok(())
}

fn validate_script(elf: &Elf32, script: &ScriptSymbol, data: &[u8]) -> VResult<()> {
    if data.len() % BYTECODE_SIZE != 0 {
        return Err(verr(format!(
            "{}: size 0x{:X} is not word-aligned",
            format_script_symbol(script),
            data.len()
        )));
    }

    let words = data.len() / BYTECODE_SIZE;
    let mut read_pos = 0usize;
    let mut end_pos: Option<usize> = None;
    let mut end_op_pos: usize = 0;
    let mut end_line: Option<u16> = None;
    let mut ctx = ScriptWalkContext::new(script);
    let mut op_lines: HashMap<usize, u16> = HashMap::new();

    while read_pos < words {
        let op_pos = read_pos;
        let raw_cmd = unsigned_word(data, read_pos * BYTECODE_SIZE);
        let opcode_value = opcode_from_raw_cmd(raw_cmd);
        let argc = argc_from_raw_cmd(raw_cmd);
        let line = line_from_raw_cmd(raw_cmd);
        ctx.current_line = if line != 0 { Some(line) } else { None };
        if line != 0 {
            op_lines.insert(op_pos, line);
        }
        read_pos += 1;

        if opcode_value == EVT_OP_INTERNAL_FETCH {
            return Err(verr(format!(
                "{}: EVT_OP_INTERNAL_FETCH appears in script data",
                format_script_site(script, op_pos, ctx.current_line)
            )));
        }
        let Some(opcode) = Opcode::from_raw(opcode_value) else {
            return Err(verr(format!(
                "{}: unknown opcode 0x{opcode_value:X}",
                format_script_site(script, op_pos, ctx.current_line)
            )));
        };
        if read_pos + argc as usize > words {
            return Err(verr(format!(
                "{}: {} argc {argc} runs past symbol boundary",
                format_script_site(script, op_pos, ctx.current_line),
                opcode.name()
            )));
        }

        let arg_pos = read_pos;
        let args: Vec<i32> = (0..argc as usize).map(|i| word_at(data, arg_pos + i)).collect();
        let raw_args: Vec<u32> = (0..argc as usize).map(|i| unsigned_word(data, (arg_pos + i) * BYTECODE_SIZE)).collect();

        validate_argc(script, op_pos, opcode, argc, ctx.current_line)?;
        validate_exec_arg_stream(script, op_pos, opcode, &args, ctx.current_line)?;
        validate_range_bound_types(script, op_pos, opcode, &args, ctx.current_line)?;
        validate_integer_math_arg_types(script, op_pos, opcode, &args, ctx.current_line)?;
        validate_clamp_literal_bounds(script, op_pos, opcode, &args, ctx.current_line)?;
        validate_lerp_duration(script, op_pos, opcode, &args, ctx.current_line)?;
        validate_mem_type(elf, script, op_pos, arg_pos, &args, opcode, ctx.current_line)?;
        validate_function_arg(elf, script, op_pos, arg_pos, &raw_args, opcode, ctx.current_line)?;
        read_pos += argc as usize;

        ctx.check_finally_command_allowed(op_pos, opcode)?;

        if opcode == Opcode::EVT_OP_END {
            end_pos = Some(read_pos);
            end_op_pos = op_pos;
            end_line = ctx.current_line;
            break;
        }

        match opcode {
            Opcode::EVT_OP_FINALLY => ctx.enter_finally(op_pos)?,
            Opcode::EVT_OP_LABEL => {
                let label = decode_label_value(elf, script, arg_pos, args[0], raw_args[0], op_pos, ctx.current_line, "Label")?;
                ctx.define_label(op_pos, label)?;
            }
            Opcode::EVT_OP_GOTO => {
                let label = decode_label_value(elf, script, arg_pos, args[0], raw_args[0], op_pos, ctx.current_line, "Goto")?;
                ctx.define_goto(op_pos, label);
            }
            _ if IF_OPS.contains(&opcode) => ctx.enter_if(op_pos),
            Opcode::EVT_OP_ELSE => ctx.enter_else(op_pos)?,
            Opcode::EVT_OP_END_IF => ctx.exit_if(op_pos)?,
            Opcode::EVT_OP_LOOP => ctx.enter_loop(op_pos)?,
            Opcode::EVT_OP_END_LOOP => ctx.exit_loop(op_pos)?,
            Opcode::EVT_OP_LERP => ctx.enter_lerp(op_pos)?,
            Opcode::EVT_OP_END_LERP => ctx.exit_lerp(op_pos)?,
            Opcode::EVT_OP_BREAK_LOOP => ctx.check_break_loop(op_pos)?,
            Opcode::EVT_OP_CONTINUE_LOOP => ctx.check_continue_loop(op_pos)?,
            Opcode::EVT_OP_RETRY_LOOP => ctx.check_retry_loop(op_pos)?,
            Opcode::EVT_OP_SWITCH | Opcode::EVT_OP_SWITCH_CONST => ctx.enter_switch(op_pos)?,
            _ if CASE_OPS.contains(&opcode) => ctx.enter_case(op_pos, opcode)?,
            Opcode::EVT_OP_END_CASE_GROUP => ctx.end_case_group(op_pos)?,
            Opcode::EVT_OP_BREAK_SWITCH => ctx.check_inside_switch(op_pos, "BreakSwitch")?,
            Opcode::EVT_OP_END_SWITCH => ctx.exit_switch(op_pos)?,
            Opcode::EVT_OP_THREAD => ctx.enter_thread(op_pos),
            Opcode::EVT_OP_END_THREAD => ctx.exit_thread(op_pos)?,
            Opcode::EVT_OP_CHILD_THREAD => ctx.enter_child_thread(op_pos),
            Opcode::EVT_OP_END_CHILD_THREAD => ctx.exit_child_thread(op_pos)?,
            _ => {}
        }
    }

    let Some(end_pos) = end_pos else {
        return Err(verr(format!(
            "{}: missing End before symbol boundary 0x{:X}",
            format_script_symbol(script),
            data.len()
        )));
    };

    if let Some(block) = ctx.stack.last() {
        let block_line = op_lines.get(&block.start_pos).copied();
        let mut msg = format!(
            "{}: unclosed {} block opened at +0x{:X}",
            format_script_symbol(script),
            block.kind.label(),
            block.start_pos * 4
        );
        if let Some(l) = block_line {
            msg.push_str(&format!(" (source line {l})"));
        }
        msg.push_str(&format!(" before End at +0x{:X}", end_op_pos * 4));
        if let Some(l) = end_line {
            msg.push_str(&format!(" (source line {l})"));
        }
        return Err(verr(msg));
    }

    let trailing_words = words - end_pos;
    if trailing_words != 0 {
        let mut msg = format!(
            "{}: {} unreachable byte(s) after End at +0x{:X}",
            format_script_symbol(script),
            trailing_words * BYTECODE_SIZE,
            end_op_pos * 4
        );
        if let Some(l) = end_line {
            msg.push_str(&format!(" (source line {l})"));
        }
        return Err(verr(msg));
    }

    for goto in &ctx.gotos {
        if !ctx.all_scopes[goto.scope_index].labels.contains_key(&goto.label) {
            return Err(verr(format!(
                "{}: Goto({}) has no matching Label in this thread scope",
                format_script_site(script, goto.op_pos, op_lines.get(&goto.op_pos).copied()),
                format_label(&goto.label)
            )));
        }
    }

    Ok(())
}

fn is_candidate_symbol(symbol: &Symbol, pattern: &SymbolPattern) -> bool {
    if symbol.shndx == SHN_UNDEF {
        return false;
    }
    if symbol.r#type() != crate::elf::STT_OBJECT {
        return false;
    }
    if (symbol.size as usize) < BYTECODE_SIZE || symbol.size as usize % BYTECODE_SIZE != 0 {
        return false;
    }
    pattern.matches(&symbol.name)
}

pub fn validate_object(path: &std::path::Path, pattern: &SymbolPattern) -> VResult<usize> {
    let elf = Elf32::open(path)?;
    let mut checked = 0;

    for symbol in &elf.symbols {
        if !is_candidate_symbol(symbol, pattern) {
            continue;
        }
        let (section, data) = elf.section_data_for_symbol(symbol)?;
        let script = ScriptSymbol {
            symbol: symbol.clone(),
            section_index: section.index,
            source_path: elf.source_path.clone(),
        };
        validate_script(&elf, &script, data)?;
        checked += 1;
    }

    Ok(checked)
}
