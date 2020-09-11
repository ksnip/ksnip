#!/bin/bash

wget -c https://github.com/damirporobic/uploadtool/raw/master/upload.sh

# Fix link to travis ci, the default links to the private projects section, we use travis-ci.org for public open source
export UPLOADTOOL_BODY="Travis CI build log: https://travis-ci.org/${TRAVIS_REPO_SLUG}/builds/${TRAVIS_BUILD_ID}/"

# Mark continuous builds as pre-release in github
if [[ "${VERSION_SUFFIX}" == "continuous" ]]; then
    export UPLOADTOOL_ISPRERELEASE="true"
fi


if [[ "${BINARY_TYPE}" == "AppImage" ]]; then
    find appdir -executable -type f -exec ldd {} \; | grep " => /usr" | cut -d " " -f 2-3 | sort | uniq
    bash upload.sh ksnip*.AppImage*
elif [[ "${BINARY_TYPE}" == "deb" ]]; then
    bash upload.sh ksnip-*.deb
elif [[ "${BINARY_TYPE}" == "rpm" ]]; then
    bash upload.sh ksnip-*.rpm
elif [[ "${BINARY_TYPE}" == "exe" ]]; then
    bash upload.sh ksnip-*.zip
elif [[ "${BINARY_TYPE}" == "app" ]]; then
    bash upload.sh ksnip-*.dmg
fi
