#!/bin/bash

cpack --verbose
mv ksnip*.msi $GITHUB_WORKSPACE/ksnip-${VERSION}.msi
