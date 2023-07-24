{ pkgs ? import <nixpkgs> {} } :
let
  # lf = pkgs.callPackage ./nix/lf.nix {};
  # lingo = pkgs.callPackage ./nix/lingo.nix {};
in 
pkgs.mkShell {
  packages = with pkgs; [
    picotool
    cmake
    gcc-arm-embedded
    openocd
    git
    nodejs
    zellij
  ];
  buildInputs = [
    # lf
    # lingo
  ];

  shellHook = ''
    echo "[shell] hook"
    git submodule update --init
    cd ./pico-sdk
    git submodule update --init
    export PICO_SDK_PATH="$PWD"
    cd ../ '';
}
