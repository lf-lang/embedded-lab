{ pkgs ? import <nixpkgs> }:
pkgs.mkShell {
  packages = with pkgs; [
    picotool
    cmake
    gcc-arm-embedded
    openocd
    #lingo
    #lingua-franca
  ];
  
  inputsFrom = with pkgs; [ 
    pico-sdk
  ];
  shellHook = ''
    export PICO_SDK_PATH=${pkgs.pico-sdk}/lib/pico-sdk
  '';

}
