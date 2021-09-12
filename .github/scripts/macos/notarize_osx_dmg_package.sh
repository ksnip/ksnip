#!/bin/bash

echo "Starting Notarization process."
response=$(xcrun altool -t osx -f ksnip-${VERSION}.dmg --primary-bundle-id org.ksnip.ksnip --notarize-app -u ${APPLE_DEV_USER} -p ${APPLE_DEV_PASS})
requestUUID=$(echo "${response}" | tr ' ' '\n' | tail -1)

retryCounter=0

while true; do
  retryCounter=$((retryCounter + 1))

  if [[ "${retryCounter}" -gt 5 ]]; then
      echo "Notarization timeout!"
      exit 1
  fi

  echo "Notarization retry ${retryCounter}."

  echo "Checking notarization status."
  statusCheckResponse=$(xcrun altool --notarization-info ${requestUUID} -u ${APPLE_DEV_USER} -p ${APPLE_DEV_PASS})

  isSuccess=$(echo "${statusCheckResponse}" | grep "success")
  isFailure=$(echo "${statusCheckResponse}" | grep "invalid")

  if [[ "${isSuccess}" != "" ]]; then
      echo "Notarization done!"
      xcrun stapler staple -v ksnip-${VERSION}.dmg
      echo "Stapler done!"
      exit 0
  fi

  if [[ "${isFailure}" != "" ]]; then
      echo "Notarization failed!"
      exit 1
  fi

  echo "Notarization not finished yet, sleep 2min then check again..."
  sleep 120
done