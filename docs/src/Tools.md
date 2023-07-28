# 1. Tools and Environments
The purpose of this lab exercise is to familiarize you with the hardware and software used for embedded software programming. This lab exercise assumes you have followed the [Installation instructions](./Installation.md).  The [Resources](./Resources.md) and [Acronyms](./Acronyms.md) pages will also prove particularly useful.

Embedded systems often have limited resources and interaction methods and hence require a different approach for programming.
Their microprocessors often have no operating system, and are therefore called "bare metal" or "bare iron" machines.
They often have no keyboard or display connected to them, which can make debugging your programs challenging.
And they often have limited networking capability.
These lab exercises will help you develop the capability to build sophisticated programs for such embedded systems.

In this lab exercise, you will learn to interact with a particular microcontroller, a [Raspberry Pi RP2040](https://en.wikipedia.org/wiki/RP2040)
on the [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86). 
The RP2040 microcontroller is a low cost dual-core chip designed by the [Raspberry Pi Foundation](https://www.raspberrypi.org) in association with [Broadcom](https://www.broadcom.com).
Each core implements the [ARM Cortex-M0+](https://en.wikipedia.org/wiki/ARM_Cortex-M#Cortex-M0+) instruction set and is clocked at 133 MHz.
The same RP2040 microprocessor is also available on the low-cost [Raspberry Pi Pico board](https://en.wikipedia.org/wiki/Raspberry_Pi#Raspberry_Pi_Pico), but this board does not have the sensors and actuators of the Pololu robot, so you will need the robot to be able to complete all the exercises.
See the [Raspberry Pi Wikipedia page](https://en.wikipedia.org/wiki/Raspberry_Pi) for more background on this family of microcontrollers.

### Hardware

The [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86) looks like this from the top and bottom:

<img src="img/0J12017.700.jpg" alt="Pololu 3pi+ 2040 robot"/>

<img src="img/0J12018.700.jpg" alt="Pololu 3pi+ 2040 robot"/>

The robot is designed to be extended with additional hardware.  The available electrical interfaces are shown below:

<img src="img/0J12020.1000.jpg" alt="Pololu 3pi+ 2040 robot"/>

The pins GP24, GP27, GP28, and GP29 are free I/O pins that are not used for anything on the 3pi+ 2040. Each of these pins is accessible on the mid expansion header, and can be used as a general purpose input, digital output, or PWM output. Three of the pins (GP27, GP28, and GP29) can be used as analog inputs.

### Software

The robot can be programmed in Python (using [MicroPython](https://micropython.org)) or in C. In these lab exercises, we will be programming in C to gain more direct experience with the boundary between software and hardware. The robot runs no operating system, so when you load a C program onto it, that is the only software running.

As is typical in embedded software development, the software you will write will depend on one or more layers of toolkits provided by the various companies involved in the product:

1. The lowest level is the [ARM Cortex-M0+](https://en.wikipedia.org/wiki/ARM_Cortex-M#Cortex-M0+) instruction set, which you will not use directly in these labs. To use it directly, you would write your code in the ARMv6 assembly language.
2. The next level is to use the C language together with a [cross compiler](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) provided by ARM, Ltd. A cross compiler is a compiler that runs on a host machine (a Windows, Mac, or Linux machine) and produces machine code to be loaded onto the microcontroller.  Writing programs in C is much easier than in assembly language.
3. The [Raspberry Pi Pico SDK](https://www.raspberrypi.com/documentation/pico-sdk/) is a collection of C functions designed for use with the RP2040 on the Pico board. Although the robot is not identical to the Pico board, many of these C functions work unchanged with the robot.  Moreover, the develpment toolchain we will use is the same (cmake for building and picotool for loading onto the processor).
4. The [Robot library](https://github.com/pololu/pololu-3pi-2040-robot/tree/master/c) provided by Pololu provides additional C functions that are customized to the particular board design on the robot. These functions provide convenient interfaces to the various sensors and actuators on the robot.
5. [Lingua Franca](https://lf-lang.org) is a coordination language for designing and composing software components.  In these lab exercises, we will use its [C target](https://www.lf-lang.org/docs/handbook/target-language-details?target=c) and a small library of pre-defined components called **reactors** that offer convenient access to certain robot features and examples on which you can base your own code.
6. [CMake](https://en.wikipedia.org/wiki/CMake) is a build tool that manages dependencies. Nearly any program you build will depend on other programs and libraries and maintaining these dependencies can be very tedious. CMake supports encoding the dependencies in a way that makes it more likely that your code will compile even when put on a different computer or with a different filesystem organization.

### Development Tools

For developing C and Lingua Franca programs, we recommend using [Visual Studio Code](https://en.wikipedia.org/wiki/Visual_Studio_Code) (**VS Code**), an integrated development environment (**IDE**) from Microsoft.
Three VS Code extensions will prove particularly useful, the [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools), the
[Lingua Franca extension](https://www.lf-lang.org/docs/handbook/code-extension), and
[CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools),
all available from the [Visual Studio Marketplace](https://marketplace.visualstudio.com).
The VS Code extension for Lingua Franca has a particularly useful feature where it automatically generates a diagram showing the structure of your program, as shown below:

<img src="img/VSCodeExtension.png" alt="VS Code extension for Lingua Franca"/>

## 1.1 Prelab

### Exercises
1. TODO
2. TODO
3. TODO

## 1.2 Exercise: A First C Program

First, check your installation has been done correctly. One of the side effects of the installation is to define an environment variable called `PICO_SDK_PATH` that points to the root location of the RPi-Pico SDK. Check it:

```
$ echo $PICO_SDK_PATH
/Users/eal/git/lf-pico/pico/pico-sdk
```

You may wish to look at the README file in that directory.
We will now compile and load an example C program onto the robot.
We do this two different ways, using the command line and using an IDE.

### Using the Command Line

First, find the pico-examples directory and make it your current working directory:

```bash
   cd lf-pico/pico/pico-examples
```

(**NOTE:** `lf-pico` here and everywhere that follows is the location of your clone of the [lf-pico repository](https://github.com/lf-lang/lf-pico)).

Make a blank `build` directory and use it to compile all the examples:

```bash
    mkdir build
    cd build
    cmake ../
    make
```

This should result in a rather lengthy output.
When it finally finishes, each of the subdirectories of the `build` directory will contain binary files that you can load onto the robot.

Connect the robot to the USB port of your host computer.
Before flashing the binary to your RP2040 based board, the board must be placed into ``BOOTSEL`` mode.  On the Pololu 3Pi+ robot, hold the `B` button and press `RESET`.
(On a Raspberry Pi Pico, hold the `RESET` button while connecting the board to the host.)
You can then use the `picotool` to load and execute one of the sample programs:


```
    picotool load -x blink/blink.elf
```

The `-x` option directs the robot to execute the code after loading it.
This will result in an LED blinking on the robot.
The loaded code will persist on the robot until the next time it is put in `BOOTSEL` mode and loaded with a new program.
You can disconnect the robot and use the power button to start it running on battery power.

### Using VS Code

Next we will repeat the exercise, but this time using VS Code rather than the command line to compile the code.
Under the hood, VS Code uses the CMake Tools extension to achieve the same process.

Start VS Code in your root lf-pico directory:

```
   $ cd lf-pico/pico/pico-examples
   $ code .
```

This will likely result in a popup appearing as follows:

<img src="img/SelectAKit.png" alt="Select a kit"/>

You should select the arm-none-eabi kit. If you do not see one, select "Scan for kits". It you do not see the popup above, click on "No kit selected" on bottom blue bar.  **NOTE:** You may need to make sure that CMake Tools is the Configuration Provider. Select View->Command Palette in the menu and begin typing "C/C++ Change Configuration Provider" until you see this:

<img src="img/ConfigurationProvider.png" alt="Configuration Provider" width="60%"/>

If CMake Tools is not available, then the cmake extension is not installed in VS Code.

If all goes well, VS Code will have compiled all the examples, and you see output something like this:

<img src="img/CompileOutput.png" alt="Compile output"/>

VS Code has run CMake, but it has not yet compiled the example programs.
To compile them, click on the "Build" button in the blue bar at the bottom.
If you run the build on the command line as above, then this time it should not take too long.

When you see "Build finished with exit code 0," then you can load the code onto the robot using picotool.  To do this from within VS Code, select the Terminal tab in the Output subwindow and issue the load command as above:

```
    picotool load -x build/blink/blink.elf
```

Make sure the robot is in `BOOTSEL` mode before doing this.

### Examining the C Program

Find and examine the C program `blink.c`. How is it controlling the timing of the blinking of the LED?

**Checkoff:** Verify that the VS Code and command-line mechanisms are working.
Explain how the timing of the blinking of the LED is controlled.


## 1.3 Exercise: A First Lingua Franca Program



### Blink
A common "Hello, World" application for embedded platforms is the blink application which periodically flashes an LED connected on a GPIO pin of the controller. Many of the low level instructions required to interact with the GPIO peripheral are abstracted using the [pico-sdk](https://github.com/raspberrypi/pico-sdk/tree/master) C/C++ library. Using the gcc-arm toolchain, the library provides cmake support for generating binaries for the rp2040.  More details [here](./Pico-SDK-Primer).

We will also introduce the Lingua Franca (LF) coordination framework as a high level scheduling framework. The framework emphasizes modeling computation as a network of concurrent reactor interactions. Reactors are similar to [actors](https://en.wikipedia.org/wiki/Actor_model) but also order simultaneous input reactions and timestamp messages. This allows for highly reproducible and testable code. More details [here](./Lingua-Franca-Primer)

To start, build the `src/Blink.lf` example using the following command. This will invoke the LF compiler which generates C sources from the LF file and builds elf, uf2 and hex binaries for the rp2040.
``` shell
lfc src/Blink.lf
```



## Debugging
Debugging is done using a secondary RPI pico board flashed with the picoprobe firmware.
This [thesis](https://openocd.org/files/thesis.pdf) dedicated to the development of the open-ocd software contains a good overview of the problems with debugging embedded platforms.
For this reason, openocd runs on the host device and uses different hardware debug protocols to interface with gdb, the gnu debugger. The debugging frontend can be changed,
and for use with vscode, a simple run configuration must be provided.

Flash the picoprobe firmware from [here](https://github.com/raspberrypi/picoprobe/releases/download/picoprobe-cmsis-v1.02/picoprobe.uf2) using picotool on the RPI Pico device that will be used
as the debugger. The wiring diagram here shows what pins to connect in order to debug the 3pi robot.
TODO: diagram

Run openocd to start the debugging server and load a specific elf file. This will create a gbd server that can be connected to. 

