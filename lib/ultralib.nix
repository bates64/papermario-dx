{ stdenv, pkgs, fetchFromGitHub, ... }:
stdenv.mkDerivation rec {
  pname = "ultralib";
  version = "K"; # https://github.com/decompals/ultralib/tree/main/base
  src = fetchFromGitHub {
    owner = "decompals";
    repo = "ultralib";
    rev = "2717d451b99c336e87a9e8548969bb57e383cfa5";
    hash = "sha256-io4GMw6P9u66lLptjme4bk3W6XZrDOYFrmrFnHHinOM=";
  };
  nativeBuildInputs = [ pkgs.python3 ];
  patchPhase = ''
    echo "CFLAGS += -fno-stack-protector -mno-abicalls -mno-gpopt" >> makefiles/modern_gcc.mk
    echo "OPTFLAGS += -Ofast" >> makefiles/modern_gcc.mk
  '';
  buildPhase = ''
    make VERSION=${version} MODERN_GCC=1 TARGET=libultra_rom
  '';
  installPhase = ''
    mkdir -p $out/lib $out/include
    cp -r build/${version}/libultra_rom/libultra_rom.a $out/lib
    cp -r include/* $out/include
  '';
}
