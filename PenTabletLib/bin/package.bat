SET DLL_PATH=..\..\FREPenTablet\Debug
SET AIR_SDK=

echo "You must update this bat with your AIR 3.0 SDK path before running"
pause

copy "%DLL_PATH%\FREPenTablet.dll" .\
"%AIR_SDK%\bin\adt.bat" -package -storetype pkcs12 -keystore test.p12 -storepass test -target ane PenTabletLib.ane extension.xml -swc PenTabletLib.swc -platform Windows-x86 library.swf FREPenTablet.dll