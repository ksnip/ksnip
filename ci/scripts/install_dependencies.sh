#!/bin/bash

cd kColorPicker
mkdir build && cd build
cmake ..
make && make install
cd ../..
cd kImageAnnotator
mkdir build && cd build
cmake ..
make && make install
cd ../..