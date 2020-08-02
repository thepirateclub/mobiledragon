@echo off
type MDPortals.mmp.temp > MDPortals.mmp
echo. >> MDPortals.mmp
echo USERINCLUDE ..\..\..\sources >> MDPortals.mmp
echo SOURCEPATH ..\..\..\sources >> MDPortals.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MDPortals.mmp