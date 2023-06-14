#!/bin/bash

LIB_PATH=$PWD/../lib
echo $LIB_PATH
# TODO provide this path in the toml 
export PICO_SDK_PATH=$LIB_PATH/pico-sdk
export ROBOT_LIB_PATH=$LIB_PATH/robot_lib

# vscode settings
# TODO: lfc should handle this
cd ${LF_SOURCE_GEN_DIRECTORY}
mkdir .vscode
cp "../../platform/launch.json" "${LF_SOURCE_GEN_DIRECTORY}/.vscode"

#sudo service udev restart && sudo udevadm trigger

mkdir build
cd build
cmake ..
cmake --build .
#cmake -b build
#cmake --build .

# try to flash
# monitor on screen
