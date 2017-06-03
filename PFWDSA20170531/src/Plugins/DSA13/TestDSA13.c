/*
*文件：DSA13.C
*插件文件，字符中国地图，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-12-27
*/

#include"DSA13.h"

char gVersion[20];
char gInterface[20];
//插件信息
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			strcpy(gVersion,"1.0.0");
			strcpy(gInterface,"DSAInterface");
			break;
		case DLL_THREAD_ATTACH:	
		case DLL_THREAD_DETACH:		
		case DLL_PROCESS_DETACH:	
			break;
    }
    return TRUE;
}
char* GetPluginVersion(){
	return gVersion;
}
char* GetPluginInterface(){
	return gInterface;
}
//插件框架的接口

void DSAInterface(void){
	int i=0;
	while(i!=4){
		system("CLS");
		printf("\n\t字符中国城市地图\
			\n请输入数字选择:\n1 嗨中国\n2 不带投影\
			\n3 带投影\n4 退出\n");
		flushall();
		scanf("%d", &i);
		switch(i){
			case 1:
				system(".\\Plugins\\DSA13.exe");break;
			case 2:
				NUProChinaCityMap();break;
			case 3:
				ProChinaCityMap();break;
			case 4:
				return;
		}
		system("PAUSE");
	}
}
