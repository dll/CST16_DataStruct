rem build PFWDSA plugin file make.bat 


DSA11.obj: DSA11.c DSA11.h
        cl -c DSA11.C

TestDSA11.obj: TestDSA11.C DSA11.h
        cl -c TestDSA11.C
TestDSA11.dll : DSA11.def TestDSA11.obj DSA11.obj
	link -def:DSA11.def -dll TestDSA11.obj DSA11.obj

copy DSA11.dll ..\..\..\bin\Plugins\
copy DSA11.txt ..\..\..\bin\Plugins\
copy DSA111.dat ..\..\..\bin\Data\

del TestDSA11.obj TestDSA11.dll TestDSA11.exp TestDSA11.lib DSA11.obj DSA11.dll

rem pause

exit