#!/bin/bash

cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DVERSION_SUFIX=$VERSION_SUFFIX -DBUILD_NUMBER=$BUILD_NUMBER
make -j$(nproc)
make DESTDIR=appdir -j$(nproc) install ; find appdir/
mkdir appdir/usr/bin ; mv appdir/bin/ksnip ./appdir/usr/bin/ ; rm -r ./appdir/bin
unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -bundle-non-qt-libs
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage -extra-plugins=iconengines,imageformats