#!/bin/bash

echo "--> Install latest version of kImageAnnotator"
git clone --depth 1 git://github.com/ksnip/kImageAnnotator

cd kImageAnnotator || exit
mkdir build && cd build || exit
cmake .. -DCMAKE_BUILD_TYPE="${ENV_BUILD_TYPE}" -DBUILD_EXAMPLE=OFF -DCMAKE_INSTALL_PREFIX="${ENV_INSTALL_PREFIX}" -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES="${ENV_INSTALL_PREFIX}/include/kColorPicker"
make && sudo make install