#!/bin/bash

VERSION_REGEX="([0-9]{1,}\.)+[0-9]{1,}"
BUILD_TIME=$(date +"%a, %d %b %Y %T %z")
BUILD_DATE=$(date  +"%a %b %d %Y")
BUILD_NUMBER=$(git rev-list --count HEAD)-$(git rev-parse --short HEAD)
VERSION_NUMBER=$(grep "project.*" CMakeLists.txt | egrep -o "${VERSION_REGEX}")
WORKSPACE="$GITHUB_WORKSPACE"
INSTALL_PREFIX="$WORKSPACE/tmp"

echo "BUILD_TYPE=Release" >> $GITHUB_ENV
echo "BUILD_TIME=$BUILD_TIME" >> $GITHUB_ENV
echo "BUILD_DATE=$BUILD_DATE" >> $GITHUB_ENV
echo "BUILD_NUMBER=$BUILD_NUMBER" >> $GITHUB_ENV
echo "VERSION_REGEX=$VERSION_REGEX" >> $GITHUB_ENV
echo "WORKSPACE=$WORKSPACE" >> $GITHUB_ENV
echo "INSTALL_PREFIX=$INSTALL_PREFIX" >> $GITHUB_ENV
echo "VERSION_NUMBER=$VERSION_NUMBER" >> $GITHUB_ENV
echo "UPLOADTOOL_ISPRERELEASE=true" >> $GITHUB_ENV
echo "BUILD_TESTS=OFF" >> $GITHUB_ENV


if [[ "$GITHUB_REF" = refs/tags* ]]; then
  GITHUB_TAG=${GITHUB_REF#refs/tags/}
 	echo "GitHub Tag is: $GITHUB_TAG"
  echo "GITHUB_TAG=$GITHUB_TAG" >> $GITHUB_ENV
else
	echo "GitHub Ref is: $GITHUB_REF"
fi


if [[ -z "${GITHUB_TAG}" ]]; then
    echo "Build is not tagged this is a continuous build"
    VERSION_SUFFIX="continuous"
    echo "VERSION_SUFFIX=$VERSION_SUFFIX" >> $GITHUB_ENV
    echo "VERSION=${VERSION_NUMBER}-${VERSION_SUFFIX}" >> $GITHUB_ENV
    echo "RELEASE_NAME=Continuous build" >> $GITHUB_ENV
    echo "IS_PRERELASE=true" >> $GITHUB_ENV
    echo "RELEASE_TAG=continuous" >> $GITHUB_ENV
else
    echo "Build is tagged this is not a continues build"
    echo "Building ksnip version ${VERSION_NUMBER}"
    echo "VERSION=${VERSION_NUMBER}" >> $GITHUB_ENV
    echo "RELEASE_NAME=${GITHUB_TAG}" >> $GITHUB_ENV
    echo "IS_PRERELASE=false" >> $GITHUB_ENV
    echo "RELEASE_TAG=${GITHUB_TAG}" >> $GITHUB_ENV
fi


# Message show on the release page
ACTION_LINK_TEXT="Build logs: https://github.com/ksnip/ksnip/actions"
BUILD_TIME_TEXT="Build Time: $(TZ=CET date +"%d.%m.%Y %T %Z")"
UPLOADTOOL_BODY="${ACTION_LINK_TEXT} %0A ${BUILD_TIME_TEXT}"
echo "UPLOADTOOL_BODY=$UPLOADTOOL_BODY" >> $GITHUB_ENV


if [[ "$QT_VERSION" == 6* ]]; then
	echo "USE_QT6=yes" >> $GITHUB_ENV
else
	echo "USE_QT6=no" >> $GITHUB_ENV
fi
