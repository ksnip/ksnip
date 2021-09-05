#!/bin/bash

cd ksnip-${VERSION_NUMBER}

rpmbuild -ba SPECS/ksnip-*.spec --define '_topdir %(pwd)'

