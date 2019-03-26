#!/bin/bash

echo "--> Build "
cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER}
make DESTDIR=appdir -j$(nproc) install ; find appdir/
unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
echo "--> Package appImage"
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -bundle-non-qt-libs
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage -extra-plugins=iconengines,imageformats
