# Non-`nix` Setup

If you use `nix` as explained in the [getting started instructions](./GettingStarted.html#configure-nix), then you should not need to manually install the Raspberry Pi Pico SDK, C library and math library compiled for bare metal Cortex ARM, or the GNU Arm Embedded Toolchain for cross-compilation. To install these manually and not rely on `nix` to provide these dependencies, follow these instructions.

## Install Raspberry Pi Pico SDK

Clone the [raspberrypi/pico-sdk](https://github.com/raspberrypi/pico-sdk) repository and set the `PICO_SDK_PATH` environment variable:

```bash
$ git clone https://github.com/raspberrypi/pico-sdk.git
$ cd pico-sdk
$ export PICO_SDK_PATH=`pwd`
```

For convenience, set `PICO_SDK_PATH` in your `~/.bash_profile` file so that the environment variable is available to any bash terminal. After completing the steps above, this can be done as follows:

```bash
$ echo "export PICO_SDK_PATH=$PICO_SDK_PATH" >> ~/.bash_profile
```

Depending on what operating system and terminal you use, you may need to find some other way to set this environment variable.

## Install `picotool`
To build and install `picotool` from source, refer to the [raspberrypi/picotool](https://github.com/raspberrypi/picotool) repository.

## Install CMake, Standard C Library, ARM cross compiler

See also the [GNU ARM installation instructions](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads).

### On Ubuntu

```
sudo apt update
sudo apt install cmake make gcc gcc-arm-none-eabi libnewlib-arm-none-eabi
```
**Note:** It might be additionally needed to also install `libstdc++-arm-none-eabi-newlib`.

### On macOS

```
$ brew install cmake make gcc arm-none-eabi-gcc
$ brew tap ArmMbed/homebrew-formulae
```

**NOTE:** If you are running on an Apple M1-based Mac you will need to install Rosetta 2 as the Arm compiler is still only compiled for x86 processors and does not have an Arm native version.
```
$ /usr/sbin/softwareupdate --install-rosetta --agree-to-license
```

## Perform a Smoke Test

To make sure your installation has worked, follow the instructions [here](Tools.html#using-the-command-line).
