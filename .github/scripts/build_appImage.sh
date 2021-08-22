#!/bin/bash

echo "--> Build"
make DESTDIR=appdir -j$(nproc) install ; find appdir/

echo "--> Copy SSL libs to appDir"
mkdir -p appdir/usr/lib/
cp /lib/x86_64-linux-gnu/libssl.so.1.0.0 appdir/usr/lib/

echo "--> Copy kImageAnnotator translations to appDir"
mkdir -p appdir/usr/share/kImageAnnotator/
cp -r ${INSTALL_PREFIX}/share/kImageAnnotator/translations appdir/usr/share/kImageAnnotator/

echo "--> Package appImage"
unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
../linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -bundle-non-qt-libs
../linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage -extra-plugins=iconengines,imageformats
