#!/bin/bash

if [[ "${BINARY_TYPE}" == "AppImage" ]]; then
    source ci/scripts/common/bootstrap_ubuntu_repos.sh

    echo "--> Download linuxdeployqt tool"
    wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
    chmod a+x linuxdeployqt-continuous-x86_64.AppImage
elif [[ "${BINARY_TYPE}" == "deb" ]]; then
    docker pull ubuntu:18.04
    docker run --name build-container -v $(pwd):$(pwd) -w $(pwd) -dit ubuntu:18.04 bash
elif [[ "${BINARY_TYPE}" == "rpm" ]]; then
    docker pull opensuse/leap:15.1
    docker run --name build-container -v $(pwd):$(pwd) -w $(pwd) -dit opensuse/leap:15.1 bash
elif [[ "${BINARY_TYPE}" == "exe" ]]; then
    source ci/scripts/exe/bootstrap_envvars.sh

    echo "--> Download Dependencies"

    QT_BASE_URL="https://download.qt.io/online/qtsdkrepository/windows_x86/desktop/qt5_599/qt.qt5.599.win32_msvc2015/5.9.9-0-201912101223"
    wget --quiet -O qtbase.7z "${QT_BASE_URL}qtbase-Windows-Windows_10-MSVC2015-Windows-Windows_10-X86.7z"
    wget --quiet -O qtwinextras.7z "${QT_BASE_URL}qtwinextras-Windows-Windows_10-MSVC2015-Windows-Windows_10-X86.7z"
    wget --quiet -O qttools.7z "${QT_BASE_URL}qttools-Windows-Windows_10-MSVC2015-Windows-Windows_10-X86.7z"
    wget --quiet -O qttranslations.7z "${QT_BASE_URL}qttranslations-Windows-Windows_10-MSVC2015-Windows-Windows_10-X86.7z"
    wget --quiet -O qtsvg.7z "${QT_BASE_URL}qtsvg-Windows-Windows_10-MSVC2015-Windows-Windows_10-X86.7z"
	  wget --quiet -O openssl.zip "https://indy.fulgan.com/SSL/openssl-1.0.2q-i386-win32.zip"

    7z x qtbase.7z -o/c/qt
    7z x qtwinextras.7z -o/c/qt
    7z x qttools.7z -o/c/qt
    7z x qttranslations.7z -o/c/qt
    7z x qtsvg.7z -o/c/qt

    7z x openssl.zip -o/c/openssl

    # windeployqt fails to find the binaries so we link the binaries where its looking for it
    WINDEPLOYQT_QT_DIR="/c/Users/qt/work"
    mkdir -p $WINDEPLOYQT_QT_DIR
    ln -s $QTDIR $WINDEPLOYQT_QT_DIR/install
fi
