#!/bin/bash

export BUILD_NUMBER=$(git rev-list --count HEAD)-$(git rev-parse --short HEAD)
export VERSION_SUFFIX=continuous
export VERSION=$VERSION_SUFFIX-$BUILD_NUMBER

if [[ "${BUILD_TYPE}" == "AppImage"  || "${BUILD_TYPE}" == "deb" ]]; then
    sudo apt-get -y install qt56base qt56x11extras qt56tools qt56svg
    source /opt/qt*/bin/qt*-env.sh
    git clone git://anongit.kde.org/extra-cmake-modules
    cd extra-cmake-modules
    mkdir build && cd build
    cmake ..
    make && sudo make install
    cd ../..
    git clone git://github.com/DamirPorobic/kColorPicker
    cd kColorPicker
    mkdir build && cd build
    cmake ..
    make && sudo make install
    sudo ldconfig
    cd ../..
    git clone git://github.com/DamirPorobic/kImageAnnotator
    cd kImageAnnotator
    mkdir build && cd build
    cmake ..
    make && sudo make install
    sudo ldconfig
    cd ../..
fi

if [[ "${BUILD_TYPE}" == "deb" ]]; then
    sudo apt-get -y install devscripts
fi