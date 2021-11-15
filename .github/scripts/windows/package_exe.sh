#!/bin/bash

mkdir packageDir
mv build/src/ksnip*.exe packageDir/ksnip.exe

windeployqt.exe --no-opengl-sw --no-system-d3d-compiler --no-compiler-runtime --release packageDir/ksnip.exe

cp build/translations/ksnip_*.qm ./packageDir/translations/
cp kImageAnnotator/build/translations/kImageAnnotator_*.qm ./packageDir/translations/
cp ${OPENSSL_DIR}/{libcrypto-1_1.dll,libssl-1_1.dll} ./packageDir/

echo "---------------"
curl -L https://github.com/ksnip/dependencies/raw/master/windows/compileRuntime.zip --output compileRuntime.zip

7z x compileRuntime.zip -o"compileRuntime"

cp compileRuntime/{msvcp140.dll,vcruntime140.dll} ./packageDir/
echo "---------------"

7z a ksnip-${VERSION}-windows.zip ./packageDir/*
