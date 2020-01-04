set SubWCRev="%ProgramFiles%\TortoiseSVN\bin\SubWCRev.exe"
%SubWCRev% "%CD%\..\.." "%CD%\VersionTemplate.txt" "%CD%\Version.txt"
set /p revNr=<"%CD%\Version.txt"

:: build
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild.exe "BurstHotWallet.sln" /t:rebuild /maxcpucount:8 /flp1:logfile=errors32.txt;errorsonly /t:"BurstHotWallet" /p:Configuration=Release /p:Platform=Win32

:: create a copy of the script with the rev number
%SubWCRev% "%CD%\..\.." "%CD%\HotWallet-Installer.wxs" "%CD%\HotWallet-r%revNr%.wxs"
del "%CD%\HotWallet-r%revNr%.msi"

:: bake installer
"%ProgramFiles(x86)%\WiX Toolset v3.11\bin\candle.exe" "%CD%\HotWallet-r%revNr%.wxs" -ext WixUIExtension -ext WixUtilExtension
mkdir "%CD%\..\..\bin\"
"%ProgramFiles(x86)%\WiX Toolset v3.11\bin\light.exe" "%CD%\HotWallet-r%revNr%.wixobj" -out "%CD%\..\..\bin\BurstHotWallet-r%revNr%.msi" -ext WixUIExtension -ext WixUtilExtension

:: del temp files
del "%CD%\BurstHotWallet-r%revNr%.wixpdb"
del "%CD%\HotWallet-r%revNr%.wxs"
del "%CD%\HotWallet-r%revNr%.wixobj"
del "%CD%\..\..\bin\BurstHotWallet-r%revNr%.wixpdb"

:: make copy to upload to github w/o rev tag
del "%CD%\..\..\bin\BurstHotWallet.msi"
copy "%CD%\..\..\bin\BurstHotWallet-r%revNr%.msi" "%CD%\..\..\bin\BurstHotWallet.msi"