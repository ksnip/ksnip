#!/bin/bash

echo "LIB=$LIB;$INSTALL_PREFIX/lib" >> $GITHUB_ENV
echo "INCLUDE=$INCLUDE;$INSTALL_PREFIX/include" >> $GITHUB_ENV
echo "PATH=$PATH;C:/msys64/usr/bin" >> $GITHUB_ENV