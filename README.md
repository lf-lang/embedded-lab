# lf-pico
Support for the lingua franca runtime on the raspberry pi pico

## Overview
Tooling here allows for directly flashing lf programs to the
rpi-pico or using a secondary pico board as a 
debugger using the [picoprobe](https://github.com/raspberrypi/picoprobe) application

Adding the pico-sdk to the global path allows for easier cmake additions in headers and avoids
relative headers but is not required. For the specific platform, define the environment variable **PICO_SDK_PATH** with the path to the cloned sdk.

## Setup
The setup uses this branch of LFC to properly generate the cmake and
provide the correct support files, 
[pico](https://github.com/lf-lang/lingua-franca/tree/pico). 
Checkout this branch and build the lfc tool or download
the tool release [here]().

After, run the setup script from the root directory.
This will populate a directory ./pico/ with all raspberry pi pico
related dependencies and will build a few simple examples 
for getting started. script [source](https://github.com/michaelstoops/pico-setup/tree/master) 
```
platform/pico_setup.sh
```

### WSL Setup
It is recommend to use WSL when developing on a windows machine.
Use the following [installation](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) instructions to install usb support.

To mount the a pico device to the wsl instance, run the following in
an administrator powershell to find the correct bus and attach.

```
usbipd wsl list
usbipd wsl attach --busid <busid>
```

In the wsl instance, run the following to verify the device has mounted.

```
lsusb
```

TODO: add how to install udev permissions what is udev?
For debuging with the picoprobe, udev permissions have to 
be setup and restart everytime the probe is used.

```
sudo service udev restart && sudo udevadm trigger
```

## Flashing
After setup, run the following in the root 

```
lfc src/<app>.lf
code ./src-gen/<app>/
```

If the vscode instance was setup properly during setup, all necessary plugins will be installed
and cmake will automatically build. If this process doesnt start immediately, run

```
mkdir build
cd build
cmake ../
cmake ./ -build
```

The build directory will be populated with a uf2 file and an elf file. 
The uf2 file is primarily used for flashing the pico directly.
- Enter into bootsel mode
    - On 3pi 2040, hold the b button and press the reset button
- Connect the hardware to the host device
- Drag the uf2 to the newly mounted storage

TODO: Add instructions on how to analyze and automatically flash binaries using the pico-tool

## Debugging
Use minicom to open a console terminal an interact with the pico.
TODO: doesnt work on the robot?
```
minicom -b 115200 -o -D /dev/ttyACM0
```
