#!/bin/bash

echo "--> Install latest version of kImageAnnotator"
git clone --depth 1 git://github.com/ksnip/kImageAnnotator

cd kImageAnnotator || exit
mkdir build && cd build || exit
cmake .. -G"${1}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -DBUILD_EXAMPLE=OFF -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}" -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES="${INSTALL_PREFIX}/include/kColorPicker"
make VERBOSE=1 && make install