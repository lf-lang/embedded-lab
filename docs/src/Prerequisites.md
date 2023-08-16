# Prerequisites

Before [getting started](./GettingStarted.html), please check whether you have all the necessary software installed and configured properly.

## Packages
Your system must have the following (very common) software packages installed:
 - `git` — [a distributed version control system](https://git-scm.com/)
 - `code` — [the Visual Studio Code IDE](https://code.visualstudio.com/download)
 - `nix` — [a purely functional package manager](https://nix.dev/tutorials/install-nix)
 - `curl` — [a CLI tool and library for transfering data with URLs](https://curl.se/)

We recommend using your favorite package manager to install them.

### Installation on Ubuntu
```bash
sudo apt install curl git nix
sudo snap install code --classic
```

### Installation on macOS
```bash
brew install --cask visual-studio-code
brew install git curl
curl -L https://nixos.org/nix/install | sh
```

## VS Code extensions
Please ensure that you have the following extensions installed:
 - `marus25.cortex-debug` — [ARM Cortex-M GDB Debugger support for VSCode](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
 - `ms-vscode.cmake-tools` — [Extended CMake support in Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
 - `lf-lang.vscode-lingua-franca` — [Lingua Franca for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=lf-lang.vscode-lingua-franca)

To install them from the commandline, run:
```bash
code --install-extension marus25.cortex-debug
code --install-extension ms-vscode.cmake-tools
code --install-extension lf-lang.vscode-lingua-franca
```

## GitHub account and SSH key
If you do not yet have a GitHub account, [create one](https://github.com/signup). In the ⚙️ <kbd>Settings</kbd> of your GitHub account, go to 🔑 <kbd>SSH and GPG keys</kbd> and enter the contents of your `~/.ssh/id_rsa.pub`. If you do not have this file, create it using the following command:
```bash
ssh-keygen -t rsa -b 4096 -C "your_github@email.com"
```
Additional information about setting up public key authentication with GitHub can be found [here](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account).

## Permissions

### Nix on Linux/WSL
To use `nix` on Linux, make sure that your user is a member of the `nix-users` group. To check this, run:

```bash
groups
```

If `nix-users` is not listed, run:

```bash
sudo usermod -aG nix-users <username>
```

Please note that you might need to reboot your system after running `usermod` in order for the new group membership to be reflected.
