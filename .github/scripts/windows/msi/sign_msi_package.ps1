$CERTIFICATE_PFX_ENCODED = $Env:MICROSOFT_CERT_PFX -replace "\\", ""
$MICROSOFT_CERT_PFX_PASS = $Env:MICROSOFT_CERT_PFX_PASS -replace "\\", ""

$CERTIFICATE_PFX = "certificate.pfx"
$CERTIFICATE_PFX_DECODE = [system.convert]::frombase64string($CERTIFICATE_PFX_ENCODED)

set-content -Path $CERTIFICATE_PFX -Value $CERTIFICATE_PFX_DECODE -Encoding Byte

$MICROSOFT_CERT_PFX_PASS_SECURED = ConvertTo-SecureString -String $MICROSOFT_CERT_PFX_PASS -AsPlainText -Force

Write-Host "Import Certificate"

Import-PfxCertificate -FilePath $CERTIFICATE_PFX -CertStoreLocation Cert:\LocalMachine\My -Password $MICROSOFT_CERT_PFX_PASS_SECURED

Write-Host "Sign package"

$KSNIP_VERSION = $Env:VERSION
$KSNIP_MSI = "ksnip-$KSNIP_VERSION.msi"
$TIMESTAMP_SERVER = "http://timestamp.comodoca.com/authenticode"
$SIGNTOOL = 'C:\Program Files (x86)\Windows Kits\10\bin\x64\signtool.exe'

& SIGNTOOL sign /v /debug /sm /s My /n 'Damir Porobic' /d 'Ksnip - Screenshot Tool' /t $TIMESTAMP_SERVER $KSNIP_MSI

rm $CERTIFICATE_PFX

Write-Host "Finished signing"