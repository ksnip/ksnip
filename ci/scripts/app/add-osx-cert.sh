#!/usr/bin/env sh

KEY_CHAIN=build.keychain
CERTIFICATE_P12=certificate.p12

echo "--> Recreate the certificate from the secure environment variable"
echo ${APPLE_CERT_P12} | base64 --decode > $CERTIFICATE_P12

echo "--> create a keychain"
security create-keychain -p travis $KEY_CHAIN

echo "--> Make the keychain the default so identities are found"
security default-keychain -s $KEY_CHAIN

echo "--> Unlock the keychain"
security unlock-keychain -p travis $KEY_CHAIN

security import $CERTIFICATE_P12 -k $KEY_CHAIN -P ${APPLE_CERT_P12_PASS} -T /usr/bin/codesign;

security set-key-partition-list -S apple-tool:,apple: -s -k travis $KEY_CHAIN

echo "--> Remove certs"
rm -fr *.p12