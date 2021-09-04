#!/bin/bash

mv build/src/ksnip*.app ksnip.app
cp build/translations/ksnip_*.qm ./ksnip.app/Contents/Resources/
cp kImageAnnotator/build/translations/kImageAnnotator_*.qm ./ksnip.app/Contents/Resources/

macdeployqt ksnip.app -dmg -sign-for-notarization="${APPLE_DEV_IDENTITY}"

mv ksnip.dmg ksnip-${VERSION}.dmg