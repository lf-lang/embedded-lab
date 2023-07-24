# Using lf-pico

## Generating Code from an LF Program

The `lf-pico/src` directory has some programs that you can compile and run on a RPi-Pico.  Assuming you are in the `lf-pico` root directory, for example, you can do this:

```
lfc src/Blink.lf
```

This will create a `src-gen/Blink` directory that contains the C source code that can be compiled and run on the RPi-Pico.

The above `lfc` command will also compile the generated code, creating a number of files, the most important of which is `Blink.uf2`, which can be uploaded to the RPi-Pico. 

## Uploading to the RPi-Pico

Plug your RPi-Pico into your USB port and start it in bootloader mode. On the Pololu robot, this is accomplished by holding thbe `B` button while pushing the `Reset` button. Two small green LEDs should be on, and a drive named something like `RPI-RP2` should appear mounted on your computer.

To flash and execute the compiled program:

```
picotool load -x bin/Blink.elf
```

Alternatively, drag the `Blink.uf2` file from `src-gen/Blink/build` into the `RPI-RP2` disk.
The Blink program should immediately start running.
It blinks the yellow LED on the Pololu robot five times per second.

## Using VS Code

After generating the C source code using `lfc`, if you have installed VS Code, then you can use VS Code to examine, compile, and debug the generated code. Just open VS Code, pointing it to the appropriate `src-gen` directory. For example, if you are in `lf-pico` root:

```
code src-gen/Blink
```

You may see a popup like this:

![Select a Kit](img/SelectAKit.png)

You should choose the GCC for arm-none-eabi option.
If the vscode instance was setup properly, all necessary plugins will be installed
and cmake will automatically build. 

**TODO**: Add instructions on how to analyze and automatically flash binaries using the pico-tool

## Debugging

Run a program that has usb enabled.
Search for a device that mentions `usb`:

```
$ ls /dev/*usb*
/dev/cu.usbmodem14201	/dev/tty.usbmodem14201
```

Then start `screen` with that device and the baud rate:

```
screen /dev/cu.usbmodem14201 115200
```

To exit screen, type Control-A k (for kill).


**FIXME**: This is incomplete.

Use minicom to open a console terminal an interact with the pico.
TODO: doesnt work on the robot?
```
minicom -b 115200 -o -D /dev/ttyACM0
```
