#!/bin/bash

export BUILD_TIME=$(date +"%a, %d %b %Y %T %z")
export BUILD_DATE=$(date  +"%a %b %d %Y")
export BUILD_NUMBER=$(git rev-list --count HEAD)-$(git rev-parse --short HEAD)
export VERSION_NUMBER=$(grep "project.*" CMakeLists.txt | egrep -o "([0-9]{1,}\.)+[0-9]{1,}")
export INSTALL_PREFIX="/usr/share"
export BUILD_TYPE="Release"

if [[ -z "${TRAVIS_TAG}" ]]; then
    echo "Build is not tagged this is a continues build"
    export VERSION_SUFFIX=continuous
    export VERSION=${VERSION_NUMBER}-${VERSION_SUFFIX}
else
    echo "Build is tagged this is not a continues build"
    export VERSION=${VERSION_NUMBER}
fi

git clone git://github.com/DamirPorobic/kColorPicker
git clone git://github.com/DamirPorobic/kImageAnnotator

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    sudo apt-get -y install qt56base qt56x11extras qt56tools qt56svg
    source /opt/qt*/bin/qt*-env.sh

    echo "--> Install Extra CMake Modules"
    git clone git://anongit.kde.org/extra-cmake-modules
    cd extra-cmake-modules
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make && sudo make install
    cd ../..

    echo "--> Install kColorPicker"
    cd kColorPicker
    mkdir build && cd build
    cmake .. -DBUILD_EXAMPLE=OFF -DCMAKE_BUILD_TYPE=Release
    make && sudo make install
    cd ../..

    echo "--> Install kImageAnnotator"
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
												   qttools5-dev \
                                                   qttools5-dev-tools \
                                                   extra-cmake-modules \
                                                   devscripts \
                                                   debhelper
    docker exec build-container bash -c "source ci/scripts/common/setup_dependencies_linux_noSudo.sh"

    source ci/scripts/deb/setup_deb_directory_structure.sh
    source ci/scripts/deb/setup_changelog_file.sh
    source ci/scripts/deb/setup_build_rules.sh
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker exec build-container zypper --non-interactive install git \
                                                                 cmake \
                                                                 extra-cmake-modules \
                                                                 patterns-devel-C-C++-devel_C_C++ \
                                                                 libqt5-linguist-devel \
                                                                 libqt5-qtx11extras-devel \
                                                                 libqt5-qtdeclarative-devel \
                                                                 libqt5-qtbase-devel \
                                                                 rpm-build \
                                                                 update-desktop-files
    docker exec build-container bash -c "source ci/scripts/common/setup_dependencies_linux_noSudo.sh"

    source ci/scripts/rpm/setup_spec_file.sh
    source ci/scripts/rpm/setup_rpm_directory_structure.sh

    sudo chown -R root:root ksnip-${VERSION_NUMBER}
elif [[ "${BUILD_TYPE}" == "exe" ]]; then
    source ci/scripts/exe/setup_dependencies_windows.sh
elif [[ "${BUILD_TYPE}" == "app" ]]; then
    brew install qt5

    export PATH="/usr/local/opt/qt/bin:$PATH"

    source ci/scripts/common/setup_dependencies_linux_noSudo.sh
fi
