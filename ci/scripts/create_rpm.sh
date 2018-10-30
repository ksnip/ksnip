#!/bin/bash

zypper --non-interactive install git cmake extra-cmake-modules patterns-openSUSE-devel_C_C++ libqt5-linguist-devel libqt5-qtx11extras-devel libqt5-qtdeclarative-devel libqt5-qtbase-devel rpm-build update-desktop-files

cd kColorPicker
mkdir build && cd build
cmake ..
make && make install
cd ../..
cd kImageAnnotator
mkdir build && cd build
cmake ..
make && make install
cd ../..

cd ksnip-*
rpmbuild -ba SPECS/ksnip-*.spec --define '_topdir %(pwd)'