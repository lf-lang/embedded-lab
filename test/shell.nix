{ pkgs ? import <nixpkgs> {} } : #specify a version tarball
let
    # lf will be accessible
    rp2040js = callPackage ../nix/rp2040js.nix {};
in 
pkgs.mkShell {
  packages = with pkgs; [
    cmake
    gcc-arm-embedded
    pico-sdk
    node
  ];
  buildInputs = [ rp2040js ];

  shellHook = ''
  '';

}
