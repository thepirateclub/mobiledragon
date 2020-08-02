@echo off
type MDTweening.mmp.temp > MDTweening.mmp
echo. >> MDTweening.mmp
echo USERINCLUDE ..\..\..\sources >> MDTweening.mmp
echo SOURCEPATH ..\..\..\sources >> MDTweening.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MDTweening.mmp