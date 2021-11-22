#!/bin/bash

mkdir packageDir
mv build/src/ksnip*.exe packageDir/ksnip.exe

windeployqt.exe --no-opengl-sw --no-system-d3d-compiler --release packageDir/ksnip.exe

cp build/translations/ksnip_*.qm ./packageDir/translations/
cp kImageAnnotator/build/translations/kImageAnnotator_*.qm ./packageDir/translations/

cp "${OPENSSL_DIR}"/*.dll ./packageDir/

cp "${COMPILE_RUNTIME_DIR}"/*.dll ./packageDir/

7z a ksnip-${VERSION}-windows.zip ./packageDir/*
