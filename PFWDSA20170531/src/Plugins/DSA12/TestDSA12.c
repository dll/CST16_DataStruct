/*
*文件：TestDSA12.C
*插件文件，图，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA12.h"

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


void TestSeqSearch1(void);
void TestSeqSearch2(void);
void TestBinSearch(void);


//声明一个包含函数指针和菜单的结构体
struct {
	void (*fun)(void); //声明一个函数指针
	char *menu;
}FindMenu[] = {   //结构体初始化
	{ TestSeqSearch1, "顺序查找1"},
	{ TestSeqSearch2, "顺序查找2"},
	{ TestBinSearch, "二分查找"},
    { 0, 0}      
};

void DSAInterface(void){
	int idx,i;
	while(1){   
		printf("\n\t\t===========================\n");
		printf("\t\t|       查找算法菜单      |\n");
		printf("\t\t---------------------------\n");
		for(i=0; FindMenu[i].fun!=0; i++)
			printf("\t\t| %2d:  %-15s    |\n", i, FindMenu[i].menu);
		printf("\t\t===========================\n");
		printf("\t请输入菜单序号并按ENTER键([-1]返回):");
		scanf("%d",&idx);  
		if(idx<i)
		{	
			if(-1==idx)return;
			(*FindMenu[idx].fun)();
		}
		else printf("\t你输入错误的数字[%d];请重新输入!\n", idx);
	}
}

void TestSeqSearch1(void){

}

void TestSeqSearch2(void){

}

void TestBinSearch(void){

}
