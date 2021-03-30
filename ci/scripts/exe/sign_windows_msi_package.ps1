$CERTIFICATE_PFX_ENCODED = $Env:MICROSOFT_CERT_PFX -replace "\\", ""
$MICROSOFT_CERT_PFX_PASS = $Env:MICROSOFT_CERT_PFX_PASS -replace "\\", ""

$CERTIFICATE_PFX = "certificate.pfx"
$CERTIFICATE_PFX_DECODE = [system.convert]::frombase64string($CERTIFICATE_PFX_ENCODED)

set-content -Path $CERTIFICATE_PFX -Value $CERTIFICATE_PFX_DECODE -Encoding Byte


$MICROSOFT_CERT_PFX_PASS_SECURED = ConvertTo-SecureString -String $MICROSOFT_CERT_PFX_PASS -AsPlainText -Force

Import-PfxCertificate -FilePath $CERTIFICATE_PFX -CertStoreLocation Cert:\LocalMachine\My -Password $MICROSOFT_CERT_PFX_PASS_SECURED

Start-Process -PassThru -Wait "C:\Program Files (x86)\Windows Kits\10\bin\x64\signtool.exe" -ArgumentList "sign -v -debug -sm -s My -n `"Ksnip`" -d `"Screenshot Tool`" ksnip*.msi"