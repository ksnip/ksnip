#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    source ci/scripts/appImage/build_appImage.sh
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker exec build-container bash -c "source ci/scripts/deb/build_deb.sh"
    mv ksnip_*.deb ksnip-$VERSION-amd64.deb
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker exec build-container bash -c "source ci/scripts/rpm/build_rpm.sh"
    sudo chown -R 2000:2000 ksnip-$VERSION_NUMBER
    mv ksnip-$VERSION_NUMBER/RPMS/x86_64/ksnip-*.rpm ksnip-$VERSION-x86_64.rpm
elif [[ "${BUILD_TYPE}" == "exe" ]]; then
    mkdir build && cd build
    cmake .. -G"NMake Makefiles" -DCMAKE_CXX_COMPILER=cl -DVERSION_SUFIX=$VERSION_SUFFIX -DBUILD_NUMBER=$BUILD_NUMBER -DCMAKE_BUILD_TYPE=Release
    nmake
    cd ..
    mv build/src/ksnip*.exe ksnip-$VERSION-x86_64.exe
fi
