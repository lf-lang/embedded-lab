# Using a Debugger

**FIXME:** This is undeveloped.

Debugging is done using a secondary RPI pico board flashed with the picoprobe firmware.
This [thesis](https://openocd.org/files/thesis.pdf) dedicated to the development of the open-ocd software contains a good overview of the problems with debugging embedded platforms.
For this reason, openocd runs on the host device and uses different hardware debug protocols to interface with gdb, the gnu debugger. The debugging frontend can be changed,
and for use with vscode, a simple run configuration must be provided.

Flash the picoprobe firmware from [here](https://github.com/raspberrypi/picoprobe/releases/download/picoprobe-cmsis-v1.02/picoprobe.uf2) using picotool on the RPI Pico device that will be used
as the debugger. The wiring diagram here shows what pins to connect in order to debug the 3pi robot.
TODO: diagram

Run openocd to start the debugging server and load a specific elf file. This will create a gbd server that can be connected to. 
