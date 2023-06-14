#!/bin/bash
# initial setup script for lf-pico
# to avoid the use of submodules and allow for users to downlaod pico-sdk
# and other tools to other repos, checks global path and adds to path

# install deps
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib

ROOT_DIR=$PWD
echo $ROOT_DIR
# TODO: check root dir

# clone pico-sdk
if [[ -z "${PICO_SDK_PATH}" ]]; then
    echo "init pico-sdk"
    # top level init
    git submodule update --init
    cd ./lib/pico-sdk
    git submodule update --init
    # add to env for script
    export PICO_SDK_PATH="$ROOT_DIR/lib/pico-sdk"
else
    echo "found in path"
fi

# setup probe binary
cd $ROOT_DIR
mkdir tmp

git clone git@github.com:raspberrypi/picoprobe.git ./tmp/picoprobe 
cd ./tmp/picoprobe/
git submodule update --init --recursive
mkdir build/
cd build
cmake ..
cmake --build .

# setup picotool binary
cd $ROOT_DIR
sudo apt install build-essential pkg-config libusb-1.0-0-dev cmake
git clone git@github.com:raspberrypi/picotool.git ./tmp/picotool 
cd ./tmp/picotool/
sudo cp udev/99-picotool.rules /etc/udev/rules.d/
mkdir build/
cd build
cmake ..
cmake --build .


cd $ROOT_DIR
cp ./tmp/picoprobe/build/picoprobe.uf2 ./picoprobe.uf2
cp ./tmp/picotool/build/picotool ./picotool
#rm -rf ./tmp/


