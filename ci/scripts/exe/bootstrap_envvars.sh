#!/bin/bash

QTDIR="/c/qt/5.6.3/msvc2015"
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

export PATH=$QT_BIN:$PATH
export PATH=$QT_PLUGIN:$PATH
export PATH=$CL_BIN:$PATH
export PATH=$RC_BIN:$PATH
export LIB=$UM_LIB:$LIB
export LIB=$UCRT_LIB:$LIB
export LIB=$MSVCRTD_LIB:$LIB
export LIB=$KCOLORPICKER_LIB:$LIB
export LIB=$KIMAGEANNOTATOR_LIB:$LIB
export INCLUDE=$UM_INCLUDE:$INCLUDE
export INCLUDE=$UCRT_INCLUDE:$INCLUDE
export INCLUDE=$SHARED_INCLUDE:$INCLUDE
export INCLUDE=$MSVCRTD_INCLUDE:$INCLUDE
export INCLUDE=$KCOLORPICKER_INCLUDE:$INCLUDE
export INCLUDE=$KIMAGEANNOTATOR_INCLUDE:$INCLUDE
export QTDIR=$QTDIR

