# Tools and Environments
The purpose of this lab exercise is to familiarize you with the various tools and environments used for embedded software programming. A simple Lingua Franca program, `blink.lf`, is provided for you to experiment with.
This lab exercise assumes you have followed the [Installation instructions](./Installation.md)

Embedded systems often have limited resources and interaction methods and hence require a different approach for programming.
Their microprocessors often have no operating system, and are therefore called "bare metal" or "bare iron" machines.
They often have no keyboard or display connected to them, which can make interaction challenging.
And they often have limited networking capability.
In this lab exercise, you will learn to interact with a particular microcontroller, a Raspberry Pi Pico RP2040
(RPi-Pico), on the [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86). 

This section will explore the RPi-Pico microcontroller, a low cost dual-core Arm-based chip with various useful and unique hardware peripherals. The chip is embedded in the popular RPi-Pico and is tailored for education.

## Prelab
### Resources

- [Nix](https://nixos.org) (for installation)
- [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) (pdf)
- [Raspberry Pi Pico SDK documentation](https://www.raspberrypi.com/documentation/pico-sdk/)
- [Raspberry Pi Pico SDK source code](https://github.com/raspberrypi/pico-sdk)
- [Raspberry Pi Pico SDK examples](https://github.com/raspberrypi/pico-examples)
- [pico-extras](https://github.com/raspberrypi/pico-extras)
- [RP2040 datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) (pdf)
- [picotool](https://github.com/raspberrypi/picotool)

Lingua Franca
- Introduction
- 

Textbook
- Memory Architecture
- Embedded Processors

### Exercises
1. TODO
2. TODO
3. TODO

## Setup
One challenge of working with embedded systems is installing tooling. To create a reproducible unix shell environment that installs all required dependency applications, we use the nix package manager. Install [nix](https://nixos.org/download.html) first for your preferred platform. There is support for windows (wsl), macos and linux. 

After installation, run the following in the shell to enable the experimental nix flakes feature.

``` bash
mkdir -p ~/.config/nix
echo "experimental-features = nix-command flakes" >> ~/.config/nix/nix.conf
```

To launch the lf-pico shell environment, run the following in the root of the lf-pico repository:

```bash
nix develop
```

This should automatically download and install specific revisions of the gcc-arm toolchain, openocd and picotool. These packages will be required compiling, flashing and debugging C code for the RP2040.

## Blink
A common "Hello, World" application for embedded platforms is the blink application which periodically flashes an LED connected on a GPIO pin of the controller. Many of the low level instructions required to interact with the GPIO peripheral are abstracted using the [pico-sdk](https://github.com/raspberrypi/pico-sdk/tree/master) C/C++ library. Using the gcc-arm toolchain, the library provides cmake support for generating binaries for the rp2040.  More details [here](./Pico-SDK-Primer).

We will also introduce the Lingua Franca (LF) coordination framework as a high level scheduling framework. The framework emphasizes modeling computation as a network of concurrent reactor interactions. Reactors are similar to [actors](https://en.wikipedia.org/wiki/Actor_model) but also order simultaneous input reactions and timestamp messages. This allows for highly reproducible and testable code. More details [here](./Lingua-Franca-Primer)

To start, build the `src/Blink.lf` example using the following command. This will invoke the LF compiler which generates C sources from the LF file and builds elf, uf2 and hex binaries for the rp2040.
``` shell
lfc src/Blink.lf
```

## Flashing
Before flashing the binary to your rp2040 based board, the board must be placed into ``BOOTSEL`` mode. 
- On a regular Raspberry Pi Pico this can be entered by holding the ``RESET`` button while connecting the board to the host device. 
- The 3PI+ robot can enter ``BOOTSEL`` mode by holding the ``B`` button and pressing the ``RESET`` button while connected through usb.
The picotool application installed in the nix shell is an easy way to interact with boards.
With the application you can check what programs are currently flashed and can directly load program binaries.
Run the following to load the Blink application on to your board.

``` shell
picotool load bin/Blink.elf
```

TODO : Explanation bubble on elf files
TODO : Bootloaders
TODO : Flash 


## Debugging
Debugging is done using a secondary RPI pico board flashed with the picoprobe firmware.
This [thesis](https://openocd.org/files/thesis.pdf) dedicated to the development of the open-ocd software contains a good overview of the problems with debugging embedded platforms.
For this reason, openocd runs on the host device and uses different hardware debug protocols to interface with gdb, the gnu debugger. The debugging frontend can be changed,
and for use with vscode, a simple run configuration must be provided.

Flash the picoprobe firmware from [here](https://github.com/raspberrypi/picoprobe/releases/download/picoprobe-cmsis-v1.02/picoprobe.uf2) using picotool on the RPI Pico device that will be used
as the debugger. The wiring diagram here shows what pins to connect in order to debug the 3pi robot.
TODO: diagram

Run openocd to start the debugging server and load a specific elf file. This will create a gbd server that can be connected to. 

