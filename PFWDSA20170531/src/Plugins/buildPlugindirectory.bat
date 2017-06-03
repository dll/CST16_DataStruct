set pi=..\..\bin\Plugins
if not exist %pi% md %pi%

MD DSA10
CD DSA10
ECHO DSA10.dll>DSA10.txt
ECHO n1.0.0>>DSA10.txt
ECHO 学号姓名>>DSA10.txt
ECHO 2012-09-19>>DSA10.txt
ECHO 详细介绍插件功能。>>DSA10.txt

ECHO //PFWDSA plugin source file DSA10.c>DSA10.c
ECHO #include "DSA10.h">>DSA10.c
ECHO.>>DSA10.c
ECHO.>>DSA10.c
ECHO //插件版本：dll中导出全局变量gVersion>>DSA10.c
ECHO char gVersion[20];>>DSA10.c
ECHO.>>DSA10.c
ECHO //在DllMain中对插件版本赋值>>DSA10.c
ECHO BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)>>DSA10.c
ECHO {>>DSA10.c
ECHO     switch (ul_reason_for_call)>>DSA10.c
ECHO 	{>>DSA10.c
ECHO 	case DLL_PROCESS_ATTACH:>>DSA10.c
ECHO 		strcpy(gVersion,"1.0.0");>>DSA10.c
ECHO 		break;>>DSA10.c
ECHO 	case DLL_THREAD_ATTACH:	>>DSA10.c
ECHO 	case DLL_THREAD_DETACH:	>>DSA10.c	
ECHO 	case DLL_PROCESS_DETACH:>>DSA10.c	
ECHO 		break;>>DSA10.c
ECHO     }>>DSA10.c
ECHO     return TRUE;>>DSA10.c
ECHO }>>DSA10.c
ECHO.>>DSA10.c
ECHO //插件版本：dll中导出函数，获得插件版本。这是C#属性的雏形>>DSA10.c
ECHO char* GetPluginVersion(){>>DSA10.c
ECHO 	return gVersion;>>DSA10.c
ECHO }>>DSA10.c
ECHO.>>DSA10.c
ECHO void DSAInterface(void){>>DSA10.c
ECHO //插件接口，写功能函数（相当于main函数）>>DSA10.c
ECHO.>>DSA10.c
ECHO.>>DSA10.c
ECHO }>>DSA10.c


ECHO //PFWDSA plugin head file DSA10.h>DSA10.h
ECHO #ifndef DSA00_H>>DSA10.h
ECHO #define DSA00_H>>DSA10.h
ECHO.>>DSA10.h
ECHO #include^<stdio.h^> >>DSA10.h
ECHO #include^<stdlib.h^> >>DSA10.h
ECHO #include^<windows.h^> >>DSA10.h
ECHO #include^<time.h^> >>DSA10.h
ECHO.>>DSA10.h
ECHO.>>DSA10.h
ECHO void DSAInterface(void);>>DSA10.h
ECHO extern char gVersion[20];>>DSA10.h
ECHO extern char* GetPluginVersion(void);>>DSA10.h
ECHO.>>DSA10.h
ECHO #endif>>DSA10.h

ECHO ;PFWDSA plugin interface file DSA10.def>DSA10.def
ECHO LIBRARY "DSA10">>DSA10.def
ECHO.>>DSA10.def
ECHO EXPORTS>>DSA10.def
ECHO.>>DSA10.def
ECHO DSAInterface @11>>DSA10.def
ECHO gVersion DATA>>DSA10.def
ECHO GetPluginVersion @12>>DSA10.def

ECHO rem build PFWDSA plugin file make.bat >make.bat
ECHO.>>make.bat
ECHO DSA10.obj: DSA10.c >>make.bat
ECHO         cl -c DSA10.C>>make.bat
ECHO.>>make.bat
ECHO DSA10.obj: DSA10.C>>make.bat
ECHO         cl -c DSA10.C>>make.bat
ECHO DSA10.dll : DSA10.def DSA10.obj>>make.bat
ECHO 	link -def:DSA10.def -dll DSA10.obj>>make.bat
ECHO.>>make.bat
ECHO copy DSA10.dll ..\..\..\bin\Plugins\DSA10.dll>>make.bat
ECHO copy DSA10.txt ..\..\..\bin\Plugins\>>make.bat
ECHO.>>make.bat
ECHO del DSA10.obj DSA10.dll DSA10.exp DSA10.lib >>make.bat
ECHO.>>make.bat
ECHO pause>>make.bat
ECHO.>>make.bat
ECHO exit>>make.bat

ECHO About this plugin...>readme.txt

exit
 