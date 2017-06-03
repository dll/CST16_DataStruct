rem build PFWDSA plugin file make.bat 

DSA09.obj: DSA09.c DSA09.h
        cl -c DSA09.C

TestDSA09.obj: TestDSA09.C DSA09.h
        cl -c TestDSA09.C
TestDSA09.dll : DSA09.def TestDSA09.obj DSA09.obj
	link -def:DSA09.def -dll TestDSA09.obj DSA09.obj

copy DSA09.dll ..\..\..\bin\Plugins\
copy DSA09.txt ..\..\..\bin\Plugins\
copy DSA091.dat ..\..\..\bin\Data\
copy DSA092.dat ..\..\..\bin\Data\
copy DSA093.dat ..\..\..\bin\Data\

del TestDSA09.obj TestDSA09.dll TestDSA09.exp TestDSA09.lib DSA09.obj DSA09.dll

rem pause

exit

