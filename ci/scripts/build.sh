#!/bin/bash

if [[ "${BINARY_TYPE}" == "AppImage" ]]; then
    source ci/scripts/appImage/build_appImage.sh
elif [[ "${BINARY_TYPE}" == "deb" ]]; then
    docker exec build-container bash -c "source ci/scripts/deb/build_deb.sh"
    mv ksnip_*.deb ksnip-${VERSION}.deb
elif [[ "${BINARY_TYPE}" == "rpm" ]]; then
    docker exec build-container bash -c "source ci/scripts/rpm/build_rpm.sh"
    sudo chown -R 2000:2000 ksnip-${VERSION_NUMBER}
    mv ksnip-${VERSION_NUMBER}/RPMS/x86_64/ksnip-*.rpm ksnip-${VERSION}.rpm
elif [[ "${BINARY_TYPE}" == "exe" ]]; then
    mkdir build && cd build
    cmake .. -G"NMake Makefiles" -DCMAKE_CXX_COMPILER=cl -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER} -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
    nmake
    cd ..

    echo "--> Package Windows"
    mkdir packageDir
    mv build/src/ksnip*.exe packageDir/ksnip.exe
    windeployqt.exe packageDir/ksnip.exe
    cp build/translations/ksnip_*.qm ./packageDir/translations/
    cp kImageAnnotator/build/translations/kImageAnnotator_*.qm ./packageDir/translations/
    cp /c/openssl/libeay32.dll ./packageDir/
    cp /c/openssl/ssleay32.dll ./packageDir/

    7z a ksnip-${VERSION}-windows.zip ./packageDir/*
elif [[ "${BINARY_TYPE}" == "app" ]]; then
    mkdir build && cd build
    cmake .. -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER} -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES=/usr/local/include/kImageAnnotator
    make
    cd ..

    echo "--> Package MacOS"
    mv build/src/ksnip*.app ksnip.app
    cp build/translations/ksnip_*.qm ./ksnip.app/Contents/Resources/
    cp build/translations/kImageAnnotator_*.qm ./ksnip.app/Contents/Resources/
    macdeployqt ksnip.app -dmg -sign-for-notarization="${APPLE_DEV_IDENTITY}"
    mv ksnip.dmg ksnip-${VERSION}.dmg

    echo "--> Notarize MacOS package"
    chmod +x ci/scripts/app/notarize_osx_dmg_package.sh;
    ./ci/scripts/app/notarize_osx_dmg_package.sh;
fi
