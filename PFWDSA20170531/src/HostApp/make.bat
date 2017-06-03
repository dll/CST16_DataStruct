cd BaseServices
start make.bat
cd..

cd PluginManager
start make.bat
cd..

cd DSATestServices
start make.bat
cd..

PFWDSA.obj : PFWDSA.c
        cl -c PFWDSA.c

PFWDSA.exe: PFWDSA.obj lib\BaseServices.lib lib\PluginManager.lib bin\DSATestServices.lib
        link PFWDSA.obj lib\BaseServices.lib lib\PluginManager.lib bin\DSATestServices.lib
copy PFWDSA.exe ..\..\bin
copy PFWDSA.txt ..\..\bin

del PFWDSA.obj PFWDSA.exe

rem pause

exit