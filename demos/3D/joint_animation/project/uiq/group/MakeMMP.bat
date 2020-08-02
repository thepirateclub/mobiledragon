@echo off
type MDJoint.mmp.temp > MDJoint.mmp
echo. >> MDJoint.mmp
echo USERINCLUDE ..\..\..\sources >> MDJoint.mmp
echo SOURCEPATH ..\..\..\sources >> MDJoint.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MDJoint.mmp