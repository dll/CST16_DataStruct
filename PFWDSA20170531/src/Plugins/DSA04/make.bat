rem build PFWDSA plugin file make.bat 


DSA04.obj: DSA04.c
        cl -c DSA04.C

TestDSA04.obj: TestDSA04.C
        cl -c TestDSA04.C
TestDSA04.dll : DSA04.def TestDSA04.obj DSA04.obj
	link -def:DSA04.def -dll TestDSA04.obj DSA04.obj

copy DSA04.dll ..\\..\\..\\bin\\Plugins\\
copy DSA04.txt ..\\..\\..\\bin\\Plugins\\
copy DSA041.dat ..\\..\\..\\bin\\Data\\

del TestDSA04.obj TestDSA04.dll TestDSA04.exp TestDSA04.lib DSA04.obj DSA04.dll

rem pause

exit

