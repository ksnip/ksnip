#!/bin/bash

cd ksnip-${VERSION_NUMBER}

debuild -us -uc --lintian-opts --profile debian

mv ${WORKSPACE}/ksnip_*.deb ${WORKSPACE}/ksnip-${VERSION}.deb

