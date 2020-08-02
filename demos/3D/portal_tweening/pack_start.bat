@ECHO OFF
REM Define variables here.
set PALM_CREATOR_ID=MDD5
set PACKDIR=..\..\..\Tools\packdir
set PDNAME=pdportween
set TARGET_WIN32_VS2005=target\win32\vs2005
set TARGET_WIN32_VS6=target\win32\vs6
set TARGET_WINCE_VS2005=target\ppc2003\vs2005
set TARGET_WINCE_EVC4=target\ppc2003\evc4
set TARGET_S60=target\s60
set TARGET_UIQ=target\uiq
set TARGET_PALM=target\palm

echo ================================================================
echo Make packdir.fat and packdir.dat
echo ================================================================

%PACKDIR%\packdir.exe data

echo ================================================================
echo Make files for Win32 (VS2005)
echo ================================================================

copy /y packdir.fat %TARGET_WIN32_VS2005%\%PDNAME%.fat
copy /y packdir.dat %TARGET_WIN32_VS2005%\%PDNAME%.dat

echo ================================================================
echo Make files for Win32 (VS6)
echo ================================================================

copy /y packdir.fat %TARGET_WIN32_VS6%\%PDNAME%.fat
copy /y packdir.dat %TARGET_WIN32_VS6%\%PDNAME%.dat


echo ================================================================
echo Make files for WinCE (VS2005)
echo ================================================================

copy /y packdir.fat %TARGET_WINCE_VS2005%\%PDNAME%.fat
copy /y packdir.dat %TARGET_WINCE_VS2005%\%PDNAME%.dat

echo ================================================================
echo Make files for WinCE (EVC4)
echo ================================================================

copy /y packdir.fat %TARGET_WINCE_EVC4%\%PDNAME%.fat
copy /y packdir.dat %TARGET_WINCE_EVC4%\%PDNAME%.dat


echo ================================================================
echo Make files for S60
echo ================================================================

copy /y packdir.fat %TARGET_S60%\%PDNAME%.fat
copy /y packdir.dat %TARGET_S60%\%PDNAME%.dat

echo ================================================================
echo Make files for UIQ
echo ================================================================

copy /y packdir.fat %TARGET_UIQ%\%PDNAME%.fat
copy /y packdir.dat %TARGET_UIQ%\%PDNAME%.dat


echo ================================================================
echo Make files for PALM
echo ================================================================

ren packdir.dat %PDNAME%.dat
ren packdir.fat %PDNAME%.fat

%PACKDIR%\packpdb.exe %PDNAME%.dat %PALM_CREATOR_ID%
%PACKDIR%\pdbc.exe result.pdbc
move /y out.pdb %TARGET_PALM%\%PDNAME%dat.pdb

%PACKDIR%\packpdb.exe %PDNAME%.fat %PALM_CREATOR_ID%
%PACKDIR%\pdbc.exe result.pdbc
move /y out.pdb %TARGET_PALM%\%PDNAME%fat.pdb

echo ================================================================
echo Deleting temporary  files
echo ================================================================

del packdir.inc

del %PDNAME%.dat
del %PDNAME%.fat

del volume*.bin
del result.pdbc

pause