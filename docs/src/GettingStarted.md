# Getting Started

Before getting started, please make sure you have satisfied all the [prerequisites](Prerequisites.html).

## Set up GitHub account and SSH key
If you do not yet have a GitHub account, [create one](https://github.com/signup).

### Set up authentication with GitHub
In order to push to your repo, you need to authenticate. You can either do this using a public/private key pair through SSH, or use token-based authentication via `gh`, the GitHub command-line interface. We recommend the latter method for VM users.

#### Using GitHub CLI
To authenticate with GitHub through its CLI tool, run:
```bash
$ gh auth login
```

#### Using SSH
In the ⚙️ [<kbd>Settings</kbd>](https://github.com/settings/profile) of your [GitHub account](https://github.com), go to 🔑 [<kbd>SSH and GPG keys</kbd>](https://github.com/settings/keys) and enter the contents of your `~/.ssh/id_rsa.pub`. If you do not have this file, create it using the following command:
```bash
$ ssh-keygen -t rsa -b 4096 -C "your_github@email.com"
```
Additional information about setting up public key authentication with GitHub can be found [here](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account).

> **_Tip for VM users_**
> 
> If you are looking for a convenient way to copy your private key onto a VM, consider using [Magic Wormhole](https://github.com/magic-wormhole/magic-wormhole). It is preinstalled on the [Ubuntu VM](https://vm.lf-lang.org) prepared for this course.


## Create your repository
Start by creating a new private repository on GitHub based on the [lf-3pi-template](https://github.com/lf-lang/lf-3pi-template) repository, which provides a starting point for students to carry out the exercises in this lab and to develop further applications using the [Raspberry Pi Pico board](https://www.raspberrypi.com/products/raspberry-pi-pico/) and the [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86).

Navigate to the [lf-3pi-template](https://github.com/lf-lang/lf-3pi-template) repository.  Select "Use this template" and "Create a new repository", as shown here:

<img src="img/3piTemplate.png" alt="Template repo"/>

Give your repo a name and click on "Create repository":

<img src="img/my-3pi.png" alt="new repo"/>

## Clone your repository
On the command line on your host machine, clone the repo.
For an SSH-based setup, run:

```bash
$ git clone git@github.com/<username>/<reponame>.git
```

Or, for a setup that uses GitHub CLI, run:

```bash
$ gh repo clone <username>/<reponame>
```

The template includes [raspberrypi/pico-sdk](https://github.com/raspberrypi/pico-sdk) as a submodule, which itself also has a lot of submodules. We recommend against using the `--recursive` flag because we do not need to recursively clone the submodules inside of `pico-sdk`. Instead, change directory into the root of your clone and run:

```bash
$ git submodule update --init
```

If  `pico-sdk` was checked out correctly, `git submodule` will show the hash _without_ a `-` preceding it,
e.g.: `6a7db34ff63345a7badec79ebea3aaef1712f374 pico-sdk (1.5.1)`.


## Configure Nix

To create a reproducible unix shell environment that installs all required dependency applications, we use the [nix](https://nixos.org) package manager, which has support for Linux, macOS, and Windows (via WSL). See [prerequisites](Prerequisites.html) for installation instructions. If you prefer to manage dependencies yourself and not rely on `nix`, follow the [instructions for a non-`nix` setup](Non-Nix.html).

After installation, run the following in the shell to enable the experimental nix flakes feature, which helps to create more consistent builds:

```bash
$ mkdir -p ~/.config/nix
$ echo "experimental-features = nix-command flakes" >> ~/.config/nix/nix.conf
```

To install the dependencies, run the following in the root of your repository:

```bash
$ nix develop
```

This should automatically download and install specific revisions of the `gcc-arm` toolchain, `openocd`, and `picotool`. These packages will be required compiling, flashing and debugging C code for the RP2040.
(You can alternatively manually [install the Raspberry Pi Pico Tools](Non-Nix.html#install-picotool).)

If you hit any error while running `nix develop`, see troubleshooting instructions below.

> **_Troubleshooting (Linux/WSL)_**
>
> You may see an error message like this when running the `nix develop` command:
> ```bash
> error:
>       … while fetching the input 'git+file:///home/osboxes/lf-lang/my-3pi'
> error:
>       cannot connect to socket at '/nix/var/nix/daemon-socket/socket': Permission denied
>
> ```
> This means that your user is not a member of the `nix-users` group. To fix this, see [prerequisites](Prerequisites.html#using-nix-on-linuxwsl).

> **_Troubleshooting (ARM/Apple Silicon Mac)_**
>
> As of August 1, 2023, the stable version of nix does *not* support ARM/Apple Silicon Macs. You may see an error message like this when running the `nix develop` command:
> ```
> is not available on the requested hostPlatform
> ```
> You can work around this issue by setting up an environmental variable and running the nix command with an additional argument, `--impure`, like this:
> ```bash
> $ export NIXPKGS_ALLOW_UNSUPPORTED_SYSTEM=1
> $ nix develop --impure
> ```
