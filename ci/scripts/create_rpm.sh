#!/bin/bash

zypper --non-interactive install git cmake extra-cmake-modules patterns-openSUSE-devel_C_C++ libqt5-linguist-devel libqt5-qtx11extras-devel libqt5-qtdeclarative-devel libqt5-qtbase-devel rpm-build

git clone git://github.com/DamirPorobic/kColorPicker
cd kColorPicker
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make && make install
ldconfig
cd ../..

git clone git://github.com/DamirPorobic/kImageAnnotator
cd kImageAnnotator
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make && make install
ldconfig
cd ../..

cd rpmBuild
rpmbuild -ba SPECS/ksnip-1.5.0.spec --define '_topdir %(pwd)'