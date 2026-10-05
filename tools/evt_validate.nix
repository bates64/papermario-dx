{ rustPlatform }:
rustPlatform.buildRustPackage {
  pname = "evt_validate";
  version = "0.1.0";
  src = ./evt_validate;
  cargoLock.lockFile = ./evt_validate/Cargo.lock;
}
