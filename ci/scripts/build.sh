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
    echo "--> cmake"
    cmake .. -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER} -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES=/usr/local/include/kImageAnnotator
    echo "--> make"
    make
    cd ..

    echo "--> Setup Certificates"
    chmod +x ci/scripts/app/add-osx-cert.sh;
    ./ci/scripts/app/add-osx-cert.sh;

    echo "--> Package MacOS"
    mkdir packageDir
    mv build/src/ksnip*.app packageDir/ksnip.app
    macdeployqt packageDir/ksnip.app -sign-for-notarization="${APPLE_DEV_IDENTITY}"
    cp build/translations/ksnip_*.qm ./packageDir/ksnip.app/Contents/Resources/
    cp build/translations/kImageAnnotator_*.qm ./packageDir/ksnip.app/Contents/Resources/
    sudo hdiutil create ksnip-${VERSION}.dmg -volname "Ksnip" -fs HFS+ -srcfolder packageDir/

    echo "--> Start Notatization process"
    sudo xcode-select -r
    xcrun altool -t osx -f ksnip-${VERSION}.dmg –primary-bundle-id org.ksnip.ksnip –notarize-app –username ${APPLE_DEV_USER} -password ${APPLE_DEV_PASS}
fi
