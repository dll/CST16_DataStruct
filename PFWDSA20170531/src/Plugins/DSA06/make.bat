rem build PFWDSA plugin file make.bat 

DSA06.obj: DSA06.c DSA06.h
        cl -c DSA06.C

TestDSA06.obj: TestDSA06.C DSA06.h
        cl -c TestDSA06.C
TestDSA06.dll : DSA06.def TestDSA06.obj DSA06.obj
	link -def:DSA06.def -dll TestDSA06.obj DSA06.obj

copy DSA06.dll ..\..\..\bin\Plugins\
copy DSA06.txt ..\..\..\bin\Plugins\
copy DSA061.dat ..\..\..\bin\Data\
copy DSA062.dat ..\..\..\bin\Data\
copy DSA063.dat ..\..\..\bin\Data\
copy DSA064.dat ..\..\..\bin\Data\

del TestDSA06.obj TestDSA06.dll TestDSA06.exp TestDSA06.lib DSA06.obj DSA06.dll

rem pause

exit

