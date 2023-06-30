# Chapter 1
## Tools and Environments
This chapter will overview the different tool required for software development on embedded
systems. Microcontrollers often have limited resources and interaction methods due to being headless devices. The tasks will introduce a common development workflows for these
platforms.

This section will explore the RP2040 microcontroller, a low cost dual-core arm based chip with various useful and unique hardware peripherals. The chip is embedded in the popular Raspberry Pi Pico and is tailored for education.

## Prelab
### Resources
Here are some documents from which this chapter was derived from that detail the various components of the setup.

Build System
- Bash Scripting
- Nix
- Command Line

RP2040
- Datasheet
- Getting Started Pico
- Pico SDK

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

## Repo
This book uses the [lf-pico](https://github.com/lf-lang/lf-pico) repository as a framework that contains setup scripts and examples for the applications described. Make sure the copy of lf-pico is up to date with the current documentation. Clone or navigate to the repository, pull the latest and compare the commit sha.
```
git clone https://github.com/lf-lang/lf-pico.git
git pull
git log -1
```
latest commit sha: 9fc422f05d934fdc45b7ebace22cfdaa12b3c3f9

## Setup
One challenge of working with embedded systems is installing tooling. To create a reproducible unix shell environment that installs all required dependency applications, we use the nix package manager. Install [nix](https://nixos.org/download.html) first for your preferred platform. There is support for windows (wsl), macos and linux. 

After installation, run the following in the shell to enable the experimental nix flakes feature.
``` bash
mkdir -p ~/.config/nix
echo "experimental-features = nix-command flakes" >> ~/.config/nix/nix.conf
```

To launch the lf-pico shell environment, run the following in the root of the lf-pico repository. 
```bash
nix develop
```

This should automatically download and install specific revisions of the gcc-arm toolchain, openocd and picotool. These packages will be required compiling, flashing and debugging C code for the RP2040.

## Blink
A common "Hello, World" application for embedded platforms is the blink application which periodically flashes an LED connected on a GPIO pin of the controller. Many of the low level instructions required to interact with the GPIO peripheral are abstracted using the [pico-sdk](https://github.com/raspberrypi/pico-sdk/tree/master) C/C++ library. Using the gcc-arm toolchain, the library provides cmake support for generating binaries for the rp2040.  More details [here](#Pico-SDK).

We will also introduce the Lingua Franca (LF) coordination framework as a high level scheduling framework. The framework emphasizes modeling programs as a network of concurrent reactor interactions. Reactors are similar to [actors](https://en.wikipedia.org/wiki/Actor_model) but additionally order simultaneous input reactions and timestamp messages. This allows for highly reproducible and testable code. More details [here](#Lingua-Franca)

To start, build the `src/Blink.lf` example using the following command. This will invoke the LF compiler which generates C sources from the LF file and builds elf, uf2 and hex binaries for the rp2040.
``` shell
lfc src/Blink.lf
```

## Pico-SDK
hello

## Lingua-Franca
mention the tradeoff between reactivity consistency