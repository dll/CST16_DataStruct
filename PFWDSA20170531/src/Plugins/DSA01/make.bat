rem build PFWDSA plugin file make.bat 


DSA01.obj: DSA01.c
        cl -c DSA01.C

TestDSA01.obj: TestDSA01.C
        cl -c TestDSA01.C
TestDSA01.dll : DSA01.def TestDSA01.obj DSA01.obj ..\..\HostApp\bin\DSATestServices.lib
	link  ..\..\HostApp\bin\DSATestServices.lib -def:DSA01.def -dll TestDSA01.obj DSA01.obj

if not exist ..\..\..\bin\Plugins md ..\..\..\bin\Plugins

copy DSA01.dll ..\..\..\bin\Plugins\
copy DSA01.txt ..\..\..\bin\Plugins\

del TestDSA01.obj TestDSA01.dll TestDSA01.exp TestDSA01.lib DSA01.obj DSA01.dll

rem pause

exit

