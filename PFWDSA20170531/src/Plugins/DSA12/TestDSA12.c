/*
*�ļ���TestDSA12.C
*����ļ���ͼ��DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include"DSA12.h"

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


void TestSeqSearch1(void);
void TestSeqSearch2(void);
void TestBinSearch(void);


//����һ����������ָ��Ͳ˵��Ľṹ��
struct {
	void (*fun)(void); //����һ������ָ��
	char *menu;
}FindMenu[] = {   //�ṹ���ʼ��
	{ TestSeqSearch1, "˳�����1"},
	{ TestSeqSearch2, "˳�����2"},
	{ TestBinSearch, "���ֲ���"},
    { 0, 0}      
};

void DSAInterface(void){
	int idx,i;
	while(1){   
		printf("\n\t\t===========================\n");
		printf("\t\t|       �����㷨�˵�      |\n");
		printf("\t\t---------------------------\n");
		for(i=0; FindMenu[i].fun!=0; i++)
			printf("\t\t| %2d:  %-15s    |\n", i, FindMenu[i].menu);
		printf("\t\t===========================\n");
		printf("\t������˵���Ų���ENTER��([-1]����):");
		scanf("%d",&idx);  
		if(idx<i)
		{	
			if(-1==idx)return;
			(*FindMenu[idx].fun)();
		}
		else printf("\t��������������[%d];����������!\n", idx);
	}
}

void TestSeqSearch1(void){

}

void TestSeqSearch2(void){

}

void TestBinSearch(void){

}
