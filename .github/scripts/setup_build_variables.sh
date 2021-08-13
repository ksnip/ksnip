#!/bin/bash

VERSION_REGEX="([0-9]{1,}\.)+[0-9]{1,}"
BUILD_TIME=$(date +"%a, %d %b %Y %T %z")
BUILD_DATE=$(date  +"%a %b %d %Y")
BUILD_NUMBER=$(git rev-list --count HEAD)-$(git rev-parse --short HEAD)
VERSION_NUMBER=$(grep "project.*" CMakeLists.txt | egrep -o "${VERSION_REGEX}")
INSTALL_PREFIX="$GITHUB_WORKSPACE/tmp"

# Store variables in files that is shared among runners.
echo "BUILD_TYPE=Debug" >> $GITHUB_ENV
echo "BUILD_TIME=$BUILD_TIME" >> $GITHUB_ENV
echo "BUILD_DATE=$BUILD_DATE" >> $GITHUB_ENV
echo "BUILD_NUMBER=$BUILD_NUMBER" >> $GITHUB_ENV
echo "VERSION_NUMBER=$VERSION_NUMBER" >> $GITHUB_ENV
echo "INSTALL_PREFIX=$INSTALL_PREFIX" >> $GITHUB_ENV