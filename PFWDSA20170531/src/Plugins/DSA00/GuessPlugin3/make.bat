sguess.obj: sguess.c
        cl -c sguess.c
copy sguess.obj ..\obj
rem pause

del sguess.obj

exit
