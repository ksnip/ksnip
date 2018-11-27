#!/bin/bash

export BUILD_TIME=$(date +"%a, %d %b %Y %T %z")
export BUILD_DATE=$(date  +"%a %b %d %Y")
export BUILD_NUMBER=$(git rev-list --count HEAD)-$(git rev-parse --short HEAD)
export VERSION_SUFFIX=continuous
export VERSION_NUMBER=$(grep "project.*" CMakeLists.txt | egrep -o "([0-9]{1,}\.)+[0-9]{1,}")
export VERSION=$VERSION_NUMBER-$VERSION_SUFFIX

git clone git://github.com/DamirPorobic/kColorPicker
git clone git://github.com/DamirPorobic/kImageAnnotator

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    sudo apt-get -y install qt56base qt56x11extras qt56tools qt56svg
    source /opt/qt*/bin/qt*-env.sh

    git clone git://anongit.kde.org/extra-cmake-modules
    cd extra-cmake-modules
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make && sudo make install
    cd ../..
    cd kColorPicker
    mkdir build && cd build
    cmake .. -DBUILD_EXAMPLE=OFF -DCMAKE_BUILD_TYPE=Release
    make && sudo make install
    cd ../..
    cd kImageAnnotator
    mkdir build && cd build
    cmake .. -DBUILD_EXAMPLE=OFF -DCMAKE_BUILD_TYPE=Release
    make && sudo make install
    cd ../..

elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker exec build-container apt-get update
    docker exec build-container apt-get -y install git \
                                                   cmake \
                                                   build-essential \
                                                   qt5-default \
                                                   libqt5x11extras5-dev \
                                                   qttools5-dev-tools \
                                                   extra-cmake-modules \
                                                   devscripts \
                                                   debhelper
    docker exec build-container bash -c "source ci/scripts/common/setup_dependencies_linux_noSudo.sh"

    mkdir ksnip-$VERSION_NUMBER
    cp -R CMakeLists.txt desktop/ icons/ LICENSE README.md src/ translations/ ksnip-$VERSION_NUMBER/
    tar -cvzf ksnip_$VERSION_NUMBER.orig.tar.gz ksnip-$VERSION_NUMBER/
    cp -R ci/debian ksnip-$VERSION_NUMBER/

    cp CHANGELOG.md changelog
    sed -i '1,2d' changelog  #Remove header and empty line ad the beginning
    sed -i 's/\[\(.*[^]]*\)\].*/\1)/g' changelog # Replace links to issues with only number
    sed -i "s/^[[:blank:]]*$/\n -- Damir Porobic <damir.porobic@gmx.com>  ${BUILD_TIME}\n/" changelog # After every release add time and author
    sed -i 's/## Release \([0-9]*\.[0-9]*\.[0-9]*\)/ksnip (\1)  stretch; urgency=medium\n/' changelog # Rename release headers
    sed -i 's/^\(\* .*\)/  \1/' changelog # Add two spaces before every entry
    echo "\n -- Damir Porobic <damir.porobic@gmx.com>  ${BUILD_TIME}" >> changelog # Add time and author for the first release
    cp changelog ksnip-$VERSION_NUMBER/debian/

    sed -i "s/dh_auto_configure --/dh_auto_configure -- -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER}/" ksnip-$VERSION_NUMBER/debian/rules
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker exec build-container zypper --non-interactive install git \
                                                                 cmake \
                                                                 extra-cmake-modules \
                                                                 patterns-openSUSE-devel_C_C++ \
                                                                 libqt5-linguist-devel \
                                                                 libqt5-qtx11extras-devel \
                                                                 libqt5-qtdeclarative-devel \
                                                                 libqt5-qtbase-devel \
                                                                 rpm-build \
                                                                 update-desktop-files
    docker exec build-container bash -c "source ci/scripts/common/setup_dependencies_linux_noSudo.sh"

    source ci/scripts/rpm/setup_spec_file.sh
    source ci/scripts/rpm/setup_rpm_directory_structure.sh

    sudo chown -R root:root ksnip-$VERSION_NUMBER
elif [[ "${BUILD_TYPE}" == "exe" ]]; then
    source ci/scripts/exe/setup_dependencies_windows.sh
fi
