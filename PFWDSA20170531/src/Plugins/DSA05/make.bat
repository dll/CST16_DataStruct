rem build PFWDSA plugin file make.bat 

DSA05.obj: DSA05.c DSA05.h
        cl -c DSA05.C

TestDSA05.obj: TestDSA05.C DSA05.h
        cl -c TestDSA05.C
TestDSA05.dll : DSA05.def TestDSA05.obj DSA05.obj
	link -def:DSA05.def -dll TestDSA05.obj DSA05.obj

copy DSA05.dll ..\..\..\bin\Plugins\
copy DSA05.txt ..\..\..\bin\Plugins\
copy DSA051.dat ..\..\..\bin\Data\
copy DSA052.dat ..\..\..\bin\Data\
copy DSA053.dat ..\..\..\bin\Data\

del TestDSA05.obj TestDSA05.dll TestDSA05.exp TestDSA05.lib DSA05.obj DSA05.dll

rem pause

exit

