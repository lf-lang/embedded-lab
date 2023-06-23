final: prev:
{
    # TODO: apply board support patch locally
    pico-sdk = prev.pico-sdk.overrideAttrs (old: rec {
        pname = "pico-sdk";
        version = "1.5.1";
        src = prev.fetchFromGitHub {
            fetchSubmodules = true;
            owner = "raspberrypi";
            repo = pname;
            rev = version;
            sha256 = "sha256:GY5jjJzaENL3ftuU5KpEZAmEZgyFRtLwGVg3W1e/4Ho=";
        };
    });

    #lingo
    #lingua-franca
    #build picoprobe

}