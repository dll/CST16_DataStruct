rem build PFWDSA plugin file make.bat 


DSA07.obj: DSA07.c DSA07.h
        cl -c DSA07.C

TestDSA07.obj: TestDSA07.C DSA07.h
        cl -c TestDSA07.C
TestDSA07.dll : DSA07.def TestDSA07.obj DSA07.obj
	link -def:DSA07.def -dll TestDSA07.obj DSA07.obj

copy DSA07.dll ..\..\..\bin\Plugins\
copy DSA07.txt ..\..\..\bin\Plugins\
copy DSA071.dat ..\..\..\bin\Data\
copy DSA072.dat ..\..\..\bin\Data\
copy DSA073.dat ..\..\..\bin\Data\
copy DSA074.dat ..\..\..\bin\Data\

del TestDSA07.obj TestDSA07.dll TestDSA07.exp TestDSA07.lib DSA07.obj DSA07.dll

rem pause

exit

