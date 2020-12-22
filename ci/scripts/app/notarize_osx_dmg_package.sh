#!/bin/bash

echo "--> Start Notarization process"
response=$(xcrun altool -t osx -f ksnip-${VERSION}.dmg --primary-bundle-id org.ksnip.ksnip --notarize-app -u ${APPLE_DEV_USER} -p ${APPLE_DEV_PASS})
requestUUID=$(echo "${response}" | tr ' ' '\n' | tail -1)

while true; do
  echo "--> Checking notarization status"
  statusCheckResponse=$(xcrun altool --notarization-info ${requestUUID} -u ${APPLE_DEV_USER} -p ${APPLE_DEV_PASS})

  isSuccess=$(echo "${statusCheckResponse}" | grep "success")
  isFailure=$(echo "${statusCheckResponse}" | grep "invalid")

  if [[ "${isSuccess}" != "" ]]; then
      echo "--> Notarization done!"
      xcrun stapler staple -v ksnip-${VERSION}.dmg
      echo "--> Stapler done!"
      break
  fi
  if [[ "${isFailure}" != "" ]]; then
      echo "--> Notarization failed"
      return 1
  fi
  echo "--> Notarization not finished yet, sleep 2min then check again..."
  sleep 120
done