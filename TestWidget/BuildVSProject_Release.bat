set "CustomWidget=D:\WorkSpace\MyCustomUIWidget"
set "QtDIR=D:\Qt\5.15.2\msvc2019_64"

xcopy "%CustomWidget%\x64\Release\*" "%~dp0x64\Release\" /E /I /Y
xcopy "%CustomWidget%\MyCustomUiWidget\*.h" "%~dp0include\" /E /I /Y
xcopy "%CustomWidget%\MyCustomUiWidget\*.ui" "%~dp0include\" /E /I /Y
xcopy "%CustomWidget%\StyleSystem\*.h" "%~dp0include\" /E /I /Y
md build
cd build
cmake -DCMAKE_CONFIGURATION_TYPES=Release .. -G "Visual Studio 17 2022"
cmake --build . --config Release

pause
