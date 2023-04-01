@ECHO OFF
SETLOCAL

@SET PROJECT_DIR=%~dp0
@IF "%PROJECT_DIR:~-1%" EQU "\" SET PROJECT_DIR=%PROJECT_DIR:~0,-1%

SET BUILD_DIR=%PROJECT_DIR%\build

if not exist "%BUILD_DIR%" MKDIR "%BUILD_DIR%"

pushd "%BUILD_DIR%"

set COMPILER=%VC64_CL%
IF "%COMPILER%" EQU "" SET COMPILER=cl

"%COMPILER%" /nologo /Zi "%PROJECT_DIR%\user_example.cpp" "%PROJECT_DIR%\api.cpp" 

@REM Compiler each driver into a separate DLL
"%COMPILER%" /nologo /Zi /LD "%PROJECT_DIR%\hdd_driver.cpp" /Fe: "hdd.dll" /link /EXPORT:GetFileDriver
"%COMPILER%" /nologo /Zi /LD "%PROJECT_DIR%\ssd_driver.cpp" /Fe: "ssd.dll" /link /EXPORT:GetFileDriver
"%COMPILER%" /nologo /Zi /LD "%PROJECT_DIR%\bluetooth_driver.cpp" /Fe: "bluetooth.dll" /link /EXPORT:GetFileDriver
"%COMPILER%" /nologo /Zi /LD "%PROJECT_DIR%\tcp_driver.cpp" /Fe: "tcp.dll" /link /EXPORT:GetFileDriver

popd

ENDLOCAL
EXIT /B 0
