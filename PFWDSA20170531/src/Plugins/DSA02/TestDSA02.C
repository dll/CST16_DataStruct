/*
*文件：TestDSA02.C
*插件文件，实现顺序列表，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/
#include "DSA02.h"

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
char SeqListMenu(SeqList *SL);

void DSAInterface(void){

	char flag;
	SeqList SL;
	InitSeqList2(&SL);//初始化
	flag='b';
	while(flag !='Q' && flag != 'q'){		
		system("CLS");//清屏
		flag = SeqListMenu(&SL);//顺序表操作	
		system("PAUSE");//暂停
	}

	ClearSeqList(&SL);//销毁
}

char SeqListMenu(SeqList *SL){

	int i, n, j, speed;
	ElemType x;
	char c, r;
	char fname[20];
	char tempFolder[100]=".\\Temp\\";

	printf("****************************** 顺序表操作 ********************************\n\n");
	printf(" 初始化操作：InitList初始化表[I/i]\n\n");
	printf(" 销毁操作：Clear销毁表[C/c]、Quit退出[Q/q]\n\n");
	printf(" 引用型操作：Find查找[F/f]、Save保存[S/s]、Print打印[P/p]\n\n");
	printf(" 加工型操作：Read读取[R/r]、Add插入[A/a]、Delete删除[D/d]、Edit编辑[E/e]\n\n");
	printf("***************************************************************************\n\n");
	printf("请输入首字符选择顺序表的操作:\t");flushall();
	c= getchar();
	switch(c){
		case 'I':
		case 'i':
			InitSeqList2(SL);
			printf("创建了一个长度为%d的空的顺序表!\n",SL->listsize);
			break;
		case 'C':
		case 'c':
			ClearSeqList(SL);
			break;
		case 'R':
		case 'r':
			printf("从文件读取中顺序表数据,如：DSA021.tmp\t");
			scanf("%s", fname);
			strcat(tempFolder, fname);
			ReadSeqList(SL,tempFolder);
			SeqListPrint2(SL);			
			break;
		case 'A':
		case 'a':
			if(SL->length==0)
				i=1;
			else
				i = (int)RandElem(1, SL->length);
			printf("输入[r]robot自动完成。否则,人工输入...\n");	flushall();
			if((r=getchar())=='r'){
				printf("输入插入多少元素和动画速度如100毫秒?\t");
				scanf("%d %d", &n, &speed);
				for(j=0;j<n-1;j++){
					x=RandElem(j, n);
					SeqListInsert(SL, i, x, speed);
					i = (int)RandElem(1, SL->length);
				}
			}
			else{
				printf("输入插入位置和元素(表长为%d):\t",SL->length);
				scanf("%d %d", &i, &x);
			}
			printf("向顺序表SL的%d位置上插入元素 %d :\n",i, x);
			SeqListInsert(SL, i, x, speed);
			SeqListPrint2(SL);			
			break;
		case 'D':
		case 'd':
			SeqListPrint2(SL);	
			if(GetSeqListLength(SL)==0)
				return 'q';
			printf("删除哪个节点(不是位序) 和动画速度如100毫秒?\t");
			scanf("%d %d", &x, &speed);
			i=LocateSeqListElem(SL, x);
			if(SeqListDelete(SL, i, &x,speed))
				printf("从顺序表SL的%d位置上删除元素 %d \n",i, x);
			else
				printf("删除失败!\n");
			break;
		case 'E':
		case 'e':
			if(GetSeqListLength(SL)==0){
				printf("顺序表为空表，返回!\n");
				return 'q';
			}
			printf("修改哪个位置上的节点,请输入位序:\t");
			scanf("%d", &i);
			if( GetSeqListElem(SL, i, &x) != 0){
				printf("顺序表SL的%d位置上元素 %d 被修改为:\t",i, x);
				scanf("%d", &x);
				SeqListEdit(SL, i, x);
				SeqListPrint2(SL);			
			}
			else
				printf("修改失败!\n");
			break;
		case 'F':
		case 'f':			
			printf("查找哪个节点(不是位序)? \t");
			scanf("%d", &x);
			if(	i=LocateSeqListElem(SL, x) != 0)
				printf("顺序表SL的%d位置上为查找的元素 %d \n",i, x);
			else
				printf("查找失败:顺序表里没有%d 元素!\n", x);
			break;
		case 'S':
		case 's':			
			printf("保存顺序表数据到文件中,如：DSA021.tmp\t");
			scanf("%s", fname);
			strcat(tempFolder, fname);
			SeqListSave(SL,tempFolder);
			SeqListSave(SL, fname);
			break;

		case 'P':
		case 'p':
			SeqListPrint2(SL);//打印			
			break;
		case 'Q':
		case 'q':
			return c;//退出线性表
		default:
			printf("请输入顺序表操作的首字符,Q/q退出!\n");
			break;
	}
	return NULL;
}