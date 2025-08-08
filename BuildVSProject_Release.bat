set "SDKDIR=D:\WorkSpace\MySdk"
set "QtDIR=D:\Qt\5.15.2\msvc2019_64"

xcopy "%SDKDIR%\include\*.h" "%~dp0include\" /E /I /Y
xcopy "%SDKDIR%\x64\Release\*" "%~dp0x64\Release\" /E /I /Y
@ECHO OFF
set CURDIR=%~dp0
set DLLDIR=%~dp0x64\Release\
md build
cd build
cmake -DCMAKE_CONFIGURATION_TYPES=Release .. -G "Visual Studio 17 2022"
cmake --build . --config Release

xcopy "%SDKDIR%\x64\Release\*" "%QTDIR%\bin" /E /I /Y
xcopy "%~dp0x64\Release\StyleSystem.dll" "%QTDIR%\plugins\designer"  /E /I /Y
xcopy "%~dp0x64\Release\DesignerPlugin.dll" "%QTDIR%\plugins\designer"  /E /I /Y
xcopy "%~dp0x64\Release\MyCustomUiWidget.dll" "%QTDIR%\bin"  /E /I /Y
xcopy "%~dp0x64\Release\SDK.dll" "%QTDIR%\bin"  /E /I /Y
xcopy "%~dp0x64\Release\StyleSystem.dll" "%QTDIR%\bin"  /E /I /Y
pause
