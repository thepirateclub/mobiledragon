@echo off
type MDParticles.mmp.temp > MDParticles.mmp
echo. >> MDParticles.mmp
echo USERINCLUDE ..\..\..\sources >> MDParticles.mmp
echo SOURCEPATH ..\..\..\sources >> MDParticles.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MDParticles.mmp