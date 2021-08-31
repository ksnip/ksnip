#!/bin/bash

if [[ -z "${GITHUB_TAG}" ]]; then
    echo "Building ksnip with latest version of kColorPicker"

    git clone --depth 1 git://github.com/ksnip/kColorPicker
else
    KCOLORPICKER_VERSION=$(grep "set.*KCOLORPICKER_MIN_VERSION" CMakeLists.txt | egrep -o "${VERSION_REGEX}")
    echo "Building ksnip with kColorPicker version ${KCOLORPICKER_VERSION}"

    git clone --depth 1 --branch "v${KCOLORPICKER_VERSION}" git://github.com/ksnip/kColorPicker
fi

cd kColorPicker || exit
mkdir build && cd build || exit
cmake .. -G"${CMAKE_GENERATOR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -DBUILD_EXAMPLE=OFF -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}"
${MAKE_BINARY} && ${MAKE_BINARY} install