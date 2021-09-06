#!/bin/bash

cd ksnip-${VERSION_NUMBER}

rpmbuild -ba SPECS/ksnip-*.spec --define '_topdir %(pwd)'

mv ksnip-${VERSION_NUMBER}/RPMS/x86_64/ksnip-*.rpm ksnip-${VERSION}.rpm

