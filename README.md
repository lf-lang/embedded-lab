# lf-pico
Support for the lingua franca runtime on the raspberry pi pico

## Overview
Tooling here allows for directly flashing lf programs to the
rpi-pico or using a secondary pico board as a 
debugger using the [picoprobe](https://github.com/raspberrypi/picoprobe) application

Adding the pico-sdk to the global path allows for easier cmake additions in headers and avoids
relative headers but is not required. For the specific platform, define the environment variable **PICO_SDK_PATH** with the path to the cloned sdk.

TODO: lingo init steps

## Setup
TODO: merge into main LFC branch
The setup uses this branch of LFC to properly generate the cmake and provide the correct support files 
[pico](https://github.com/lf-lang/lingua-franca/tree/pico). Checkout this branch and build the lfc tool.
After, run the setup script from the root directory. This will populate the sdk submodule and build
the picoprobe.uf2 used for debugging the robot.
```
platform/setup.sh
```

TODO: use picotool for auto testing and flashing

## Flashing
- Install Toolchain
The pico uses the GNU arm toolchain. 
Install [here](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

`` 
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
``

After setup, run the following in the root 

``
lfc src/<file>.lf
cd src-gen/<file>/build
make .
``

The custom build script will open a new vscode instance and run cmake to 
generate the build files for the project. The build directory will also be populated with a uf2 file
and an elf file. 
- Enter into bootsel mode
    - On 3pi 2040, hold the b button and press the reset button
- Connect the hardware to the host device
- Drag the uf2 or elf file to the newly mounted storage

TODO: Add instructions on how to analyze and automatically flash binaries using the pico-tool

## Debugging
