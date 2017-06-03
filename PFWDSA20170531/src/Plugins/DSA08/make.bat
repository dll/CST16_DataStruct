rem build PFWDSA plugin file make.bat 


DSA08.obj: DSA08.c DSA08.h
        cl -c DSA08.C

TestDSA08.obj: TestDSA08.C DSA08.h
        cl -c TestDSA08.C
TestDSA08.dll : DSA08.def TestDSA08.obj DSA08.obj
	link -def:DSA08.def -dll TestDSA08.obj DSA08.obj

copy DSA08.dll ..\..\..\bin\Plugins\
copy DSA08.txt ..\..\..\bin\Plugins\
copy DSA081.dat ..\..\..\bin\Data\
copy DSA082.dat ..\..\..\bin\Data\
copy DSA083.dat ..\..\..\bin\Data\
copy DSA084.dat ..\..\..\bin\Data\

del TestDSA08.obj TestDSA08.dll TestDSA08.exp TestDSA08.lib DSA08.obj DSA08.dll

rem pause

exit

