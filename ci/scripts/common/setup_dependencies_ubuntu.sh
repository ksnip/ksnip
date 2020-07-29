#!/bin/bash

echo "--> Install Extra CMake Modules"
git clone git://github.com/KDE/extra-cmake-modules
cd extra-cmake-modules
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
make && sudo make install
cd ../..

echo "--> Install kColorPicker"
cd kColorPicker
mkdir build && cd build
cmake .. -DBUILD_EXAMPLE=OFF -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
make && sudo make install
cd ../..

echo "--> Install kImageAnnotator"
cd kImageAnnotator
mkdir build && cd build
cmake .. -DBUILD_EXAMPLE=OFF -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
make && sudo make install
cd ../..