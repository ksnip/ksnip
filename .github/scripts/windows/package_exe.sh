#!/bin/bash

mkdir packageDir
mv build/src/ksnip*.exe packageDir/ksnip.exe

windeployqt.exe --no-opengl-sw --no-system-d3d-compiler --no-compiler-runtime --release packageDir/ksnip.exe

cp build/translations/ksnip_*.qm ./packageDir/translations/
cp kImageAnnotator/build/translations/kImageAnnotator_*.qm ./packageDir/translations/
cp ${OPENSSL_DIR}/{libeay32.dll,ssleay32.dll} ./packageDir/ || true

echo "---------------"
curl -L https://de.dll-files.com/download/7b92a6cb5d2cad407c457ab12d2b211d/msvcp140.dll.html?c=L20zYStrQm0zU1FDekpvTTdxRldJZz09 --output msvcp140.zip
curl -L https://de.dll-files.com/download/cfc08fca16c3647a42e78ef7556e4090/vcruntime140.dll.html?c=SHY4Z3V4WlZQZ2RzYWFnVHVsNFdVdz09 --output vcruntime140.zip

7z x msvcp140.zip || true
7z x vcruntime140.zip || true

cp msvcp140.dll ./packageDir/ || true
cp vcruntime140.dll ./packageDir/ || true
echo "---------------"

7z a ksnip-${VERSION}-windows.zip ./packageDir/*
