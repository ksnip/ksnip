#!/bin/bash

apt-get update
apt-get -y install git cmake build-essential qt5-default libqt5x11extras5-dev qttools5-dev-tools extra-cmake-modules devscripts debhelper

cd kColorPicker
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/lib
make && make install
ldconfig
cd ../..
cd kImageAnnotator
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/lib
make && make install
ldconfig
cd ../..

cd debBuild
debuild -us -uc
