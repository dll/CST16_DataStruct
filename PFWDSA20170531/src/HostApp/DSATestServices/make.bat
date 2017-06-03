DSATestServices.obj: DSATestServices.c
        cl -c DSATestServices.c
DSATestServices.dll : DSATestServices.def DSATestServices.obj
	link -def:DSATestServices.def -dll DSATestServices.obj
CD..
MD bin
copy DSATestServices\DSATestServices.dll bin
copy DSATestServices\DSATestServices.dll ..\..\bin
copy DSATestServices\DSATestServices.lib bin

del DSATestServices\DSATestServices.dll  DSATestServices\DSATestServices.lib DSATestServices\DSATestServices.exp DSATestServices\DSATestServices.obj

rem pause

exit