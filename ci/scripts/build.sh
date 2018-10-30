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
    docker run -v `pwd`:`pwd` -w `pwd` -it ubuntu:17.10 bash -c "source ci/scripts/create_deb.sh"
    mv ksnip_*.deb ksnip-$VERSION-amd64.deb
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker run -v `pwd`:`pwd` -w `pwd` -it opensuse:42.2 bash -c "source ci/scripts/create_rpm.sh"
    sudo chown -R 2000:2000 ksnip-1.5.0
    mv ksnip-1.5.0/RPMS/x86_64/ksnip-*.rpm ksnip-$VERSION-x86_64.rpm
fi
