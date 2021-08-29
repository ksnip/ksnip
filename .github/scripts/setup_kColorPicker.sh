#!/bin/bash

echo "--> Install latest version of kColorPicker"
git clone --depth 1 git://github.com/ksnip/kColorPicker

cd kColorPicker || exit
mkdir build && cd build || exit
cmake .. -G"${CMAKE_GENERATOR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -DBUILD_EXAMPLE=OFF -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}"
${MAKE_BINARY} && ${MAKE_BINARY} install