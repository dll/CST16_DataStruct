/*
*文件：DSA08.C
*插件文件，特殊线性表：数组和广义表，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA08.h"

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

void TestSymmetricMatrix(void);
void TestTupleSeqList(void);
void TestGList(void);
void TestAcrossLinker(void);


void DSAInterface(void){
	int i=0;
	while(i!=5){
		system("CLS");
		printf("\n数组和广义表演示\
			\n请输入数字选择:\n1 TestSymmetricMatrix\n2 TestTupleSeqList\
			\n3 TestGList\n4 TestAcrossLinker\n5 退出\n");
		flushall();
		scanf("%d", &i);
		switch(i){
			case 1:
				TestSymmetricMatrix();break;
			case 2:
				TestTupleSeqList();break;
			case 3:
				TestGList();break;
			case 4:
				TestAcrossLinker();break;
			case 5:return;
		}
		system("PAUSE");
	}
}

void TestSymmetricMatrix(void){
	FILE * pf;
	int i, j, k, m[N][N], a[N*(N+1)/2];
	
	if((pf=fopen("Data/DSA081.dat", "r"))==NULL){
		printf("打开文件 DSA081.dat 失败!"); exit(0);
	}
	k=0;
	while(!feof(pf)){
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				fscanf(pf, "%d ", &m[i][j]);
				if(i>=j)a[k++]= m[i][j];
			}
			fscanf(pf,"\n");
		}
	}
	fclose(pf);

	PrintSymmetricMatrix(a);
}


void TestTupleSeqList(void){
	FILE * pf;
	int i, j, m[N][N];
	TupleSeqList TSL, TSL_T;

	if((pf=fopen("Data/DSA082.dat", "r"))==NULL){
		printf("打开文件 DSA082.dat 失败!"); exit(0);
	}
	while(!feof(pf)){
		for(i=0; i<N; i++){
			for(j=0; j<N; j++)
				fscanf(pf, "%d\t", &m[i][j]);
			fscanf(pf,"\n");
		}
	}
	fclose(pf);
	
	CreateTSL(&TSL, m);
	PrintSparseMatrix(&TSL);
	PrintTupleSeqList(&TSL);

	Translate(&TSL_T, &TSL);
	
	PrintSparseMatrix(&TSL_T);
	PrintTupleSeqList(&TSL_T);

}


void TestGList(void){

	int i;
	char ch[30];
	FILE * pf;
	GLHTNode  *GL;

	if((pf=fopen("Data/DSA083.dat", "r"))==NULL){
		printf("打开文件 DSA083.dat 失败!"); exit(0);
	}
	for(i=0; !feof(pf); i++){
		fscanf(pf, "%c", &ch[i]);
		fscanf(pf,"\n");
	}
	ch[i]='\0';
	fclose(pf);
	
	GL=CreateGL(ch);
	printf("\n广义表为:");
	PrintGL(GL);
	printf("\n深度为:\t%d", GetGLDepth(GL));
	printf("\n表头为:\t");
	PrintGL(GetGLHead(GL));
	printf("\n表尾为:\t");
	PrintGL(GetGLTail(GL));
	printf("\n");

}

void TestAcrossLinker(void){
	FILE * pf;
	int i, j, m[M][N],n[M][N];
	AcrossLinker  *ma,*mb;
	AcrossLinker  *h[Max];

	if((pf=fopen("Data/DSA084.dat", "r"))==NULL){
		printf("打开文件 DSA084.dat 失败!"); exit(0);
	}
	while(!feof(pf)){
		for(i=0; i<M; i++){
			for(j=0; j<N; j++)
				fscanf(pf, "%d\t", &m[i][j]);
			fscanf(pf,"\n");
		}
		fscanf(pf,"\n");

		for(i=0; i<M; i++){
			for(j=0; j<N; j++)
				fscanf(pf, "%d\t", &n[i][j]);
			fscanf(pf,"\n");
		}
	}
	fclose(pf);
	
	ma=CreateAcrossLinker(h, m);
	PrintAcrossLinker(ma);

	mb=CreateAcrossLinker(h, n);
	PrintAcrossLinker(mb);

	MatrixAdd(ma, mb, h);
	
	PrintAcrossLinker(ma);

	//DestroyAcrossLinker(ma);
	//DestroyAcrossLinker(mb);
}