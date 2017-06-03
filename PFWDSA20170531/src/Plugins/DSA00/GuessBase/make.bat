bguess.obj: bguess.c
        cl -c bguess.c
bguess.lib : bguess.obj
	lib bguess.obj
CD..
MD lib
copy GuessBase\bguess.lib lib\GuessBase.lib
copy GuessBase\bguess.h include\GuessBase.h

del GuessBase\bguess.lib GuessBase\bguess.obj

rem pause

exit