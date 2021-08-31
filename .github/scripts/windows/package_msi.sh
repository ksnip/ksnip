#!/bin/bash

mkdir build && cd build

cpack --verbose
mv ksnip*.msi ${GITHUB_WORKSPACE}/ksnip-${VERSION}.msi
