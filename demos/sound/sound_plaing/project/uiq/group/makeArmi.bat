call makemmp
call \Symbian\UIQ_21\epoc32\tools\bldmake bldfiles @UIQ_21:com.symbian.UIQ
call abld clean armi urel @UIQ_21:com.symbian.UIQ
call abld build armi urel @UIQ_21:com.symbian.UIQ
pause