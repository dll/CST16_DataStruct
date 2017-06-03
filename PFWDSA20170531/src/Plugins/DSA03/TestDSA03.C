/*
*文件：TestDSA02.C
*插件文件，实现链表的测试文件，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include "DSA03.h"

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

char LinkListMenu(LinkList *LL);

void DSAInterface(void){

	char flag;
	LinkList LL;
	flag='b';
	CreateLinkList(&LL, 0);
	while(flag !='Q' && flag != 'q'){
		system("CLS");//清屏
		flag = LinkListMenu(&LL);//链表操作	
		system("PAUSE");//暂停
	}	
	ClearLinkList(&LL);//销毁
}

char LinkListMenu(LinkList *LL){

	int i, n, j, speed;
	ElemType x;
	char c, r;
	char fname[20];
	char tempFolder[100]=".\\Temp\\";

	printf("******************************** 链表操作 ********************************\n\n");
	printf(" 初始化操作：InitList初始化表[I/i]\n\n");
	printf(" 销毁操作：Clear销毁表[C/c]、Quit退出[Q/q]\n\n");
	printf(" 引用型操作：Find查找[F/f]、Save保存[S/s]、Print打印[P/p]\n\n");
	printf(" 加工型操作：Read读取[R/r]、Add插入[A/a]、Delete删除[D/d]、Edit编辑[E/e]\n\n");
	printf("***************************************************************************\n\n");
	printf("请输入首字符选择链表的操作:\t");flushall();
	c= getchar();
	switch(c){
		case 'I':
		case 'i':
			printf("创建几个节点的链表?\n");
			scanf("%d", &n);
			CreateLinkList(LL, n);
			printf("创建了%d个节点的链表!\n", n);
			break;
		case 'C':
		case 'c':
			ClearLinkList(LL);
			break;
		case 'R':
		case 'r':
			printf("从文件读取中链表数据,如：DSA031.tmp\t");
			scanf("%s", fname);
			strcat(tempFolder, fname);
			ReadLinkList(*LL,tempFolder);
			PrintLinkList(*LL);			
			break;
		case 'A':
		case 'a':
			if(GetLinkListLength(*LL)==0)
				i=1;
			else
				i = (int)RandElem(1, GetLinkListLength(*LL));
			printf("输入[r]robot自动完成。否则,人工输入...\n");	flushall();
			if((r=getchar())=='r'){
				printf("输入插入多少元素和动画速度如100毫秒?\t");
				scanf("%d %d", &n, &speed);
				for(j=0;j<n-1;j++){
					x=RandElem(j, n);
					InsertLinkListElem(*LL, i, x, speed);
					i = (int)RandElem(1, GetLinkListLength(*LL));
				}
			}
			else{
				printf("输入插入位置和元素(表长为%d):\t",GetLinkListLength(*LL));
				scanf("%d %d", &i, &x);
			}
			printf("向链表LL的%d位置上插入元素 %d :\n",i, x);
			InsertLinkListElem(*LL, i, x, speed);
			PrintLinkList(*LL);			
			break;
		case 'D':
		case 'd':
			PrintLinkList(*LL);	
			if(GetLinkListLength(*LL)==0)
				return 'q';
			printf("删除哪个位序上的什么节点和动画速度如100毫秒?\t");
			scanf("%d %d %d", &i,  &x, &speed);
			if(DeleteLinkListElem(*LL, i, &x,speed))
				printf("从链表LL的%d位置上删除元素 %d \n",i, x);
			else
				printf("删除失败!\n");
			break;
		case 'E':
		case 'e':
			if(GetLinkListLength(*LL)==0){
				printf("链表为空表，返回!\n");
				return 'q';
			}
			printf("修改哪个位置上的节点,请输入位序:\t");
			scanf("%d", &i);
			if(	GetLinkListElem(*LL, i, &x) != 0){
				printf("链表LL的%d位置上元素 %d 被修改为:\t",i, x);
				scanf("%d", &x);
				EditLinkListElem(*LL, i, x);
				PrintLinkList(*LL);			
			}
			else
				printf("修改失败!\n");
			break;
		case 'F':
		case 'f':			
			printf("查找哪个节点(不是位序)? \t");
			scanf("%d", &x);
			if(	i=LocateLinkListElem(*LL, x) != 0)
				printf("链表LL的%d位置上为查找的元素 %d \n",i, x);
			else
				printf("查找失败!\n");
			break;
		case 'S':
		case 's':			
			printf("保存链表数据到文件中,如：DSA031.tmp\t");
			scanf("%s", fname);
			strcat(tempFolder, fname);
			SaveLinkList(*LL, tempFolder);
			break;

		case 'P':
		case 'p':
			PrintLinkList(*LL);//打印			
			break;
		case 'Q':
		case 'q':
			return c;//退出线性表
		default:
			printf("请输入链表操作的首字符,Q/q退出!\n");
			break;
	}
	return NULL;
}