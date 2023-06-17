# Installing Raspberry Pi Pico Tools

These instructions are adapted from the [Pololu instructions](../lib/pololu-3pi-2040-robot/c/README.md). See also the [GNU ARM installation instructions](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

## Set the PICO\_SDK\_PATH Environment Variable

Set the `PICO_SDK_PATH` environment variable:

```
export PICO_SDK_PATH=.../lf-pico/lib/pico-sdk
```

where `...` is replaced by the path to the folder where you cloned the `lf-pico` repository.  For convenience, put the above command in your `~/.bash_profile` file so that the environment variable is available to any bash terminal.  Depending on what operating system and terminal you use, you may need to find some other way to set this environment variable.

## Install CMake and ARM cross compiler

### On Linux

```
sudo apt update
sudo apt install cmake make gcc gcc-arm-none-eabi libnewlib-arm-none-eabi
```
Note:  Ubuntu and Debian users might additionally need to also install `libstdc++-arm-none-eabi-newlib`.

### On MacOS

```
$ brew install cmake make gcc arm-none-eabi-gcc
$ brew tap ArmMbed/homebrew-formulae
```

**NOTE:** If you are running on an Apple M1-based Mac you will need to install Rosetta 2 as the Arm compiler is still only compiled for x86 processors and does not have an Arm native version.
```$ /usr/sbin/softwareupdate --install-rosetta --agree-to-license
```

## Compile Plain C Examples

To make sure your installation has worked, compile the example programs provided with the pico-sdk.  Assuming you have cloned `lf-pico`, then from the `lf-pico` root directory, do this:

```
cd lib/pico-examples
mkdir build
cd build
cmake ..
make
```
After a while, the build directory will have subdirectories for many examples.  To load the Blink example onto the robot (which simply blinks an LED):

* Plug the robot into the USB port of your computer.
* Put the robot in boot loader mode by holding the B button while pressing the reset button. You should see an external disk appear with a name like `RPI-RP2`.
* Open the `RPI-RP2` folder.
* Drag the `blink.uf2` (in `lib/pico-examples/build/blink`) into the `RPI-RP2` folder.

The robot should immediately start running the program.
