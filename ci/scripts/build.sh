#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DVERSION_SUFIX=$VERSION_SUFFIX -DBUILD_NUMBER=$BUILD_NUMBER
    make -j$(nproc)
    make DESTDIR=appdir -j$(nproc) install ; find appdir/
    mkdir appdir/usr/bin ; mv appdir/bin/ksnip ./appdir/usr/bin/ ; rm -r ./appdir/bin
    wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
    chmod a+x linuxdeployqt-continuous-x86_64.AppImage
    unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
    ./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -bundle-non-qt-libs
    ./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage -extra-plugins=iconengines,imageformats
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker exec build-container bash -c "source ci/scripts/create_deb.sh"
    mv ksnip_*.deb ksnip-$VERSION-amd64.deb
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker exec build-container bash -c "source ci/scripts/create_rpm.sh"
    sudo chown -R 2000:2000 ksnip-$VERSION_NUMBER
    mv ksnip-$VERSION_NUMBER/RPMS/x86_64/ksnip-*.rpm ksnip-$VERSION-x86_64.rpm
elif [[ "${BUILD_TYPE}" == "exe" ]]; then
    mkdir build && cd build
    cmake .. -G"NMake Makefiles" -DCMAKE_CXX_COMPILER=cl -DVERSION_SUFIX=$VERSION_SUFFIX -DBUILD_NUMBER=$BUILD_NUMBER -DCMAKE_BUILD_TYPE=Release
    nmake
    cd ..
    mv build/src/ksnip*.exe ksnip-$VERSION-x86_64.exe
fi
