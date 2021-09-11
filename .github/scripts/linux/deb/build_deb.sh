#!/bin/bash

cd ksnip-${VERSION_NUMBER}

dpkg-buildpackage -us -uc -i -b

mv ${WORKSPACE}/ksnip_*.deb ${WORKSPACE}/ksnip-${VERSION}.deb
