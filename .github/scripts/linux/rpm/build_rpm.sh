#!/bin/bash

cd ksnip-*
rpmbuild -ba SPECS/ksnip-*.spec --define '_topdir %(pwd)'

