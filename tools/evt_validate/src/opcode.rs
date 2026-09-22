// Keep these values and argument counts in sync with include/evt.h.

pub const MAX_ARGC: u8 = 0xFF;
pub const MAX_EVAL_ARGS: u8 = 6;

#[derive(Clone, Copy, PartialEq, Eq, Debug, Hash)]
pub struct Opcode(pub u8);

macro_rules! opcodes {
    ($($konst:ident = ($value:expr, $min:expr $(, $max:expr)?);)*) => {
        impl Opcode {
            $(pub const $konst: Opcode = Opcode($value);)*

            pub fn from_raw(value: u8) -> Option<Opcode> {
                match value {
                    $($value => Some(Opcode::$konst),)*
                    _ => None,
                }
            }

            pub fn name(self) -> &'static str {
                match self.0 {
                    $($value => stringify!($konst),)*
                    _ => unreachable!(),
                }
            }

            pub fn argc_min(self) -> u8 {
                match self.0 {
                    $($value => $min,)*
                    _ => unreachable!(),
                }
            }

            pub fn argc_max(self) -> u8 {
                match self.0 {
                    $($value => opcodes!(@max $min $(, $max)?),)*
                    _ => unreachable!(),
                }
            }
        }
    };
    (@max $min:expr) => { $min };
    (@max $min:expr, $max:expr) => { $max };
}

