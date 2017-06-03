/*
*文件：DSA10.C
*插件文件，图，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA10.h"

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

int TestGraph(void);
int TestPrimMST(void);
int TestKruskalMST(void);
int TestDijkstra(void);
int TestFloyd(void);
int TestTopSort(void);

void DSAInterface(void){
	int i=0;
	while(i!=7){
		system("CLS");
		printf("\n\t图算法演示\
			\n请输入数字选择:\n1 TestGraph\n2 TestPrimMST\
			\n3 TestKruskalMST\n4 TestTopSort\n5 TestDijkstra\n6 TestFloyd \n7退出\n");
		flushall();
		scanf("%d", &i);
		switch(i){
			case 1:
				TestGraph();break;
			case 2:
				TestPrimMST();break;
			case 3:
				TestKruskalMST();break;
			case 4:
				TestTopSort();break;
			case 5:
				TestFloyd();break;
			case 6:
				TestDijkstra();break;
			case 7:
				return;
		}
		system("PAUSE");
	}
}

int TestGraph(void){

	AdjMatrixGraph MG,MG1;
	AdjLinkListGraph LG,LG1,LG2;
	printf("\n邻接矩阵表示的图\n");
	//CreateAdjMatrixGraph(&MG);
	//PrintAdjMatrixGraph(&MG);
	
	CreateAdjMatrixGraphFromFile(&MG1,"G4");
	PrintAdjMatrixGraph(&MG1);
	FindAdjVex(&MG1);
	system("PAUSE");

	printf("\n\n邻接链表表示的图\n");
	//CreateAdjLinkListGraph(&LG, 5, 0);
	//PrintAdjLinkListGraph(&LG);
	//DFSVisitGraph(&LG);
	//BFSVisitGraph(&LG);
	
	CreateAdjLinkListGraphFromFile(&LG1, "G6", 5, 1);
	PrintAdjLinkListGraph(&LG1);
	
	printf("\n\n");
	system("PAUSE");
	CreateAdjLinkListGraphFromFile(&LG2,"G8",8, 0);
	PrintAdjLinkListGraph(&LG2);
	DFSVisitGraph(&LG2);

	BFSVisitGraph(&LG2);

	return 0;
}

int TestPrimMST(void){
	int i, j, k;
	int cost[MAXVERTEXES][MAXVERTEXES];
	EdgeSet ges={{0,0,0},{1,2,6},{1,3,9},{1,4,5},{1,5,13},{2,3,14},{2,4,7},{2,5,8},{3,4,9},{3,5,3},{4,5,2}};
	qsort(ges,11,sizeof(ges[0]),cmp);
	for(i=1; i<=11; i++)
		for(j=1; j<=11; j++)
			cost[i][j]=MAXCOST;
	for(k=1; k<=11; k++){
		i=ges[k].bVertex;
		j=ges[k].eVertex;
		cost[i][j]=ges[k].weight; 
		cost[j][i]=ges[k].weight; 
	}
	PrimMST(cost, 5);
	return 0;
}

int TestKruskalMST(void){
	EdgeSet ges={{0,0,0},{1,2,6},{1,3,9},{1,4,5},{1,5,13},{2,3,14},{2,4,7},{2,5,8},{3,4,9},{3,5,3},{4,5,2}};
	qsort(ges,11,sizeof(ges[0]),cmp); 
	KruskalMST(ges, 5, 10); 
	return 0;
}


int TestTopSort(void){

	AdjLinkListGraphTopSort LG;
	printf("\n\n邻接链表表示的图--拓扑排序\n");
	CreateAdjLinkListGraphTopSort(&LG, 6, 1);//P162
	PrintAdjLinkListGraphTopSort(&LG);
	TopSort(&LG);
	system("PAUSE");
	return 0;
}
int TestDijkstra(void){

	AdjMatrixGraph MG;
	int d[6]={0};
	int i=0;
	printf("\n邻接矩阵表示的图\n");
	CreateAdjMatrixGraphDijkstra(&MG);
	PrintAdjMatrixGraphDijkstra(&MG);

	Dijkstra(&MG, 6, 0, d);
	for(i=1; i<6;i++)
		printf("%c-%c最短距离 %d \n", 'A', 'A'+i, d[i]);
	printf("\n");

	return 0;
}
int TestFloyd(void){

	AdjMatrixGraph MG;
	int w[][MAXVERTEX]={0};
	int p[][MAXVERTEX]={0};
	int i=0;
	int n=6;
	printf("\n邻接矩阵表示的图\n");
	CreateAdjMatrixGraph(&MG);
	PrintAdjMatrixGraph(&MG);

	Floyd((&MG)->arc, n, w, p);
	for(i=1; i<n;i++)
		printf("%c-%c最短距离 %d \n", 'A', 'A'+i, p[i]);
	printf("\n");

	return 0;
}