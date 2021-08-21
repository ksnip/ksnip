#!/bin/bash

export KIMAGEANNOTATOR="${INSTALL_PREFIX}"
export QTDIR="${QT5_DIR}"
export OPENSSL_DIR="${GITHUB_WORKSPACE}/open_ssl"

cd build
cpack --verbose
mv ksnip*.msi ${GITHUB_WORKSPACE}/ksnip-${VERSION}.msi
