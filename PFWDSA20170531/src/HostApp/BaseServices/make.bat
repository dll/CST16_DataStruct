BaseServices.obj: BaseServices.c
        cl -c BaseServices.c
BaseServices.lib : BaseServices.obj
	lib BaseServices.obj
CD..
MD lib
copy BaseServices\BaseServices.lib lib
copy BaseServices\BaseServices.lib PFWDSASDK\lib
rem copy BaseServices\BaseServices.lib ..\Plugins\DSA00\lib
 
del BaseServices\BaseServices.lib BaseServices\BaseServices.obj

rem pause

exit