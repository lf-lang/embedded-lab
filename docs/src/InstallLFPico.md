# Install lf-pico

These installation instructions are pretty rough. Please recommend updates, preferably via a pull request.

Windows users please see [notes for Windows users](WindowsInstallation.md).

## Clone the lf-pico Repository

```
git clone git@github.com:lf-lang/lf-pico.git
```

or

```
git clone https://github.com/lf-lang/lf-pico.git
```

## Setup
To create a reproducible unix shell environment that installs all required dependency applications, we use the nix package manager. Install [nix](https://nixos.org/download.html) first for your preferred platform. There is support for windows (wsl), macos and linux. 

After installation, run the following in the shell to enable the experimental nix flakes feature.
``` bash
mkdir -p ~/.config/nix
echo "experimental-features = nix-command flakes" >> ~/.config/nix/nix.conf
```

To launch the lf-pico shell environment, run the following in the root of the lf-pico repository. 
```bash
nix develop
```

This should automatically download and install specific revisions of the gcc-arm toolchain, openocd and picotool. These packages will be required compiling, flashing and debugging C code for the RP2040.

(You can alternatively manually [install the Raspberry Pi Pico Tools](InstallingPicoTools.md).)

## Install Lingua Franca and VS Code

* [Install Lingua Franca](InstallLF.md)
* [Install Visual Studio Code](InstallVSCode.md)
