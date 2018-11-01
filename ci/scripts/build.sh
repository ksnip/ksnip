#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    docker exec build-container bash -c "source ci/scripts/create_appImage.sh"
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker exec build-container bash -c "source ci/scripts/create_deb.sh"
    mv ksnip_*.deb ksnip-$VERSION-amd64.deb
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker exec build-container bash -c "source ci/scripts/create_rpm.sh"
    sudo chown -R 2000:2000 ksnip-$VERSION_NUMBER
    mv ksnip-$VERSION_NUMBER/RPMS/x86_64/ksnip-*.rpm ksnip-$VERSION-x86_64.rpm
fi
