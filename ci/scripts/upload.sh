#!/bin/bash

wget -c https://github.com/probonopd/uploadtool/raw/master/upload.sh

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    find appdir -executable -type f -exec ldd {} \; | grep " => /usr" | cut -d " " -f 2-3 | sort | uniq
    bash upload.sh ksnip*.AppImage*
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    bash upload.sh ksnip*.deb
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    bash upload.sh ksnip*.rpm
fi
