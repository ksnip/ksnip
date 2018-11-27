#!/bin/bash

echo "--> Create directory and everything we need to deliver"
mkdir ksnip-$VERSION_NUMBER
cp -R CMakeLists.txt desktop/ icons/ LICENSE README.md src/ translations/ ksnip-$VERSION_NUMBER/
echo "--> Package directory"
tar -cvzf ksnip-$VERSION_NUMBER.tar.gz ksnip-$VERSION_NUMBER/
echo "--> Copy package to SOURCE directory"
mkdir ksnip-$VERSION_NUMBER/SOURCES
cp ksnip-$VERSION_NUMBER.tar.gz ksnip-$VERSION_NUMBER/SOURCES/
echo "--> Copy spec file to SPEC directory"
mkdir ksnip-$VERSION_NUMBER/SPECS
cp ksnip.spec ksnip-$VERSION_NUMBER/SPECS/ksnip-$VERSION_NUMBER.spec
