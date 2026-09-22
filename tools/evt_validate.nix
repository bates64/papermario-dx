# Validates EVT bytecode stored in MIPS ELF object files (see
# tools/evt_validate/src). See tools/test/evt_validator for its fixture
# test suite.
{ rustPlatform }:
rustPlatform.buildRustPackage {
  pname = "evt_validate";
  version = "0.1.0";
  src = ./evt_validate;
  cargoLock.lockFile = ./evt_validate/Cargo.lock;
}
