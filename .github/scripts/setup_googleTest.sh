#!/bin/bash

git clone --depth 1 https://github.com/google/googletest
cd googletest || exit
mkdir build && cd build || exit
cmake .. -G"${CMAKE_GENERATOR}" -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}"
${MAKE_BINARY} && ${MAKE_BINARY} install