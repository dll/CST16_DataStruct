rem build PFWDSA plugin file make.bat 

cd HelloChina
start make.bat
cd..

DSA13.obj: DSA13.c DSA13.h
        cl -c DSA13.C

NUProChinaCityMap.obj: NUProChinaCityMap/NUProChinaCityMap.c DSA13.h
        cl -c NUProChinaCityMap/NUProChinaCityMap.C

ProChinaCityMap.obj: ProChinaCityMap/ProChinaCityMap.c DSA13.h ProChinaCityMap/ProChinaCityMap.h ProChinaCityMap/stdbool.h
        cl -c ProChinaCityMap/ProChinaCityMap.C

TestDSA13.obj: TestDSA13.C DSA13.h
        cl -c TestDSA13.C
TestDSA13.dll : DSA13.def TestDSA13.obj DSA13.obj NUProChinaCityMap.obj ProChinaCityMap.obj
	link -def:DSA13.def -dll TestDSA13.obj DSA13.obj NUProChinaCityMap.obj ProChinaCityMap.obj

copy DSA13.dll ..\\..\\..\\bin\\Plugins\\
copy DSA13.txt ..\\..\\..\\bin\\Plugins\\
copy DSA131.dat ..\\..\\..\\bin\\Data\\

del TestDSA13.obj TestDSA13.dll TestDSA13.exp TestDSA13.lib DSA13.obj DSA13.dll NUProChinaCityMap.obj ProChinaCityMap.obj

rem pause

exit