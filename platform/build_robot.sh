#!/bin/bash

# copy robot library files to src-gen
ROOT_PATH=$PWD/../
echo $ROOT_PATH

# copy lib sources
cp -r "$ROOT_PATH/lib/" "${LF_SOURCE_GEN_DIRECTORY}/lib/"
#sudo service udev restart && sudo udevadm trigger