{
  description = "lf-pico dev env";
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-23.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.simpleFlake {
      inherit self nixpkgs;
      name = "lf-pico";
      overlay = ./overlay.nix;
      shell = ./shell.nix;
    };
}
