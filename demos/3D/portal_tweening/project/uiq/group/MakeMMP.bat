@echo off
type MDPortTween.mmp.temp > MDPortTween.mmp
echo. >> MDPortTween.mmp
echo USERINCLUDE ..\..\..\sources >> MDPortTween.mmp
echo SOURCEPATH ..\..\..\sources >> MDPortTween.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MDPortTween.mmp