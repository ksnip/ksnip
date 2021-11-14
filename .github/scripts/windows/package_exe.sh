#!/bin/bash

mkdir packageDir
mv build/src/ksnip*.exe packageDir/ksnip.exe

echo "---------------"
find /c -name VCRUNTIME140_1.dll
echo "---------------"

windeployqt.exe --no-opengl-sw --no-system-d3d-compiler --compiler-runtime --release packageDir/ksnip.exe

cp build/translations/ksnip_*.qm ./packageDir/translations/
cp kImageAnnotator/build/translations/kImageAnnotator_*.qm ./packageDir/translations/
cp open_ssl/{libeay32.dll,ssleay32.dll} ./packageDir/ || true

7z a ksnip-${VERSION}-windows.zip ./packageDir/*
