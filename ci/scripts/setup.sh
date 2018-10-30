#!/bin/bash

export BUILD_NUMBER=$(git rev-list --count HEAD)-$(git rev-parse --short HEAD)
export BUILD_TIME=$(date +"%a, %d %b %Y %T %z")
export BUILD_DATE=$(date  +"%a %b %d %Y")
export VERSION_SUFFIX=continuous
export VERSION=$VERSION_SUFFIX-$BUILD_NUMBER

git clone git://github.com/DamirPorobic/kColorPicker
git clone git://github.com/DamirPorobic/kImageAnnotator

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    sudo apt-get -y install qt56base qt56x11extras qt56tools qt56svg
    source /opt/qt*/bin/qt*-env.sh
    git clone git://anongit.kde.org/extra-cmake-modules
    cd extra-cmake-modules
    mkdir build && cd build
    cmake ..
    make && sudo make install
    cd ../..
    cd kColorPicker
    mkdir build && cd build
    cmake ..
    make && sudo make install
    cd ../..
    cd kImageAnnotator
    mkdir build && cd build
    cmake ..
    make && sudo make install
    cd ../..
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    mkdir debBuild
    cp -R CMakeLists.txt desktop/ icons/ LICENSE README.md src/ external/ translations/ debBuild/
    tar -cvzf ksnip_1.5.0.orig.tar.gz debBuild/
    cp -R ci/debian debBuild/

    cp CHANGELOG.md changelog
    sed -i '1,2d' changelog  #Remove header and empty line ad the beginning
    sed -i 's/\[\(.*[^]]*\)\].*/\1)/g' changelog # Replace links to issues with only number
    sed -i "s/^[[:blank:]]*$/\n -- Damir Porobic <damir.porobic@gmx.com>  ${BUILD_TIME}\n/" changelog # After every release add time and author
    sed -i 's/## Release \([0-9]\.[0-9]\.[0-9]\)/ksnip (\1)  stretch; urgency=medium\n/' changelog # Rename release headers
    sed -i 's/^\(\* .*\)/  \1/' changelog # Add two spaces before every entry
    echo "\n -- Damir Porobic <damir.porobic@gmx.com>  ${BUILD_TIME}" >> changelog # Add time and author for the first release
    cp changelog debBuild/debian/

    sed -i "s/dh_auto_configure -- /dh_auto_configure -- -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER}/" debBuild/debian/rules
    cat debBuild/debian/rules
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    cp ci/rpm/ksnip-1.5.0.spec .

    cp CHANGELOG.md changelog
    sed -i '1,2d' changelog  #Remove header and empty line ad the beginning
    sed -i 's/* /-- /g' changelog # Replace asterisk with double dash
    sed -i 's/\[\(.*[^]]*\)\].*/\1)/g' changelog # Replace links to issues with only number
    sed -i "s/## Release \([0-9]\.[0-9]\.[0-9]\)/* ${BUILD_DATE} Damir Porobic <damir.porobic@gmx.com> \1/" changelog # Format release headers
    cat changelog >> ksnip-1.5.0.spec

    sed -i "s/cmake ./cmake . -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER}/" ksnip-1.5.0.spec
    cat ksnip-1.5.0.spec # REMOVE THIS

    mkdir ksnip-1.5.0
    cp -R CMakeLists.txt desktop/ icons/ LICENSE README.md src/ external/ translations/ ksnip-1.5.0/
    tar -cvzf ksnip-1.5.0.tar.gz ksnip-1.5.0/
    mkdir ksnip-1.5.0/SOURCES
    cp ksnip-1.5.0.tar.gz ksnip-1.5.0/SOURCES/
    mkdir ksnip-1.5.0/SPECS
    cp ksnip-1.5.0.spec ksnip-1.5.0/SPECS/
    sudo chown -R root:root ksnip-1.5.0
fi
