from pathlib import Path

def convert_expression(expr: str) -> str:
  if expr.endswith("`"):
    return expr[:-1]

  if expr.startswith("."):
    if expr.startswith(".Anim") or expr.startswith(".AVar"):
      # e.g. .Anim:KingBoo_Hide -> ANIM_KingBoo_Hide
      key, val = expr[1:].split(":")
      return key.upper() + "_" + val
    elif expr.startswith(".Part"):
        return expr.replace(".Part", "PRT").replace(":", "_").upper()
    else:
      return expr[1:].replace(":", "_").upper()

  if expr[0].isdigit():
    return "0x" + expr

  # TODO: pointers
  if expr.startswith("$"):
    return expr.replace("$", "EVT_PTR(") + ")"

  if expr.startswith("*Fixed["):
    return expr.replace("*Fixed[", "EVT_FLOAT(").replace("]", ")")

  if expr.startswith("*Var"):
    return expr.replace("*Var", "LVar")

  return expr

def convert_script_line(line: str) -> str:
  if line.strip().startswith("%"):
    return line.replace("%", "//")

  # count leading whitespace
  leading_whitespace = 0
  for c in line:
    if c.isspace():
      leading_whitespace += 1
    elif c == "\t":
      leading_whitespace += 4
    else:
      break

  tokens = line.split()

  if not tokens:
    return ""

  opcode = tokens.pop(0)
  tokens = [convert_expression(t) for t in tokens if t != "(" and t != ")"]

  if opcode == "Call":
    opcode = "EVT_CALL"
  elif opcode == "Return":
    opcode = "EVT_RETURN"
  elif opcode == "End":
    opcode = "EVT_END"
  elif opcode == "Switch":
    opcode = "EVT_SWITCH"
  elif opcode == "EVT_END_SWITCH":
    opcode = "EVT_END_SWITCH"
  elif opcode == "Thread":
    opcode = "EVT_THREAD"
  elif opcode == "EndThread":
    opcode = "EVT_END_THREAD"
  elif opcode == "Set":
    opcode = "EVT_SET"
  elif opcode == "Add":
    opcode = "EVT_ADD"
  elif opcode == "Sub":
    opcode = "EVT_SUB"
  elif opcode == "Mul":
    opcode = "EVT_MUL"
  elif opcode == "Div":
    opcode = "EVT_DIV"
  elif opcode == "Mod":
    opcode = "EVT_MOD"
  elif opcode == "SetF":
    opcode = "EVT_SETF"

  if tokens:
    line = opcode + "(" + ", ".join(tokens) + ")"
  else:
    line = opcode

  # add leading whitespace
  line = " " * leading_whitespace + line

  return line

#['Call', 'SetAnimation', '(', '.Actor:Self', '.Part:KingBoo', '.Anim:KingBoo_Hide', ')']
#        Call  SetAnimation ( .Actor:Self .Part:KingBoo .Anim:KingBoo_Hide )
text = Path("TODO/Tatanga/Chikako.bpat").read_text()

# Collect all scripts
scripts = {} # name -> script
cur_script_lines = []
in_script = False
for line in text.splitlines():
  if line.startswith("#new:Script"):
    name_of_script = line.split()[1]
    cur_script_lines = []
    in_script = True
  elif in_script:
    if line.startswith("{"):
      pass
    elif line.startswith("}"):
      scripts[name_of_script] = cur_script_lines
      in_script = False
    else:
      cur_script_lines.append(line)

# Convert scripts to decomp syntax
for name, lines in scripts.items():
  # make the name EVS
  name = name.replace("$", "EVS_").replace("Script_", "")

  lines = [convert_script_line(line) for line in lines]

  print(f"EvtScript N({name}) = {{")
  print("\n".join(lines))
  print("};")
