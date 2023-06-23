{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  packages = with pkgs; [
    picotool
    cmake
    gcc-arm-embedded
    openocd
    git
    #lingo
    #lingua-franca
  ];

  shellHook = ''
    git submodule update --init
    cd ./lib/pico-sdk
    git submodule update --init
    export PICO_SDK_PATH="$PWD"
    cd ../../
  '';

}
