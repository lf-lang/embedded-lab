
{ stdenv, pkgs, fetchgit }:
stdenv.mkDerivation {
    pname = "lingua-franca";
    version = "0.4.1";
    src = fetchgit {
        fetchSubmodules = true;
        url = "https://github.com/lf-lang/lingo.git";
        rev = "fe15e2510cf094956e30936143d23503c90c27d4"; 
        sha256 = "sha256:V327g9qx6I5bJd9U1gbInX7H4sT1hSpxSuYHpVOiAVM=";
    };

    buildPhase = ''
        echo "[lingo] build" 
    '';

    installPhase = ''
        echo "[lingo] install" 
    '';

}