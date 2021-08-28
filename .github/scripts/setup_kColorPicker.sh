#!/bin/bash

echo "--> Install latest version of kColorPicker"
git clone --depth 1 git://github.com/ksnip/kColorPicker

cd kColorPicker || exit
mkdir build && cd build || exit
${2} .. -G"${1}" -D CMAKE_CXX_FLAGS="-D_WIN32_WINNT=0x0A00" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -DBUILD_EXAMPLE=OFF -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}"
make && make install