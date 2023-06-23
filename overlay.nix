final: prev:
{
    # TODO: apply board support patch locally
    pico-sdk = prev.pico-sdk.overrideAttrs (old: rec {
        pname = "pico-sdk";
        version = "1.5.1";
        src = fetchFromGithub {
            fetchSubmodules = true;
            owner = "raspberrypi";
            repo = pname;
            version = version;
            hash = "";
        };
    });
}