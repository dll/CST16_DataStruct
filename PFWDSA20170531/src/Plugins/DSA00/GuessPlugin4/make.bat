tguess.obj: tguess.c
        cl -c tguess.c

copy tguess.obj ..\obj
rem pause

del tguess.obj

exit
