@echo off
setlocal ENABLEDELAYEDEXPANSION

set "CLIENT_PARAMETERS= -game -log -ResX=1280 -ResY=720 -WINDOWED"

set "PROJECT_NAME=%~dp0\TimberWork.uproject"

set UE_PATH="D:\Epic\UE_5.5\Engine\Binaries\Win64\UnrealEditor.exe"
set "PROJECT_PATH=%PROJECT_NAME%"
set "CLIENT_COMMAND=!UE_PATH! %PROJECT_PATH% %CLIENT_PARAMETERS%"

start "%PROJECT_NAME% - Client" %CLIENT_COMMAND%
