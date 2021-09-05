#!/bin/bash

sudo chown -R root:root ksnip-${VERSION_NUMBER}

cd ksnip-${VERSION_NUMBER}

rpmbuild -ba SPECS/ksnip-*.spec --define '_topdir %(pwd)'

