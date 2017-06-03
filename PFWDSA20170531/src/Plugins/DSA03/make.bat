rem build PFWDSA plugin file make.bat 


DSA03.obj: DSA03.c
        cl -c DSA03.C

TestDSA03.obj: TestDSA03.C
        cl -c TestDSA03.C
TestDSA03.dll : DSA03.def TestDSA03.obj DSA03.obj
	link -def:DSA03.def -dll TestDSA03.obj DSA03.obj

copy DSA03.dll ..\..\..\bin\Plugins\
copy DSA03.txt ..\..\..\bin\Plugins\


del TestDSA03.obj TestDSA03.dll TestDSA03.exp TestDSA03.lib DSA03.obj DSA03.dll

rem pause

exit

