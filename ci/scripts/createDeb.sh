#!/bin/bash

apt-get install git cmake qt5-default libqt5x11extras5-dev qttools5-dev-tools extra-cmake-modules

echo "building deb in "
pwd
echo "Content:"
ls

cd kColorPicker
mkdir build && cd build
cmake ..
make && sudo make install
sudo ldconfig
cd ../..
cd kImageAnnotator
mkdir build && cd build
cmake ..
make && sudo make install
sudo ldconfig
cd ../..

cd debBuild
debuild -us -uc
