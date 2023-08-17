# Prerequisites

Before [getting started](./GettingStarted.html), please check whether you have all the necessary software installed and configured properly.
Alternatively, a preconfigured Ubuntu VM image is available [here](https://vm.lf-lang.org). 
Instructions for allowing the VM to access the RPi3+ via USB are available [here](VirtualMachine.html).

## Packages
Your system must have the following (very common) software packages installed:
 - `git` — [a distributed version control system](https://git-scm.com/)
 - `cmake` — [a cross-platform family of tools for building, testing and packaging software](https://cmake.org/)
 - `code` — [the Visual Studio Code IDE](https://code.visualstudio.com/download)
 - `curl` — [a CLI tool and library for transfering data with URLs](https://curl.se/)
 - `java` — [Java 17](https://openjdk.org/projects/jdk/17)
 - `nix` — [a purely functional package manager](https://nix.dev/tutorials/install-nix)
 - `screen` — [a terminal multiplexer](https://dev.to/thiht/learn-to-use-screen-a-terminal-multiplexer-gl)

We recommend using your favorite package manager to install them.

### Installation on Ubuntu
```bash
$ sudo apt install curl git openjdk-17-jdk openjdk-17-jre nix screen
$ sudo snap install code --classic
```

### Installation on macOS
```bash
$ brew install --cask visual-studio-code
$ brew install cmake git curl openjdk@17 screen
$ curl -L https://nixos.org/nix/install | sh
```

## VS Code extensions
Please ensure that you have the following extensions installed:
 - `marus25.cortex-debug` — [ARM Cortex-M GDB Debugger support for VSCode](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
 - `ms-vscode.cmake-tools` — [Extended CMake support in Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
 - `lf-lang.vscode-lingua-franca` — [Lingua Franca for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=lf-lang.vscode-lingua-franca)

To install them from the commandline, run:
```bash
$ code --install-extension marus25.cortex-debug
$ code --install-extension ms-vscode.cmake-tools
$ code --install-extension lf-lang.vscode-lingua-franca
```

## Permissions

### Using `nix` on Linux/WSL
To use `nix` on Linux, make sure that your user is a member of the `nix-users` group. To check this, run:

```bash
$ groups
```

If `nix-users` is not listed, run:

```bash
$ sudo usermod -aG nix-users $USER
```

Please note that you might need to reboot your system after running `usermod` in order for the new group membership to be reflected.

### Using `picotool` on Linux/WSL
To allow access to the RP2040 via USB without root superuser privileges, add a custom `udev` rules using the following command:
```bash
$ curl -s https://raw.githubusercontent.com/raspberrypi/picotool/master/udev/99-picotool.rules | sudo tee -a /etc/udev/rules.d/99-picotool.rules >/dev/null
```
