# lf-pico
support for lf on the raspberry pi pico using the pico-sdk

## Usage
tooling here to build and flash a program through the makefile
using picoprobe to flash

add the pico-sdk to a global cmake flag
allows for easier cmake additions in headers and avoid relative

after the setting up the pico-probe on your system run lfc src/"file".lf. "file" is the name of the lingua franca program you'd like to run. The custom build script will open a new vscode instance and run cmake to generate the build files for the project.