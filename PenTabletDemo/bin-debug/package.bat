SET AIR_SDK=
SET ANE_PATH=..\..\PenTabletLib\bin

echo "You must update this bat with your AIR 3.0 SDK path before running"
pause

"%AIR_SDK%\bin\adt.bat" -package -XnoAneValidate -storetype pkcs12 -keystore test.p12 -storepass test -target native PenTabletDemo PenTabletDemo-app.xml PenTabletDemo.swf -extdir "%ANE_PATH%"