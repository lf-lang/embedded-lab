# Installing Raspberry Pi Pico Tools

If you use Nix as explained in the [installation instructions](./Installation.md), then you should not need to manually install the Raspberry Pi Pico SDK.  But just in case, we provide here instructions adapted from the [Pololu instructions](../lib/pololu-3pi-2040-robot/c/README.md). See also the [GNU ARM installation instructions](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

## Set the PICO\_SDK\_PATH Environment Variable

Set the `PICO_SDK_PATH` environment variable:

```
export PICO_SDK_PATH=../lf-pico/lib/pico-sdk
```

where `...` is replaced by the path to the folder where you cloned the `lf-pico` repository.  For convenience, put the above command in your `~/.bash_profile` file so that the environment variable is available to any bash terminal.  Depending on what operating system and terminal you use, you may need to find some other way to set this environment variable.

Note that the `PICO_SDK_PATH` variable is automatically set by `nix develop` in the shell that  it launches (see the [installation instructions](./Installation.md)).
Moreover, if you use the template repo, then `PICO_SDK_PATH` will be subsequently automatically set whenever you compile any LF file in your repo even if you are not using the shell launched by `nix develop`.

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
```
$ /usr/sbin/softwareupdate --install-rosetta --agree-to-license
```

## Compile Plain C Examples

To make sure your installation has worked, compile the example programs provided with the pico-sdk.  Assuming you have cloned `lf-pico`, then from the `lf-pico` root directory, do this:

```
cd pico/pico-examples
mkdir build
cd build
cmake ..
make
```
After a while, the build directory will have subdirectories for many examples.  To load the Blink example onto the robot (which simply blinks an LED):

* Plug the robot into the USB port of your computer.
* Put the robot in BOOTSEL mode by holding the B button while pressing the reset button. You should see an external disk appear with a name like `RPI-RP2`.
* Open the `RPI-RP2` folder.
* Drag the `blink.uf2` (in `lib/pico-examples/build/blink`) into the `RPI-RP2` folder.

The robot should immediately start running the program.