opcodes! {
    EVT_OP_END = (0x01, 0);
    EVT_OP_RETURN = (0x02, 0);
    EVT_OP_LABEL = (0x03, 1);
    EVT_OP_GOTO = (0x04, 1);
    EVT_OP_LOOP = (0x05, 1);
    EVT_OP_END_LOOP = (0x06, 0);
    EVT_OP_BREAK_LOOP = (0x07, 0);
    EVT_OP_CONTINUE_LOOP = (0x08, 0);
    EVT_OP_RETRY_LOOP = (0x09, 0);
    EVT_OP_WAIT_FRAMES = (0x0A, 1);
    EVT_OP_WAIT_SECS = (0x0B, 1);
    EVT_OP_IF_EQ = (0x0C, 2);
    EVT_OP_IF_NE = (0x0D, 2);
    EVT_OP_IF_LT = (0x0E, 2);
    EVT_OP_IF_GT = (0x0F, 2);
    EVT_OP_IF_LE = (0x10, 2);
    EVT_OP_IF_GE = (0x11, 2);
    EVT_OP_IF_RANGE = (0x12, 3);
    EVT_OP_IF_NOT_RANGE = (0x13, 3);
    EVT_OP_IF_FLAG = (0x14, 2);
    EVT_OP_IF_NOT_FLAG = (0x15, 2);
    EVT_OP_ELSE = (0x16, 0);
    EVT_OP_END_IF = (0x17, 0);
    EVT_OP_SWITCH = (0x18, 1);
    EVT_OP_SWITCH_CONST = (0x19, 1);
    EVT_OP_CASE_EQ = (0x1A, 1);
    EVT_OP_CASE_NE = (0x1B, 1);
    EVT_OP_CASE_LT = (0x1C, 1);
    EVT_OP_CASE_GT = (0x1D, 1);
    EVT_OP_CASE_LE = (0x1E, 1);
    EVT_OP_CASE_GE = (0x1F, 1);
    EVT_OP_CASE_DEFAULT = (0x20, 0);
    EVT_OP_CASE_OR_EQ = (0x21, 1);
    EVT_OP_CASE_AND_EQ = (0x22, 1);
    EVT_OP_CASE_FLAG = (0x23, 1);
    EVT_OP_END_CASE_GROUP = (0x24, 0);
    EVT_OP_CASE_RANGE = (0x25, 2);
    EVT_OP_BREAK_SWITCH = (0x26, 0);
    EVT_OP_END_SWITCH = (0x27, 0);
    EVT_OP_SET = (0x28, 2);
    EVT_OP_SET_CONST = (0x29, 2);
    EVT_OP_SETF = (0x2A, 2);
    EVT_OP_ADD = (0x2B, 2, MAX_ARGC);
    EVT_OP_SUB = (0x2C, 2, 3);
    EVT_OP_MUL = (0x2D, 2, MAX_ARGC);
    EVT_OP_DIV = (0x2E, 2, 3);
    EVT_OP_MOD = (0x2F, 2, 3);
    EVT_OP_ADDF = (0x30, 2, MAX_ARGC);
    EVT_OP_SUBF = (0x31, 2, 3);
    EVT_OP_MULF = (0x32, 2, MAX_ARGC);
    EVT_OP_DIVF = (0x33, 2, 3);
    EVT_OP_NEG = (0x34, 1, 2);
    EVT_OP_NEGF = (0x35, 1, 2);
    EVT_OP_ABS = (0x36, 1, 2);
    EVT_OP_ABSF = (0x37, 1, 2);
    EVT_OP_SIGN = (0x38, 1, 2);
    EVT_OP_SIGNF = (0x39, 1, 2);
    EVT_OP_MIN = (0x3A, 2, MAX_ARGC);
    EVT_OP_MINF = (0x3B, 2, MAX_ARGC);
    EVT_OP_MAX = (0x3C, 2, MAX_ARGC);
    EVT_OP_MAXF = (0x3D, 2, MAX_ARGC);
    EVT_OP_CLAMP = (0x3E, 3, 4);
    EVT_OP_CLAMPF = (0x3F, 3, 4);
    EVT_OP_USE_BUF = (0x40, 1);
    EVT_OP_BUF_READ = (0x41, 1, MAX_ARGC);
    EVT_OP_BUF_PEEK = (0x42, 2);
    EVT_OP_USE_FBUF = (0x43, 1);
    EVT_OP_FBUF_READ = (0x44, 1, MAX_ARGC);
    EVT_OP_FBUF_PEEK = (0x45, 2);
    EVT_OP_MEM_GET = (0x46, 4);
    EVT_OP_MEM_SET = (0x47, 4);
    EVT_OP_USE_ARRAY = (0x48, 1);
    EVT_OP_USE_FLAGS = (0x49, 1);
    EVT_OP_MALLOC_ARRAY = (0x4A, 2);
    EVT_OP_BITWISE_AND = (0x4B, 2);
    EVT_OP_BITWISE_AND_CONST = (0x4C, 2);
    EVT_OP_BITWISE_OR = (0x4D, 2);
    EVT_OP_BITWISE_OR_CONST = (0x4E, 2);
    EVT_OP_CALL = (0x4F, 1, MAX_ARGC);
    EVT_OP_EXEC = (0x50, 1, MAX_ARGC);
    EVT_OP_EXEC_GET_ID = (0x51, 2, MAX_ARGC);
    EVT_OP_EXEC_WAIT = (0x52, 1, MAX_ARGC);
    EVT_OP_BIND_TRIGGER = (0x53, 5);
    EVT_OP_UNBIND = (0x54, 0);
    EVT_OP_KILL_SCRIPT = (0x55, 1);
    EVT_OP_JUMP = (0x56, 1);
    EVT_OP_SET_PRIORITY = (0x57, 1);
    EVT_OP_SET_TIMESCALE = (0x58, 1);
    EVT_OP_SET_GROUP = (0x59, 1);
    EVT_OP_BIND_ITEM_PROMPT = (0x5A, 6);
    EVT_OP_SUSPEND_GROUP = (0x5B, 1);
    EVT_OP_RESUME_GROUP = (0x5C, 1);
    EVT_OP_SUSPEND_OTHERS = (0x5D, 1);
    EVT_OP_RESUME_OTHERS = (0x5E, 1);
    EVT_OP_SUSPEND_SCRIPT = (0x5F, 1);
    EVT_OP_RESUME_SCRIPT = (0x60, 1);
    EVT_OP_IS_SCRIPT_RUNNING = (0x61, 2);
    EVT_OP_THREAD = (0x62, 0);
    EVT_OP_END_THREAD = (0x63, 0);
    EVT_OP_CHILD_THREAD = (0x64, 0);
    EVT_OP_END_CHILD_THREAD = (0x65, 0);
    EVT_OP_AWAIT_CHILDREN = (0x66, 0);
    EVT_OP_AWAIT_SCRIPT = (0x67, 1);
    EVT_OP_DEBUG_PRINT_VAR = (0x68, 1);
    EVT_OP_DEBUG_BREAKPOINT = (0x69, 1);
    EVT_OP_EXPECT_ARGS = (0x6A, 1);
    EVT_OP_FINALLY = (0x6B, 0);
    EVT_OP_EVAL = (0x6C, 2, 2 + MAX_EVAL_ARGS);
    EVT_OP_EVALF = (0x6D, 2, 2 + MAX_EVAL_ARGS);
    EVT_OP_INVOKE = (0x6E, 1, 1 + MAX_EVAL_ARGS);
    EVT_OP_INVOKEF = (0x6F, 1, 1 + MAX_EVAL_ARGS);
    EVT_OP_IF_EVAL = (0x70, 1, 1 + MAX_EVAL_ARGS);
    EVT_OP_IF_NOT_EVAL = (0x71, 1, 1 + MAX_EVAL_ARGS);
    EVT_OP_IF_EVALF = (0x72, 1, 1 + MAX_EVAL_ARGS);
    EVT_OP_IF_NOT_EVALF = (0x73, 1, 1 + MAX_EVAL_ARGS);
    EVT_OP_LERP = (0x74, 5);
    EVT_OP_END_LERP = (0x75, 0);
}

