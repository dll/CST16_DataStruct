rem build PFWDSA plugin file make.bat 

DSA02.obj: DSA02.c
        cl -c DSA02.C

TestDSA02.obj: TestDSA02.C
        cl -c TestDSA02.C
TestDSA02.dll : DSA02.def TestDSA02.obj DSA02.obj
	link -def:DSA02.def -dll TestDSA02.obj DSA02.obj

set pi=..\..\..\bin\Plugins
if not exist %pi% md %pi%

copy DSA02.dll %pi%
copy DSA02.txt %pi%

del TestDSA02.obj TestDSA02.dll TestDSA02.exp TestDSA02.lib DSA02.obj DSA02.dll

rem pause

exit

