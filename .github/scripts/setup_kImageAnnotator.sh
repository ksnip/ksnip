#!/bin/bash

if [[ -z "${GITHUB_TAG}" ]]; then
    echo "Building ksnip with latest version of kImageAnnotator"

    git clone --depth 1 git://github.com/ksnip/kImageAnnotator
else
    KIMAGEANNOTATOR_VERSION=$(grep "set.*KIMAGEANNOTATOR_MIN_VERSION" CMakeLists.txt | egrep -o "${VERSION_REGEX}")
    echo "Building ksnip with kImageAnnotator version ${KIMAGEANNOTATOR_VERSION}"

    git clone --depth 1 --branch "v${KIMAGEANNOTATOR_VERSION}" git://github.com/ksnip/kImageAnnotator
fi

cd kImageAnnotator || exit
mkdir build && cd build || exit
cmake .. -G"${CMAKE_GENERATOR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -DBUILD_EXAMPLE=OFF -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}" -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES="${INSTALL_PREFIX}/include"
${MAKE_BINARY} && ${MAKE_BINARY} install