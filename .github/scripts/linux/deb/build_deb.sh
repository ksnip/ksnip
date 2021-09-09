#!/bin/bash

cd ksnip-${VERSION_NUMBER}

debuild -us -uc --lintian-opts --profile debian

mv ksnip_*.deb ksnip-${VERSION}.deb

echo "-----------"
ls .. -al
echo "-----------"
ls -al
echo "-----------"
