#!/bin/bash

wget -c https://github.com/probonopd/uploadtool/raw/master/upload.sh

# Fix link to travis ci, the default links to the private projects section, we use travis-ci.org for public open source
export UPLOADTOOL_BODY="Travis CI build log: https://travis-ci.org/${TRAVIS_REPO_SLUG}/builds/${TRAVIS_BUILD_ID}/"

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    find appdir -executable -type f -exec ldd {} \; | grep " => /usr" | cut -d " " -f 2-3 | sort | uniq
    bash upload.sh ksnip*.AppImage*
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    bash upload.sh ksnip-*.deb
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    bash upload.sh ksnip-*.rpm
elif [[ "${BUILD_TYPE}" == "exe" ]]; then
    bash upload.sh ksnip-*.zip
elif [[ "${BUILD_TYPE}" == "app" ]]; then
    bash upload.sh ksnip-*.dmg
fi
