rem write bat to build PFWDSA.EXE and all Plugins in Plugins folder

cd HostApp
start make.bat
cd..

cd Plugins
start make.bat

rem pause

exit
