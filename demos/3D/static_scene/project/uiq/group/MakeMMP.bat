@echo off
type MDStatic.mmp.temp > MDStatic.mmp
echo. >> MDStatic.mmp
echo USERINCLUDE ..\..\..\sources >> MDStatic.mmp
echo SOURCEPATH ..\..\..\sources >> MDStatic.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MDStatic.mmp