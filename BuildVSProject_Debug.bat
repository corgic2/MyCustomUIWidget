set "SDKDIR=D:\WorkSpace\MySdk"

xcopy "%SDKDIR%\include\*.h" "%~dp0include\" /E /I /Y
xcopy "%SDKDIR%\x64\Debug\*" "%~dp0x64\Debug\" /E /I /Y
@ECHO OFF
set CURDIR=%~dp0
set DLLDIR=%~dp0x64\Debug\
md build
cd build
cmake -DCMAKE_CONFIGURATION_TYPES=Debug .. -G "Visual Studio 17 2022"
cmake --build . --config Debug

@REM windeployqt
if defined QT_DIR (
    set QTDIR=%QT_DIR%
) else (
    set QTDIR=D:/Qt/5.15.2/msvc2019_64
)

pause
