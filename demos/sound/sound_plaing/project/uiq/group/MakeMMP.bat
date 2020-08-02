@echo off
type MDSound.mmp.temp > MDSound.mmp
echo. >> MDSound.mmp
echo USERINCLUDE ..\..\..\sources >> MDSound.mmp
echo SOURCEPATH ..\..\..\sources >> MDSound.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MDSound.mmp