@echo off
type MD2DScene.mmp.temp > MD2DScene.mmp
echo. >> MD2DScene.mmp
echo USERINCLUDE ..\..\..\sources >> MD2DScene.mmp
echo SOURCEPATH ..\..\..\sources >> MD2DScene.mmp
for %%i in (../../../sources/*.cpp) do echo SOURCE %%i >> MD2DScene.mmp