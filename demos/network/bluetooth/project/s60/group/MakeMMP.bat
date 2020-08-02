@echo off
type MDBluetooth.mmp.temp > MDBluetooth.mmp
echo. >> MDBluetooth.mmp
echo USERINCLUDE ..\..\..\sources >> MDBluetooth.mmp
echo SOURCEPATH ..\..\..\sources >> MDBluetooth.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MDBluetooth.mmp