/*
*�ļ���DSA13.C
*����ļ����ַ��й���ͼ��DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-12-27
*/

#include"DSA13.h"

char gVersion[20];
char gInterface[20];
//�����Ϣ
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
//�����ܵĽӿ�

void DSAInterface(void){
	int i=0;
	while(i!=4){
		system("CLS");
		printf("\n\t�ַ��й����е�ͼ\
			\n����������ѡ��:\n1 ���й�\n2 ����ͶӰ\
			\n3 ��ͶӰ\n4 �˳�\n");
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
