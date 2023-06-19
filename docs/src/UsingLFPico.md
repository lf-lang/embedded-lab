# Using lf-pico

## Generating Code from an LF Program

The `lf-pico/src` directory has some programs that you can compile and run on a RPi-Pico.  Assuming you are in the `lf-pico` root directory, for example, you can do this:

```
lfc src/Blink.lf
```

This will create a `src-gen/Blink` directory that contains the C source code that can be compiled and run on the RPi-Pico.

The above `lfc` command will also compile the generated code, creating a number of files, the most important of which is `Blink.uf2`, which can be uploaded to the RPi-Pico. 

## Uploading to the RPi-Pico

Plug your RPi-Pico into your USB port and start it in bootloader mode. On the Polulu robot, this is accomplished by holding thbe `B` button while pushing the `Reset` button. Two small green LEDs should be on, and a drive named something like `RPI-RP2` should appear mounted on your computer.

Drag the `Blink.uf2` file from `src-gen/Blink/build` into the `RPI-RP2` disk.
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

**FIXME**: This did not work for me. VS Code tried to use /usr/local/bin/arm-none-eabi-gcc-6.2.1, which did not exist for me. /usr/local/bin/arm-none-eabi-gcc does exist.

**TODO**: Add instructions on how to analyze and automatically flash binaries using the pico-tool

## Debugging

**FIXME**: This is incomplete.

Use minicom to open a console terminal an interact with the pico.
TODO: doesnt work on the robot?
```
minicom -b 115200 -o -D /dev/ttyACM0
```
