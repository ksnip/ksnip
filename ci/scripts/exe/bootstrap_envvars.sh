#!/bin/bash

QT_BIN="/c/qt/5.6.3/msvc2015/bin"
QT_PLUGIN="/c/qt/5.6.3/msvc2015/plugins/platforms"
CL_BIN="/c/Program Files (x86)/Microsoft Visual Studio/2017/BuildTools/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x86"
RC_BIN="/c/Program Files (x86)/Windows Kits/10/bin/10.0.17134.0/x86"
UM_LIB="/c/Program Files (x86)/Windows Kits/10/Lib/10.0.17134.0/um/x86"
UCRT_LIB="/c/Program Files (x86)/Windows Kits/10/Lib/10.0.17134.0/ucrt/x86"
MSVCRTD_LIB="/c/Program Files (x86)/Microsoft Visual Studio/2017/BuildTools/VC/Tools/MSVC/14.16.27023/lib/x86"
KCOLORPICKER_LIB="/c/Program Files (x86)/kColorPicker/lib"
KIMAGEANNOTATOR_LIB="/c/Program Files (x86)/kImageAnnotator/lib"
UM_INCLUDE="/c/Program Files (x86)/Windows Kits/10/Include/10.0.17134.0/um"
UCRT_INCLUDE="/c/Program Files (x86)/Windows Kits/10/Include/10.0.17134.0/ucrt"
SHARED_INCLUDE="/c/Program Files (x86)/Windows Kits/10/Include/10.0.17134.0/shared"
MSVCRTD_INCLUDE="/c/Program Files (x86)/Microsoft Visual Studio/2017/BuildTools/VC/Tools/MSVC/14.16.27023/include"
KCOLORPICKER_INCLUDE="/c/Program Files (x86)/kColorPicker/include"
KIMAGEANNOTATOR_INCLUDE="/c/Program Files (x86)/kImageAnnotator/include"

export QT="/c/qt/5.6.3/msvc2015/"
export QTDIR="/c/qt/5.6.3/msvc2015/"
export QT_DIR="/c/qt/5.6.3/msvc2015/"
export PATH=$PATH:$QT_BIN
export PATH=$PATH:$QT_PLUGIN
export PATH=$PATH:$CL_BIN
export PATH=$PATH:$RC_BIN
export LIB=$LIB:$UM_LIB
export LIB=$LIB:$UCRT_LIB
export LIB=$LIB:$MSVCRTD_LIB
export LIB=$LIB:$KCOLORPICKER_LIB
export LIB=$LIB:$KIMAGEANNOTATOR_LIB
export INCLUDE=$INCLUDE:$UM_INCLUDE
export INCLUDE=$INCLUDE:$UCRT_INCLUDE
export INCLUDE=$INCLUDE:$SHARED_INCLUDE
export INCLUDE=$INCLUDE:$MSVCRTD_INCLUDE
export INCLUDE=$INCLUDE:$KCOLORPICKER_INCLUDE
export INCLUDE=$INCLUDE:$KIMAGEANNOTATOR_INCLUDE

mkdir -p /c/Users/qt/work/install
ln -s /c/Users/qt/work/install/bin /c/qt/5.6.3/msvc2015/bin

