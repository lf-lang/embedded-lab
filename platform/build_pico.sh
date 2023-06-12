#!/bin/bash

# vscode settings
cd ${LF_SOURCE_GEN_DIRECTORY}
mkdir .vscode
cp "../../platform/launch.json" "${LF_SOURCE_GEN_DIRECTORY}/.vscode"

#sudo service udev restart && sudo udevadm trigger

mkdir build
cd build
cmake ..
#cmake --build .
code ../
#cmake -b build
#cmake --build .

