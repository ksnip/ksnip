#!/bin/bash

mkdir packageDir
mv build/src/ksnip*.exe packageDir/ksnip.exe

windeployqt.exe --no-opengl-sw --no-system-d3d-compiler --no-compiler-runtime --release packageDir/ksnip.exe

cp build/translations/ksnip_*.qm ./packageDir/translations/
cp kImageAnnotator/build/translations/kImageAnnotator_*.qm ./packageDir/translations/
cp open_ssl/{libeay32.dll,ssleay32.dll} ./packageDir/ || true

echo "---------------"
curl -L https://de.dll-files.com/download/7b92a6cb5d2cad407c457ab12d2b211d/msvcp140.dll.html?c=L20zYStrQm0zU1FDekpvTTdxRldJZz09 --output msvcp140.dll
curl -L https://de.dll-files.com/download/3b22b2ec303b0721827dd768c87df6ed/vcruntime140_1.dll.html?c=aENVeFR6N21JY1VvT3JKNHNwckhndz09 --output vcruntime140_1.dll
cp msvcp140.dll ./packageDir/ || true
cp vcruntime140_1.dll ./packageDir/ || true
echo "---------------"

7z a ksnip-${VERSION}-windows.zip ./packageDir/*
