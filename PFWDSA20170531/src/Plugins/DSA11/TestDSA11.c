/*
*�ļ���TestDSA11.C
*����ļ���ͼ��DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include"DSA11.h"

void TestStraightInsertSort ( void );
void TestBinInsertSort ( void );
void TestTwoInsertSort ( void );
void TestHeapSort(void);
void TestSLInsertSort(void);
void TestAdjustSLLink(void);
void TestShellInsertSort ( void );
void TestBubbleSort ( void );
void TestBetterBubbleSort ( void );
void TestHoareSort ( void );
void TestSimpleSelectSort (void );
void TestBetterSelectSort(void);
void TestHeapSort (void );
void TestMergeSort ( void );
void TestNRecurMergeSort ( void );
void TestCountSort ( void );
void TestRadixSort (void);

//����һ����������ָ��Ͳ˵��Ľṹ��
struct {
	void (*fun)(void); //����һ������ָ��
	char *menu;
}SortMenu[] = {   //�ṹ���ʼ��
	{ TestStraightInsertSort, "ֱ�Ӳ���"},
	{ TestBinInsertSort, "�۰����"},
	{ TestTwoInsertSort, "2·����"},
    { TestSLInsertSort, "��̬�������"},
    { TestAdjustSLLink, "�Ľ�����"},
	{ TestShellInsertSort, "ϣ������"},	
	{ TestBubbleSort, "ð��"},
	{ TestBetterBubbleSort, "�Ľ�ð��"},
	{ TestHoareSort, "����"},
	{ TestSimpleSelectSort, "��ѡ��"},
	{ TestBetterSelectSort, "�Ľ�ѡ��"},
    { TestHeapSort, "������"},
	{ TestMergeSort, "2·�鲢"},  
	{ TestNRecurMergeSort, "�ǵ�2·�鲢"},  
	{ TestCountSort, "����"},  
	{ TestRadixSort, "����"},  
    { 0, 0}      
};

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
	int idx,i;
	while(1){   
		printf("\n\t\t===========================\n");
		printf("\t\t|       �����㷨�˵�      |\n");
		printf("\t\t---------------------------\n");
		for(i=0; SortMenu[i].fun!=0; i++)
			printf("\t\t| %2d:  %-15s    |\n", i, SortMenu[i].menu);
		printf("\t\t===========================\n");
		printf("\t������˵���Ų���ENTER��([-1]����):");
		scanf("%d",&idx);  
		if(idx<i)
		{	
			if(-1==idx)return;
			(*SortMenu[idx].fun)();
		}
		else printf("\t��������������[%d];����������!\n", idx);
	}
}
void TestStraightInsertSort ( void ){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	InsertSort ( L );
	PrintSortListA ( L );
}
void TestBinInsertSort ( void ){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	BinInsertSort ( L );
	PrintSortListA ( L );
}

void TestTwoInsertSort ( void ){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	TwoInsertSort ( L );
	PrintSortListA ( L );
}

void TestSLInsertSort ( void){
	SLinkList SL[MAXSIZE];
	CreateSLList ( SL );
	PrintStaticLnkList ( *SL );
	SLInsertSort ( SL );
	PrintStaticLnkList ( *SL );
}
void TestAdjustSLLink(void){
	SLinkList SL[MAXSIZE];
	CreateSLList ( SL );
	PrintStaticLnkList ( *SL );
	AdjustSLLink ( SL );
	PrintStaticLnkList ( *SL );
}
void TestShellInsertSort ( void ){
	SortList L[MAXSIZE];
	int d[]={3,2,1};
	int t=3;
	CreateSortList ( L );
	PrintSortListB ( L );
	ShellInsertSort ( L, d, t );
	PrintSortListA ( L );
}
void TestBubbleSort ( void ){
	SortList L[MAXSIZE];
	CreateSortList( L );
	PrintSortListB ( L );
	BubbleSort ( L );
	PrintSortListA ( L );
}
void TestBetterBubbleSort ( void ){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	BetterBubbleSort ( L );
	PrintSortListA ( L );
}
void TestHoareSort ( void ){
	SortList L[MAXSIZE];
	int low=1;
	int high;
	CreateSortList ( L );
	high=L->length;
	PrintSortListB ( L );
	HoareSort ( L, low, high );
	PrintSortListA ( L );
}
void TestSimpleSelectSort (void ){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	SimpleSelectSort ( L );
	PrintSortListA ( L );
}

void TestBetterSelectSort (void){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	BetterSelectSort ( L );
	PrintSortListA ( L );
}
void TestTreeSort ( void ){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	TreeSort ( L );
	PrintSortListA ( L );
}
void TestHeapSort(void){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	HeapSort ( L );
	PrintSortListA ( L );
}

void TestMergeSort ( void ){
	SortList SR[MAXSIZE];
	SortList TR[MAXSIZE];
	int s;
	int t;
	CreateSortList ( SR );
	s=1;
	t=SR->length;
	MergeSort ( SR, TR, s, t );
	PrintSortListA (TR);
}
void  TestNRecurMergeSort(void){
	SortList Q[MAXSIZE];
	CreateSortList ( Q );
	PrintSortListB ( Q );
	NRecurMergeSort ( Q );
	PrintSortListA ( Q );
}

void TestCountSort ( void ){
	SortList L[MAXSIZE];
	CreateSortList ( L );
	PrintSortListB ( L );
	CountSort ( L );
	PrintSortListA ( L );
}
void TestRadixSort (void){
	SLink *L=NULL;
	int n=10;
	L=CreateSLink ( n );
	PrintLnkList ( L );
	L=RadixSort ( L );
	PrintLnkList ( L );
	DestroyLnkList(L);
}