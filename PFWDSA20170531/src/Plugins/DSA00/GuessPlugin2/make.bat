rguess.obj: rguess.c
        cl -c rguess.c
copy rguess.obj ..\obj
rem pause

del rguess.obj

exit
