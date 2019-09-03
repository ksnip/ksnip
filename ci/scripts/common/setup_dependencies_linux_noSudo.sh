#!/bin/bash

echo "--> Build and Install kColorPicker"
cd kColorPicker
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DBUILD_EXAMPLE=OFF
make && make install
cd ../..

echo "--> Build and Install kImageAnnotator"
cd kImageAnnotator
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DBUILD_EXAMPLE=OFF
make && make install
cd ../..