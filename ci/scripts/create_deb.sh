#!/bin/bash

apt-get update
apt-get -y install git cmake build-essential qt5-default libqt5x11extras5-dev qttools5-dev-tools extra-cmake-modules devscripts debhelper

cd debBuild
debuild -us -uc
