#!/bin/bash
export BUILD_TYPE="Release"

echo "--> Install Extra CMake Modules"
cd extra-cmake-modules
git pull
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
make && sudo make install
cd ../..

echo "--> Install kColorPicker"
cd kColorPicker
git pull
mkdir build && cd build
cmake .. -DBUILD_EXAMPLE=OFF -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
make && sudo make install
cd ../..

echo "--> Install kImageAnnotator"
cd kImageAnnotator
git pull
mkdir build && cd build
cmake .. -DBUILD_EXAMPLE=OFF -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
make && sudo make install
cd ../..