impl Opcode {
    pub fn is_variadic(self) -> bool {
        self.argc_min() != self.argc_max()
    }
}

pub fn command_display_name(opcode: Opcode) -> String {
    if let Some(o) = FINALLY_COMMAND_NAME_OVERRIDE.iter().find(|(k, _)| *k == opcode) {
        return o.1.to_string();
    }
    opcode
        .name()
        .strip_prefix("EVT_OP_")
        .unwrap_or(opcode.name())
        .split('_')
        .map(|part| {
            let mut c = part.chars();
            match c.next() {
                Some(f) => f.to_uppercase().collect::<String>() + &c.as_str().to_lowercase(),
                None => String::new(),
            }
        })
        .collect()
}

pub const FINALLY_COMMAND_NAME_OVERRIDE: &[(Opcode, &str)] = &[
    (Opcode::EVT_OP_WAIT_FRAMES, "Wait"),
    (Opcode::EVT_OP_WAIT_SECS, "WaitSecs"),
    (Opcode::EVT_OP_DEBUG_BREAKPOINT, "BreakPoint"),
];

pub const IF_OPS: &[Opcode] = &[
    Opcode::EVT_OP_IF_EQ,
    Opcode::EVT_OP_IF_NE,
    Opcode::EVT_OP_IF_LT,
    Opcode::EVT_OP_IF_GT,
    Opcode::EVT_OP_IF_LE,
    Opcode::EVT_OP_IF_GE,
    Opcode::EVT_OP_IF_RANGE,
    Opcode::EVT_OP_IF_NOT_RANGE,
    Opcode::EVT_OP_IF_FLAG,
    Opcode::EVT_OP_IF_NOT_FLAG,
    Opcode::EVT_OP_IF_EVAL,
    Opcode::EVT_OP_IF_NOT_EVAL,
    Opcode::EVT_OP_IF_EVALF,
    Opcode::EVT_OP_IF_NOT_EVALF,
];

