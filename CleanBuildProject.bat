echo off
setlocal EnableExtensions EnableDelayedExpansion

set enginepath=D:\Epic\UE_5.5\Engine

echo Deleting Binaries
del *.sln
rmdir /s /q .vs
FOR /d /r . %%d IN ("Binaries") DO @IF EXIST "%%d" rd /s /q "%%d"


echo Deleting Intermediate
FOR /d /r . %%d IN ("Intermediate") DO @IF EXIST "%%d" rd /s /q "%%d"
FOR /d /r . %%d IN ("DerivedDataCache") DO @IF EXIST "%%d" rd /s /q "%%d"
FOR /d /r . %%d IN ("Saved") DO @IF EXIST "%%d" rd /s /q "%%d"


set	UVS="C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"
set UBT="%enginepath%\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"


%UVS% /switchversionsilent %cd%\TimberWork.uproject %enginepath%

echo Generating project files

%UVS% /projectfiles %cd%\TimberWork.uproject

echo Compiling project

%UBT% Development Win64 -Project=%cd%\TimberWork.uproject -TargetType=Editor -Progress -NoHotReloadFromIDE

pause

