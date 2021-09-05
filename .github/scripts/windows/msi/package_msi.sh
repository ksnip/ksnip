#!/bin/bash

cd build

echo "--------------"
ls -al
echo "--------------"

rm ./*.nuspec

cpack --verbose
mv ksnip*.msi ${GITHUB_WORKSPACE}/ksnip-${VERSION}.msi
