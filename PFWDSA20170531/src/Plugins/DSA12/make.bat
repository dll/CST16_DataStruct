rem build PFWDSA plugin file make.bat 


DSA12.obj: DSA12.c DSA12.h
        cl -c DSA12.C

TestDSA12.obj: TestDSA12.C DSA12.h
        cl -c TestDSA12.C
TestDSA12.dll : DSA12.def TestDSA12.obj DSA12.obj
	link -def:DSA12.def -dll TestDSA12.obj DSA12.obj

copy DSA12.dll ..\..\..\bin\Plugins\
copy DSA12.txt ..\..\..\bin\Plugins\
copy DSA121.dat ..\..\..\bin\Data\

del TestDSA12.obj TestDSA12.dll TestDSA12.exp TestDSA12.lib DSA12.obj DSA12.dll

pause

exit