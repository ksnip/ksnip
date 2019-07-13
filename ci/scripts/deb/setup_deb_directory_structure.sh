#!/bin/bash

echo "--> Create directory and copy everything we need to deliver"
mkdir ksnip-${VERSION_NUMBER}
cp -R CMakeLists.txt cmake/ desktop/ icons/ LICENSE README.md src/ translations/ ksnip-${VERSION_NUMBER}/
echo "--> Package source content"
tar -cvzf ksnip_${VERSION_NUMBER}.orig.tar.gz ksnip-${VERSION_NUMBER}/
echo "--> Copy source package to debian directory"
cp -R ci/debian ksnip-${VERSION_NUMBER}/
