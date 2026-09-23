//! Validates EVT bytecode stored in MIPS ELF object files.
//!
//! This is intentionally a structural validator. It trusts ELF symbol
//! extents, not EVT_OP_END, to bound a script. That lets it catch both
//! missing End commands and premature End commands with trailing
//! unreachable bytecode/data.
//!
//! Validation currently catches:
//! - missing End commands;
//! - early End commands followed by unreachable bytecode/data;
//! - unknown, truncated, or malformed commands;
//! - commands with the wrong number of arguments;
//! - mismatched or unclosed If/Else/EndIf blocks;
//! - mismatched or unclosed Loop/EndLoop blocks;
//! - mismatched, nested, or unclosed Lerp/EndLerp blocks;
//! - mismatched or unclosed Switch/EndSwitch blocks;
//! - Loop and Switch nesting deeper than the runtime supports;
//! - CaseOrEq/CaseAndEq groups missing an EndCaseGroup;
//! - CaseOrEq and CaseAndEq mixed within the same case group;
//! - EndCaseGroup without an active CaseOrEq/CaseAndEq group;
//! - mismatched or unclosed Thread/EndThread and ChildThread/EndChildThread blocks;
//! - BreakLoop outside a Loop or Lerp;
//! - ContinueLoop outside a Loop, or inside a Lerp;
//! - RetryLoop outside a Loop, or inside a Lerp;
//! - BreakSwitch or Case commands outside a Switch;
//! - duplicate Label values within the same thread scope;
//! - thread scopes with more Label commands than the runtime supports;
//! - Label/Goto operands that are not integer constants or relocation-backed string labels;
//! - Goto(label) commands with no matching Label(label) in the current thread scope;
//! - misplaced, duplicated, or blocking commands inside Finally cleanup tails;
//! - mixed integer/Float literal bounds in IfRange/IfNotRange;
//! - Float literals in integer-only math commands where a float variant exists;
//! - literal Clamp/ClampF bounds where min > max;
//! - literal Lerp durations less than zero;
//! - memory access types that are not supported literal EVT_MEM_* values;
//! - Eval/Invoke/IfEval function operands that are not relocation-backed function addresses.

mod elf;
mod opcode;
mod pattern;
mod validate;

use std::io::IsTerminal;
use std::path::{Path, PathBuf};
use std::process::ExitCode;

use pattern::SymbolPattern;
use validate::ValidateError;

struct Args {
    objects: Vec<PathBuf>,
    out: Option<PathBuf>,
    symbol_pattern: String,
}

fn parse_args() -> Result<Args, String> {
    let mut objects = Vec::new();
    let mut object_lists = Vec::new();
    let mut out = None;
    let mut symbol_pattern = "(^|_)EVS_".to_string();

    let mut it = std::env::args().skip(1);
    while let Some(arg) = it.next() {
        match arg.as_str() {
            "--object-list" => {
                let path = it.next().ok_or("--object-list requires a value")?;
                object_lists.push(PathBuf::from(path));
            }
            "--out" => {
                let path = it.next().ok_or("--out requires a value")?;
                out = Some(PathBuf::from(path));
            }
            "--symbol-regex" => {
                symbol_pattern = it.next().ok_or("--symbol-regex requires a value")?;
            }
            other => objects.push(PathBuf::from(other)),
        }
    }

    for list_path in &object_lists {
        let content = std::fs::read_to_string(list_path)
            .map_err(|e| format!("{}: {e}", list_path.display()))?;
        for line in content.lines() {
            if !line.is_empty() {
                objects.push(PathBuf::from(line));
            }
        }
    }

    Ok(Args { objects, out, symbol_pattern })
}

fn stderr_supports_color() -> bool {
    std::io::stderr().is_terminal()
}

fn error_prefix() -> &'static str {
    if stderr_supports_color() {
        "\u{1b}[1;31merror:\u{1b}[0m"
    } else {
        "error:"
    }
}

fn highlight_error_message(message: &str) -> String {
    if !stderr_supports_color() {
        return message.to_string();
    }
    match message.rfind(": ") {
        Some(idx) => {
            let (head, tail) = (&message[..idx + 2], &message[idx + 2..]);
            format!("{head}\u{1b}[1;31m{tail}\u{1b}[0m")
        }
        None => format!("\u{1b}[1;31m{message}\u{1b}[0m"),
    }
}

fn format_cli_error(error: &ValidateError, current_object: Option<&Path>, objects: &[PathBuf]) -> String {
    match error {
        ValidateError::Validation(msg) => highlight_error_message(msg),
        ValidateError::Elf(msg) => {
            if let Some(obj) = current_object {
                highlight_error_message(&format!("{}: {msg}", obj.display()))
            } else if !objects.is_empty() {
                let joined = objects.iter().map(|p| p.display().to_string()).collect::<Vec<_>>().join(", ");
                highlight_error_message(&format!("{joined}: {msg}"))
            } else {
                highlight_error_message(msg)
            }
        }
    }
}

fn run() -> Result<(), (ValidateError, Option<PathBuf>, Vec<PathBuf>)> {
    let args = match parse_args() {
        Ok(a) => a,
        Err(msg) => return Err((ValidateError::Validation(msg), None, Vec::new())),
    };

    let pattern = match SymbolPattern::parse(&args.symbol_pattern) {
        Ok(p) => p,
        Err(msg) => return Err((ValidateError::Validation(msg), None, args.objects)),
    };

    if args.objects.is_empty() {
        return Err((ValidateError::Validation("no object files provided".to_string()), None, args.objects));
    }

    let mut checked = 0usize;
    for object in &args.objects {
        match validate::validate_object(object, &pattern) {
            Ok(n) => checked += n,
            Err(e) => return Err((e, Some(object.clone()), args.objects.clone())),
        }
    }

    if let Some(out) = &args.out {
        if let Some(parent) = out.parent() {
            std::fs::create_dir_all(parent).map_err(|e| {
                (ValidateError::Elf(format!("{e}")), None, args.objects.clone())
            })?;
        }
        std::fs::write(out, format!("{checked}\n")).map_err(|e| {
            (ValidateError::Elf(format!("{e}")), None, args.objects.clone())
        })?;
    }

    Ok(())
}

fn main() -> ExitCode {
    match run() {
        Ok(()) => ExitCode::SUCCESS,
        Err((error, current_object, objects)) => {
            eprintln!(
                "{} {}",
                error_prefix(),
                format_cli_error(&error, current_object.as_deref(), &objects)
            );
            ExitCode::FAILURE
        }
    }
}
