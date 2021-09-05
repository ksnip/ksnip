#!/bin/bash

cd build

"C:\Program Files\CMake\bin\cpack.exe" --verbose
mv ksnip*.msi ${GITHUB_WORKSPACE}/ksnip-${VERSION}.msi
