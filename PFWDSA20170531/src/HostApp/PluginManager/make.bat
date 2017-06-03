PluginManager.obj: PluginManager.c
        cl -c PluginManager.c
PluginManager.lib : PluginManager.obj
	lib PluginManager.obj
CD..
MD lib
copy PluginManager\PluginManager.lib lib
rem copy PluginManager\PluginManager.lib ..\Plugins\DSA00\lib

del PluginManager\PluginManager.lib PluginManager\PluginManager.obj

rem pause

exit