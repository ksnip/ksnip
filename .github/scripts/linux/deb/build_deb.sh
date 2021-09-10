#!/bin/bash

cd ksnip-${VERSION_NUMBER}

debuild -us -uc --lintian-opts --profile debian --preserve-envvar VERSION_SUFFIX

mv ${WORKSPACE}/ksnip_*.deb ${WORKSPACE}/ksnip-${VERSION}.deb

