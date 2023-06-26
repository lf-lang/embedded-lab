
{ stdenv, pkgs, fetchgit }:
stdenv.mkDerivation {
    pname = "lingua-franca";
    version = "0.4.1";
    src = fetchgit {
        fetchSubmodules = true;
        url = "https://github.com/lf-lang/lingo.git";
        rev = "fe15e2510cf094956e30936143d23503c90c27d4"; 
        sha256 = "";
    };

    buildPhase = ''
        echo "[lingo] install" 
    '';

    installPhase = ''
        echo "[lingo] install" 
    ''

}