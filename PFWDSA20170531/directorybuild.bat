rem 这是创建目录结构的bat文件

MD src bin
CD bin 
MD Plugins
MD Data
MD Temp

CD..
CD src
ECHO To write make.bat>readme.txt
ECHO rem write bat to build PFWDSA.EXE and all Plugins>make.bat
MD HostApp Plugins
CD HostApp
MD BaseServices
MD PluginManager
MD DSATestServices
ECHO To write bat to build PFWDSA.EXE>readme.txt

CD..
CD Plugins
MD DSA00 DSA01 DSA02 DSA03 DSA04 DSA05 DSA06 DSA07 DSA08 DSA09  DSA10 

CD..
CD..
CD bin
MD Plugins
ECHO To execute PFWDSA.EXE>readme.txt
 