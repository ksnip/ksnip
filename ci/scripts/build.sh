#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    source ci/scripts/appImage/build_appImage.sh
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker exec build-container bash -c "source ci/scripts/deb/build_deb.sh"
    mv ksnip_*.deb ksnip-$VERSION-amd64.deb
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker exec build-container bash -c "source ci/scripts/rpm/build_rpm.sh"
    sudo chown -R 2000:2000 ksnip-$VERSION_NUMBER
    mv ksnip-$VERSION_NUMBER/RPMS/x86_64/ksnip-*.rpm ksnip-$VERSION-x86_64.rpm
elif [[ "${BUILD_TYPE}" == "exe" ]]; then
    mkdir build && cd build
    cmake .. -G"NMake Makefiles" -DCMAKE_CXX_COMPILER=cl -DVERSION_SUFIX=$VERSION_SUFFIX -DBUILD_NUMBER=$BUILD_NUMBER -DCMAKE_BUILD_TYPE=Release
    nmake
    cd ..
    echo "--> Package Windows"
    mkdir packageDir
    mv build/src/ksnip*.exe packageDir/ksnip.exe
    windeployqt.exe packageDir/ksnip.exe
    7z a ksnip-$VERSION-windows-x86_64.zip ./packageDir/*
elif [[ "${BUILD_TYPE}" == "app" ]]; then
    mkdir build && cd build
    cmake .. -DVERSION_SUFIX=$VERSION_SUFFIX -DBUILD_NUMBER=$BUILD_NUMBER -DCMAKE_BUILD_TYPE=Release
    make && sudo make install
    cd ..

    echo "--> Package MacOS"
    mkdir packageDir
    mv build/src/ksnip*.app packageDir/ksnip.app
    sudo hdiutil create ksnip-$VERSION-x86_64.dmg -volname "Ksnip" -fs HFS+ -srcfolder packageDir/
fi
