call makemmp
call bldmake.bat bldfiles
call abld export
call abld clean armi urel
call abld build armi urel
pause