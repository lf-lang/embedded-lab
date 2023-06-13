#!/bin/bash
# initial setup script for lf-pico
# to avoid the use of submodules and allow for users to downlaod pico-sdk
# and other tools to other repos, checks global path and adds to path

# install deps
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib

ROOT_DIR=$PWD
echo $ROOT_DIR

# clone pico-sdk
if [[ -z "${PICO_SDK_PATH}" ]]; then
    echo "cloning pico-sdk"
    git clone -b develop "git@github.com:raspberrypi/pico-sdk.git" ./lib/pico-sdk/
    cd ./lib/pico-sdk
    git submodule update --init
    echo "export PICO_SDK_PATH=$ROOT_DIR/lib/pico-sdk" >> ~/.bashrc
    source ~/.bashrc
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

cd $ROOT_DIR
cp ./tmp/picoprobe/build/picoprobe.uf2 ./picoprobe.uf2

# setup pico-tool
rm -rf ./tmp/


