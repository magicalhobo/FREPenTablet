SET AIR_SDK=

echo "You must update this bat with your AIR 3.0 SDK path before running"
pause

"%AIR_SDK%\bin\adt.bat" -certificate -cn SelfSign -ou QE -o "Example, Co" -c US 2048-RSA test.p12 test