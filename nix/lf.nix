{pkgs ? import <nixpkgs> {}}:
pkgs.stdenv.mkDerivation {
    pname = "lingua-franca";
    version = "0.4.1";
    src = pkgs.fetchgit {
        fetchSubmodules = true;
        url = "https://github.com/lf-lang/lingua-franca.git";
        rev = "ea6f05a08cbb6b07bbd4a82203ecd23dae0fe1dc"; 
        sha256 = "sha256:xE1B69Cl3ryqSPOQhLGwh/SBGv+Mm8wtHGzRes3O1rQ=";
    };

    buildPhase = ''
        echo "[lfc] build"
        echo "[lfd] build"
        echo "[lff] build"
    '';

    installPhase = ''
        echo "[lfc, lfd, lff] install"
        cp -r ./ $out/
    '';

    # chmod +x $out/bin/lfc
}