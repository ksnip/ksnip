#!/bin/bash

echo "--> Build and Install kColorPicker"
cd kColorPicker
mkdir build && cd build
cmake .. -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DBUILD_EXAMPLE=OFF -DCMAKE_CXX_COMPILER=cl
nmake && nmake install
cd ../..

echo "--> Build and Install kImageAnnotator"
cd kImageAnnotator
mkdir build && cd build
cmake .. -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DBUILD_EXAMPLE=OFF -DCMAKE_CXX_COMPILER=cl
nmake && nmake install
cd ../..

