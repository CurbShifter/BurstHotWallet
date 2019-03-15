set SubWCRev="%ProgramFiles%\TortoiseSVN\bin\SubWCRev.exe"
%SubWCRev% "%CD%\..\.." "%CD%\VersionTemplate.txt" "%CD%\Version.txt"
set /p revNr=<"%CD%\Version.txt"

call "%ProgramFiles(x86)%\Microsoft Visual Studio 12.0\VC\bin\vcvars32.bat"
msbuild.exe "BurstHotWallet.sln" /t:rebuild /maxcpucount:8 /flp1:logfile=errors32.txt;errorsonly /t:"BurstHotWallet" /p:Configuration=Release /p:Platform=Win32


%SubWCRev% "%CD%\..\.." "%CD%\HotWallet-Installer.wxs" "%CD%\HotWallet-r%revNr%.wxs"
del "%CD%\HotWallet-r%revNr%.msi"

"%ProgramFiles(x86)%\WiX Toolset v3.10\bin\candle.exe" "%CD%\HotWallet-r%revNr%.wxs" -ext WixUIExtension -ext WixUtilExtension
"%ProgramFiles(x86)%\WiX Toolset v3.10\bin\light.exe" "%CD%\HotWallet-r%revNr%.wixobj" -out "%CD%\HotWallet-r%revNr%.msi" -ext WixUIExtension -ext WixUtilExtension

del "%CD%\HotWallet-r%revNr%.wixpdb"
del "%CD%\HotWallet-r%revNr%.wxs"
del "%CD%\HotWallet-r%revNr%.wixobj"