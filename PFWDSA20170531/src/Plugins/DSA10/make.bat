rem build PFWDSA plugin file make.bat 


DSA10.obj: DSA10.c DSA10.h
        cl -c DSA10.C

TestDSA10.obj: TestDSA10.C DSA10.h
        cl -c TestDSA10.C
TestDSA10.dll : DSA10.def TestDSA10.obj DSA10.obj
	link -def:DSA10.def -dll TestDSA10.obj DSA10.obj

copy DSA10.dll ..\\..\\..\\bin\\Plugins\\
copy DSA10.txt ..\\..\\..\\bin\\Plugins\\
copy DSA101.dat ..\\..\\..\\bin\\Data\\

del TestDSA10.obj TestDSA10.dll TestDSA10.exp TestDSA10.lib DSA10.obj DSA10.dll

rem pause

exit