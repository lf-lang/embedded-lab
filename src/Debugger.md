# Using a Debugger

## Debugging
To debug applications for RP2040 based boards, there exists a nice tool called [picoprobe](https://github.com/raspberrypi/picoprobe). This applications allows a Raspberry Pi Pico or RP2040 board to act as a [cmsis-dap](https://arm-software.github.io/CMSIS_5/DAP/html/index.html) device which interacts with the target device cortex cores through a [serial wire debug](https://wiki.segger.com/SWD) (swd) pin interface connection.

To get started, you'll need a secondary RP2040 based board and will need to flash the picoprobe [binaries](https://github.com/raspberrypi/picoprobe/releases/tag/picoprobe-cmsis-v1.02) linked here. The page contains pre-built firmware packages that can be flashed using picotool or copied to a `bootsel` mounted board. 

### Wiring
Once the **probe** device is prepared, wire it up to the **target** device as follows. The following is an example of a pico to pico connection and the pin numbers will differ from board to board.

```
Probe GND -> Target GND
Probe GP2 -> Target SWCLK
Probe GP3 -> Target SWDIO
Probe GP4 (UART1 TX) -> Target GP1 (UART0 RX)
Probe GP5 (UART1 RX) -> Target GP0 (UART0 TX)
```

*UART0* is the default uart peripheral used for stdio when uart is enabled for stdio in cmake. The target board uart is passed through the probe and can be accessed as usual using a serial port communication program on the host device connected to the probe.

### OpenOCD
[Open On-Chip Debugger](https://openocd.org/) is a program that runs on host machines called a `debug translator` It understands the swd protocol and is able to communicate with the probe device while exposing a local debug server for `GDB` to attach to.

After wiring, run the following command to flash a test binary of your choice
```
openocd -f interface/cmsis-dap.cfg -c "adapter speed 5000" -f target/rp2040.cfg -c "program bin/HelloPico.elf verify reset exit"
```
The above will specify the 
- probe type: `cmsis-dap`
- the target type: `rp2040`
- commands: the `-c` flag will directly run open ocd commands used to configure the flash operation. 
	- `adapter speed 5000` makes the transaction faster
	- `program <binary>.elf` specifies the `elf` binary to load into flash memory. These binaries specify the areas of where different parts of the program are loaded and the sizes.
	- `verify` reads the flash and checks against the binary
	- `reset` places the mcu in a clean initial state
	- `exit` disconnects openocd and the program will start to run on the board

### GDB
The gnu debugger is an open source program for stepping through application code. Here we use the remote target feature to connect to the exposed debug server provided by openocd. 

Make sure the intended program to be debugged on the **target** device has an accessible `.elf` binary that was built using the `Debug` option. To specify this property in an LF program, add the following to the program header:

```lf
target C {
    platform: {
        name: "RP2040",
        board: ...
    },
    build-type: "Debug"
    ...
}
```

First start openocd using the following command

```bash
openocd -f interface/cmsis-dap.cfg -c "adapter speed 5000" -f target/rp2040.cfg -s tcl
```

In a separate terminal window, run the following GDB session providing the elf binary. Since this binary was built using the `Debug` directive, it will include a symbol table that will be used for setting up breakpoints in gdb.

```bash
gdb <binary>.elf
```
Once the GDB environment is opened, connect to the debug server using the following. Each core exposes its own port but `core0` which runs the main thread exposes `3333`.

```bash
(gdb) target extended-remote localhost:3333
```

From this point onwards normal gdb functionality such as breakpoints, stack traces and register analysis can be accessed through various gdb commands.

### Visual Studio Code
Breakpoints can be placed in generated lingua franca project source code within **vscode**. 
As a part of the code generation process, each lfc generates a ``.vscode`` directory in the program ``src-gen`` folder. 
This is populated with settings to configure and run ``gdb``, ``openocd`` and ``cmake``.

Run the following after generating code for the desired lf program.
```bash
$ code src-gen/<program>/
```
In vscode, navigate to the run and debug tab on the left. A **Pico Debug** option should appear at the top as shown.

<img src="img/vscode-debug.png" alt="Debugging in VSCode"/>

Make sure the *picoprobe* is connected and wired as noted above and click run. The debugger should automatically break
at the ``main`` method of the application. Breakpoints can be visually inserted and other debugger options are accessible through
the IDE gui.


