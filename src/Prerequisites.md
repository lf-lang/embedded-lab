# Prerequisites

Before [getting started](./GettingStarted.html), please check whether you have all the necessary software installed and configured properly.
Alternatively, a pre-configured Ubuntu VM image is available [here](https://vm.lf-lang.org). Instructions for usage of the VM are provided [here](UbuntuVM.html).

## Packages

Your system must have the following (very common) software packages installed (we recommend using your favorite package manager to install them):

- `gh` — [a CLI tool for interaction with GitHub](https://cli.github.com/)
- `git` — [a distributed version control system](https://git-scm.com/)
- `cmake` — [a cross-platform family of tools for building, testing and packaging software](https://cmake.org/)
- `code` — [the Visual Studio Code IDE](https://code.visualstudio.com/download)
- `curl` — [a CLI tool and library for transfering data with URLs](https://curl.se/)
- `java` — [Java 17](https://openjdk.org/projects/jdk/17)
- `nix` — [a purely functional package manager](https://nix.dev/tutorials/install-nix)
- `screen` — [a terminal multiplexer](https://dev.to/thiht/learn-to-use-screen-a-terminal-multiplexer-gl)

### Installation on Ubuntu

```bash
$ sudo apt update
$ sudo apt install gh git curl openjdk-17-jdk openjdk-17-jre nix screen
$ sudo snap install code --classic
```

### Installation on macOS

```bash
$ brew install --cask visual-studio-code
$ brew install gh git cmake curl openjdk@17 screen
$ curl -L https://nixos.org/nix/install | sh
```

## Lingua Franca Toolchain

To install the nightly (recommended) Lingua Franca CLI tools (i.e, the compiler `lfc`, the diagram generator `lfd`, and the code formatter `lff`), run:

```
curl -Ls https://install.lf-lang.org | bash -s nightly cli
```

If you prefer an Eclipse-based IDE over the Lingua Franca VS Code extension, install the nightly build of `epoch` using the following command:

```
curl -Ls https://install.lf-lang.org | bash -s nightly epoch
```

> **_Troubleshooting for permission denied error_**
>
> If you get a permission denied error while running the command above (the error will look like below):
>
> ```
> > Creating directory /usr/local/share/lingua-franca
> mkdir: /usr/local/share/lingua-franca: Permission denied
> ```
>
> Try running the following commands which download the installation shell script and run the script with sudo:
>
> ```bash
> wget https://raw.githubusercontent.com/lf-lang/installation/main/install.sh
> chmod +x install.sh
> sudo bash install.sh nightly cli
> ```

## VS Code extensions

Please ensure that you have the following extensions installed:

- `ms-vscode.cmake-tools` — [Extended CMake support in Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- `ms-vscode.cpptools` — [C/C++ IntelliSense, debugging, and code browsing](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- `lf-lang.vscode-lingua-franca` — [Lingua Franca for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=lf-lang.vscode-lingua-franca)

For debugging support in VS Code:

- `marus25.cortex-debug` — [ARM Cortex-M GDB Debugger support for VSCode](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)

To install them from the command line, run:

```bash
$ code --install-extension ms-vscode.cmake-tools
$ code --install-extension ms-vscode.cpptools
$ code --install-extension lf-lang.vscode-lingua-franca --pre-release
$ code --install-extension marus25.cortex-debug
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

To allow access to the RP2040 via USB without superuser privileges, add custom `udev` rules using the following command:

```bash
$ curl -s https://raw.githubusercontent.com/raspberrypi/picotool/master/udev/99-picotool.rules | sudo tee -a /etc/udev/rules.d/99-picotool.rules >/dev/null
```
