#!/bin/bash

cd ksnip-${VERSION_NUMBER}

debuild -us -uc --lintian-opts --profile debian

mv ../ksnip_*.deb ${WORKSPACE}/ksnip-${VERSION}.deb

echo "-----------"
pwd
echo "-----------"
ls .. -al
echo "-----------"
ls -al
echo "-----------"
