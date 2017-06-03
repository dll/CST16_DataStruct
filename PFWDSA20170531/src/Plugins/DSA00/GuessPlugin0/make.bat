dguess.obj: dguess.c
        cl -c dguess.c

copy dguess.obj ..\obj
rem pause

del dguess.obj

exit
