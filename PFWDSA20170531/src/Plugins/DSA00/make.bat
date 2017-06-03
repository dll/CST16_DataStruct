DSA00.obj: DSA00.c
        cl -c DSA00.c
cd GuessPlugin0
start make.bat
cd..
cd GuessPlugin1
start make.bat
cd..
cd GuessPlugin2
start make.bat
cd..
cd GuessPlugin3
start make.bat
cd..
cd GuessPlugin4
start make.bat
cd..

DSA00.dll : DSA00.def DSA00.obj lib\GuessBase.lib ..\..\HostApp\bin\DSATestServices.lib obj\dguess.obj obj\pguess.obj obj\rguess.obj obj\sguess.obj obj\tguess.obj
	link lib\GuessBase.lib ..\..\HostApp\bin\DSATestServices.lib -def:DSA00.def -dll DSA00.obj obj\dguess.obj obj\pguess.obj obj\rguess.obj obj\sguess.obj obj\tguess.obj 

cd..
cd..
cd..
cd bin
md Plugins
cd..
cd src
cd Plugins
cd DSA00

copy DSA00.dll ..\..\..\bin\Plugins\
copy DSA00.txt ..\..\..\bin\Plugins\

del DSA00.obj DSA00.dll DSA00.exp DSA00.lib

rem pause

exit
