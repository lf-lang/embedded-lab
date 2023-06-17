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

Then:

```
cd lf-pico
git submodule update --init --recursive
```

## Setup Script

Assuming you are in the `lf-pico` root directory, run:

```
platform/pico_setup.sh
```

After running the setup script, a directory `pico` will contain the RPi-Pico dependencies and will build a few simple examples 
for getting started. The script comes from this [source](https://github.com/michaelstoops/pico-setup/tree/master).

(You can alternatively manually [install the Raspberry Pi Pico Tools](InstallingPicoTools.md).)

## Install Lingua Franca and VS Code

* [Install Lingua Franca](InstallLF.md)
* [Install Visual Studio Code](InstallVSCode.md)
