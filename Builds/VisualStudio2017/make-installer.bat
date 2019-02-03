set SubWCRev="%ProgramFiles%\TortoiseSVN\bin\SubWCRev.exe"
%SubWCRev% "%CD%\..\.." "%CD%\VersionTemplate.txt" "%CD%\Version.txt"
set /p revNr=<"%CD%\Version.txt"

%SubWCRev% "%CD%\..\.." "%CD%\HotWallet-Installer.wxs" "%CD%\HotWallet-r%revNr%.wxs"
del "%CD%\HotWallet-r%revNr%.msi"

"%ProgramFiles(x86)%\WiX Toolset v3.11\bin\candle.exe" "%CD%\HotWallet-r%revNr%.wxs" -ext WixUIExtension -ext WixUtilExtension
"%ProgramFiles(x86)%\WiX Toolset v3.11\bin\light.exe" "%CD%\HotWallet-r%revNr%.wixobj" -out "%CD%\HotWallet-r%revNr%.msi" -ext WixUIExtension -ext WixUtilExtension

del "%CD%\HotWallet-r%revNr%.wixpdb"
del "%CD%\HotWallet-r%revNr%.wxs"
del "%CD%\HotWallet-r%revNr%.wixobj"