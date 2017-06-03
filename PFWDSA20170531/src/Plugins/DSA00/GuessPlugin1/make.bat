pguess.obj: pguess.c
        cl -c pguess.c

copy pguess.obj ..\obj

del pguess.obj

rem pause

exit