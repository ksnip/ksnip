#!/bin/bash

cd build

echo "--------------"
ls -al "C:\Program Files\CMake\bin\""
echo "--------------"

rm ./*.nuspec

"C:\Program Files\CMake\bin\cpack.exe" --verbose
mv ksnip*.msi ${GITHUB_WORKSPACE}/ksnip-${VERSION}.msi
