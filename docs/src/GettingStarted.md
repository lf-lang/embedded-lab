# Getting Started

Before getting started, please make sure you have satisfied all the [prerequisites](Prerequisites.html).

## Create and clone your repository
Start by creating a new private repository on GitHub based on the [lf-3pi-template](https://github.com/lf-lang/lf-3pi-template) repository, which provides a starting point for students to carry out the exercises in this lab and to develop further applications using the [Raspberry Pi Pico board](https://www.raspberrypi.com/products/raspberry-pi-pico/) and the [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86).

Navigate to the [lf-3pi-template](https://github.com/lf-lang/lf-3pi-template) repository.  Select "Use this template" and "Create a new repository", as shown here:

<img src="img/3piTemplate.png" alt="Template repo"/>

Give your repo a name and click on "Create repository":

<img src="img/my-3pi.png" alt="new repo"/>

You can then clone your repository onto your host machine.
Copy the link:

<img src="img/newrepo.png" alt="new repo"/>

On the command line on your host machine, clone the repo:

```bash
git clone git@github.com/<username>/<reponame>.git
```

The template includes [raspberrypi/pico-sdk](https://github.com/raspberrypi/pico-sdk) as a submodule, which itself also has a lot of submodules. We recommend against using the `--recursive` flag because we do not need to recursively clone the submodules inside of `pico-sdk`. Instead, change directory into the root of your clone and run:

```bash
git submodule update --init
```

If  `pico-sdk` was checked out correctly, `git submodule` will show the hash _without_ a `-` preceding it,
e.g.: `6a7db34ff63345a7badec79ebea3aaef1712f374 pico-sdk (1.5.1)`.

## Configure Nix

To create a reproducible unix shell environment that installs all required dependency applications, we use the [nix](https://nixos.org) package manager. Install [nix](https://nixos.org/download.html) first for your preferred platform. There is support for Windows (via WSL), MacOS, and Linux.  If possible, use a **multi-user** install, which will require sudo permissions.

After installation, run the following in the shell to enable the experimental nix flakes feature, which helps to create more consistent builds:

```bash
mkdir -p ~/.config/nix
echo "experimental-features = nix-command flakes" >> ~/.config/nix/nix.conf
```

To install the dependencies, run the following in the root of your repository:

```bash
nix develop
```

This should automatically download and install specific revisions of the `gcc-arm` toolchain, `openocd`, and `picotool`. These packages will be required compiling, flashing and debugging C code for the RP2040.
(You can alternatively manually [install the Raspberry Pi Pico Tools](InstallingPicoTools.md).)

If you hit any error while running `nix develop`, see trouble shooting instructions below.

> **_Troubleshooting (Linux/WSL)_:** You may see an error message like this when running the `nix develop` command:
> ```bash
> error:
>       … while fetching the input 'git+file:///home/osboxes/lf-lang/my-3pi'
> error:
>       cannot connect to socket at '/nix/var/nix/daemon-socket/socket': Permission denied
>
> ```
> This means that your user is not a member of the `nix-users` group. To fix this, see (prerequisites)[Prerequisites.html#nix-on-linuxwsl].

> **_Troubleshooting (ARM/Apple Silicon Mac)_:** As of August 1, 2023, the stable version of nix does *not* support ARM/Apple Silicon Macs. You may see an error message like this when running the `nix develop` command:
> ```
> is not available on the requested hostPlatform
> ```
> Here is a workaround for this. You need to set up an environmental variable and run the nix command with an additional argument, `--impure`, like this:
> ```bash
> export NIXPKGS_ALLOW_UNSUPPORTED_SYSTEM=1
> nix develop --impure
> ```