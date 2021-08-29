#!/bin/bash

mkdir packageDir
mv build/src/ksnip*.exe packageDir/ksnip.exe

windeployqt.exe packageDir/ksnip.exe

cp build/translations/ksnip_*.qm ./packageDir/translations/
cp kImageAnnotator/build/translations/kImageAnnotator_*.qm ./packageDir/translations/
cp open_ssl/{libeay32.dll,ssleay32.dll} ./packageDir/ || true

7z a ksnip-${VERSION}-windows.zip ./packageDir/*
