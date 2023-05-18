#!/bin/bash

cd ${LF_SOURCE_GEN_DIRECTORY}
cp "../../platform/CMakeLists.txt" "${LF_SOURCE_GEN_DIRECTORY}"
cp "../../platform/CMakeLists_platform.txt" "${LF_SOURCE_GEN_DIRECTORY}/core/platform/CMakeLists.txt"
cp "../../platform/Platform.cmake" "${LF_SOURCE_GEN_DIRECTORY}/core/platform"

cp "../../platform/lf_pico_support.c" "${LF_SOURCE_GEN_DIRECTORY}/core/platform"

cp "../../platform/lf_pico_support.h" "${LF_SOURCE_GEN_DIRECTORY}/include/core/platform"
cp "../../platform/platform.h" "${LF_SOURCE_GEN_DIRECTORY}/include/core"

mkdir build
cd build
cmake ..
cmake --build .