pub const CASE_OPS: &[Opcode] = &[
    Opcode::EVT_OP_CASE_EQ,
    Opcode::EVT_OP_CASE_NE,
    Opcode::EVT_OP_CASE_LT,
    Opcode::EVT_OP_CASE_GT,
    Opcode::EVT_OP_CASE_LE,
    Opcode::EVT_OP_CASE_GE,
    Opcode::EVT_OP_CASE_DEFAULT,
    Opcode::EVT_OP_CASE_OR_EQ,
    Opcode::EVT_OP_CASE_AND_EQ,
    Opcode::EVT_OP_CASE_FLAG,
    Opcode::EVT_OP_CASE_RANGE,
];

pub const CASE_GROUP_OPS: &[Opcode] = &[Opcode::EVT_OP_CASE_OR_EQ, Opcode::EVT_OP_CASE_AND_EQ];

pub const FINALLY_FORBIDDEN_OPS: &[Opcode] = &[
    Opcode::EVT_OP_RETURN,
    Opcode::EVT_OP_LABEL,
    Opcode::EVT_OP_GOTO,
    Opcode::EVT_OP_LOOP,
    Opcode::EVT_OP_END_LOOP,
    Opcode::EVT_OP_BREAK_LOOP,
    Opcode::EVT_OP_CONTINUE_LOOP,
    Opcode::EVT_OP_RETRY_LOOP,
    Opcode::EVT_OP_LERP,
    Opcode::EVT_OP_END_LERP,
    Opcode::EVT_OP_WAIT_FRAMES,
    Opcode::EVT_OP_WAIT_SECS,
    Opcode::EVT_OP_EXEC_WAIT,
    Opcode::EVT_OP_AWAIT_CHILDREN,
    Opcode::EVT_OP_AWAIT_SCRIPT,
    Opcode::EVT_OP_DEBUG_BREAKPOINT,
    Opcode::EVT_OP_JUMP,
    Opcode::EVT_OP_THREAD,
    Opcode::EVT_OP_CHILD_THREAD,
];

pub const EXEC_OPS: &[Opcode] = &[
    Opcode::EVT_OP_EXEC,
    Opcode::EVT_OP_EXEC_GET_ID,
    Opcode::EVT_OP_EXEC_WAIT,
];

pub const RANGE_IF_OPS: &[Opcode] = &[Opcode::EVT_OP_IF_RANGE, Opcode::EVT_OP_IF_NOT_RANGE];

pub const CLAMP_OPS: &[Opcode] = &[Opcode::EVT_OP_CLAMP, Opcode::EVT_OP_CLAMPF];

pub fn integer_math_float_variant(opcode: Opcode) -> Option<&'static str> {
    match opcode {
        Opcode::EVT_OP_NEG => Some("NegF"),
        Opcode::EVT_OP_ABS => Some("AbsF"),
        Opcode::EVT_OP_SIGN => Some("SignF"),
        Opcode::EVT_OP_MIN => Some("MinF"),
        Opcode::EVT_OP_MAX => Some("MaxF"),
        Opcode::EVT_OP_CLAMP => Some("ClampF"),
        _ => None,
    }
}

/// Index (0-based, into the command's own args) of the function-pointer
/// argument for opcodes whose relocation-backed argument needs checking.
pub fn function_arg_index(opcode: Opcode) -> Option<usize> {
    match opcode {
        Opcode::EVT_OP_EVAL => Some(1),
        Opcode::EVT_OP_EVALF => Some(1),
        Opcode::EVT_OP_INVOKE => Some(0),
        Opcode::EVT_OP_INVOKEF => Some(0),
        Opcode::EVT_OP_IF_EVAL => Some(0),
        Opcode::EVT_OP_IF_NOT_EVAL => Some(0),
        Opcode::EVT_OP_IF_EVALF => Some(0),
        Opcode::EVT_OP_IF_NOT_EVALF => Some(0),
        _ => None,
    }
}
