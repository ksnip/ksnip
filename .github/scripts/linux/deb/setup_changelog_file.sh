#!/bin/bash

echo "--> Setup changelog file"
cp CHANGELOG.md changelog
sed -i '1,2d' changelog  #Remove header and empty line ad the beginning
sed -i 's/\[\(.*[^]]*\)\].*/\1)/g' changelog # Replace links to issues with only number
sed -i "s/^[[:blank:]]*$/\n -- Damir Porobic <damir.porobic@gmx.com>  ${BUILD_TIME}\n/" changelog # After every release add time and author
sed -i 's/## Release \([0-9]*\.[0-9]*\.[0-9]*\)/ksnip (\1)  stretch; urgency=medium\n/' changelog # Rename release headers
sed -i 's/^\(\* .*\)/  \1/' changelog # Add two spaces before every entry
printf "\n -- Damir Porobic <damir.porobic@gmx.com>  ${BUILD_TIME}\n" >> changelog # Add time and author for the first release
cp changelog ksnip-${VERSION_NUMBER}/debian/
