# Non-`nix` Setup

If you use `nix` as explained in the [getting started instructions](./GettingStarted.html#configure-nix), then you should not need to manually install the Raspberry Pi Pico SDK, C library and math library compiled for bare metal Cortex ARM, or the GNU Arm Embedded Toolchain for cross-compilation. To install these manually and not rely on `nix` to provide these dependencies, follow these instructions.

## Install Raspberry Pi Pico SDK

Clone the [raspberrypi/pico-sdk](https://github.com/raspberrypi/pico-sdk) repository (and its submodules) and set the `PICO_SDK_PATH` environment variable:

```bash
$ git clone https://github.com/raspberrypi/pico-sdk.git
$ cd pico-sdk
$ git submodule update --init
$ export PICO_SDK_PATH=`pwd`
```

For convenience, set `PICO_SDK_PATH` in your `~/.profile` file so that the environment variable is available to any bash terminal. After completing the steps above, this can be done as follows:

```bash
$ echo "export PICO_SDK_PATH=$PICO_SDK_PATH" >> ~/.profile
```

__Caution__: Depending on what operating system and terminal you use, and how it is configured, you may need to find some other way to set this environment variable.

### Robot Board Header
To support different pin configurations for rp2040 based boards, pico-sdk uses board header files found in `pico-sdk/src/boards/include/boards`.
When building binaries for boards other than the raspberrypi pico, `-DPICO_BOARD=<board_name>` can be passed to the cmake command 
where `<board_name>` is the header name.

The board header for the 3pi robot in the repo might not correctly map the uart pins. Modify `pololu_3pi_2040_robot.h` in the board header directory 
to include the following lines:

``` C
#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 28
#endif

#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 29
#endif
```

## Install `picotool`
To build and install `picotool` from source, run the following commands:

```bash
$ git clone https://github.com/raspberrypi/picotool.git
$ cd picotool
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

## Install CMake, Standard C Library, ARM cross compiler

For reference, see the [GNU ARM installation instructions](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). For installation instructions specific to Ubuntu and macOS, read on.

### On Ubuntu

```
sudo apt update
sudo apt install cmake make gcc gcc-arm-none-eabi libnewlib-arm-none-eabi
```

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
