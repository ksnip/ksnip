#!/bin/bash

cd kColorPicker
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLE=OFF
make && make install
cd ../..
cd kImageAnnotator
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLE=OFF
make && make install
cd ../..