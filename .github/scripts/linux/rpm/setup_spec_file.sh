#!/bin/bash

echo "--> Create copy of spec file"
cp ci/rpm/ksnip.spec .

echo "--> Update changelog entries"
cp CHANGELOG.md changelog
sed -i '1,2d' changelog  #Remove header and empty line ad the beginning
sed -i 's/* /-- /g' changelog # Replace asterisk with double dash
sed -i 's/\[\(.*[^]]*\)\].*/\1)/g' changelog # Replace links to issues with only number
sed -i "s/## Release \([0-9]*\.[0-9]*\.[0-9]*\)/* ${BUILD_DATE} Damir Porobic <damir.porobic@gmx.com> \1/" changelog # Format release headers
cat changelog >> ksnip.spec

echo "--> Update version"
sed -i "s/Version: X.X.X/Version: ${VERSION_NUMBER}/" ksnip.spec
sed -i "s;cmake .;cmake . -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER} -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=${BUILD_TYPE};" ksnip.spec # ; is the delimiter
