#!/bin/bash

echo "--> Install latest version of kColorPicker"
git clone --depth 1 git://github.com/ksnip/kColorPicker

cd kColorPicker || exit
mkdir build && cd build || exit
cmake .. -DCMAKE_BUILD_TYPE="${ENV_BUILD_TYPE}" -DBUILD_EXAMPLE=OFF -DCMAKE_INSTALL_PREFIX="${ENV_INSTALL_PREFIX}"
make && sudo make install