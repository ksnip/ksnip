#!/bin/bash

cd ksnip-${VERSION_NUMBER}

rpmbuild -ba SPECS/ksnip-*.spec --define '_topdir %(pwd)'

echo "----------------"
ls ${WORKSPACE}/ksnip-${VERSION_NUMBER}/RPMS/
echo "----------------"
pwd
echo "----------------"
mv ${WORKSPACE}/ksnip-${VERSION_NUMBER}/RPMS/x86_64/ksnip-*.rpm ${WORKSPACE}/ksnip-${VERSION}.rpm
echo "----------------"
ls ${WORKSPACE}/
echo "----------------"

