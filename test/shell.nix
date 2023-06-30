{ pkgs ? import <nixpkgs> {} } : #specify a version tarball
let
    # lf will be accessible
in 
pkgs.mkShell {
  packages = with pkgs; [
    cmake
    gcc-arm-embedded
    pico-sdk
    node
  ];

  shellHook = ''
  '';

}
