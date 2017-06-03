#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<malloc.h>
#include<string.h>

using namespace std;

#define INFINITY  10000// 用整型最大值代替∞
#define MAX_VERTEX_NUM 20 // 最大顶点个数
#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define MAXQSIZE100 
typedef int QElemType;
typedef float VRType;
typedef int InfoType;
typedef char  VertexType;

//============邻接矩阵的定义============ 
typedef struct {
	VRType   adj; 
	InfoType info;   // 该弧相关信息的指针(可无) 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 顶点向量
	AdjMatrix arcs; // 邻接矩阵
	int vexnum,arcnum; // 图的当前顶点数和弧数 
} MGraph ;
//=======================邻接矩阵的定义========

//=================================邻接表的定义=========
typedef struct ArcNode{      // 表结点
	int  adjvex;              // 该弧所指向的顶点的位置
	struct ArcNode *nextarc;   // 指向下一条弧的指针
	float info;                // 网的权值指针
} ArcNode;    
typedef struct{                   // 头结点
	VertexType data[MAX_VERTEX_NUM];     // 顶点信息
	ArcNode *firstarc;        // 第一个表结点的地址 
} VNode, AdjList[MAX_VERTEX_NUM];   
typedef struct {
	AdjList  vertices;
	int vexnum,arcnum;   // 图的当前顶点数和弧数
}ALGraph;
int  visited[MAX_VERTEX_NUM];
//=================邻接表的定义=========================


//=========队列定义和基本操作===============
typedef struct QNODE{
	QElemType  data;
	struct QNODE *next;
}QNode, *QueuePtr;
typedef struct { //链队列的定义
	QElemType *base; 
	int  front;  
	int  rear; 
} SqQueue;
typedef struct{  
	QueuePtr  front;
	QueuePtr  rear;
}LinkQueue;

LinkQueue InitQueue(LinkQueue Q){
	
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		exit(1);	
	Q.front->next=NULL;
	return Q;
}

int EnQueue(LinkQueue* Q, QElemType e){
	QueuePtr p;
	if( !(p=(QueuePtr)malloc(sizeof(QNode))) )     
		return ERROR;
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

int DeQueue(LinkQueue *Q, QElemType *e) { 
	QueuePtr  p;  
	if( Q->front == Q->rear )
		return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p)  Q->rear = Q->front;
	free(p);
	return OK;
}

int QueueEmpty(LinkQueue *Q) {
	if(Q->front ==Q->rear)  return 1;
	else  return 0;
}

int DestroyQueue( LinkQueue *Q ){
	while(Q->front) {
		Q->rear=Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	}
	return OK;
}

//===================队列定义和基本操作===============

int LocateVex(MGraph G,char *vert)
{  
	int  i;

	for(i=0; i<G.vexnum; i++)
		if(strcmp(G.vexs[i],vert)==0)
		return i;
	return -1;
}

int LocateVex1(ALGraph G,char *vert)
{     int  i;
for(i=0; i<G.vexnum; i++)
	if(strcmp(G.vertices[i].data,vert)==0)
	return i;
return -1;
}

//建立无向网G的邻接矩阵
MGraph  CreateGraph_UDN( MGraph G, char * filename){
	int  i, j,k;
	float  w;
	VertexType v1[100], v2[100];
//	printf("输入顶点数,数边数：");
	FILE *pf = fopen(filename,"r");
	fscanf(pf, "%d %d", &G.vexnum, &G.arcnum);
	for(i=0; i<G.vexnum; i++)	  // 读入所有的顶点 
	{   
//		printf("输入第%d个顶点的信息：",i+1);
		fscanf(pf, "%s", &G.vexs[i]);	
	}
	for(i=0; i <G.vexnum; i++)	  //初始化邻接矩阵 
		for(j=0; j<G.vexnum; j++)  
		G.arcs[i][j].adj=INFINITY;
		for(k=0; k<G.arcnum; k++) { 	  // 输入所有的边 
//			printf("输入第%d条边依附的两个顶点和边上的权值:",k+1);
			fscanf(pf, "%s %s %f", &v1, &v2, &w);	
			// 查询两个顶点在图中存储的位置 
			i = LocateVex(G, v1);	
			j = LocateVex(G, v2);
			if (i==-1 || j==-1)
			{printf("输入的边不正确\n"); exit(0);}
			G.arcs[i][j].adj = w;
			G.arcs[j][i].adj = G.arcs[i][j].adj;	
		}
	fclose(pf);
	
	return G;
}
//建立无向网G的邻接表
ALGraph CreateALGraph_UDN(ALGraph G ,char * filename)
{        
	int i,j,k;
	float w;
	ArcNode * p;
	VertexType v1[100], v2[100];
//	printf("输入顶点数,数边数：");
	FILE *pf = fopen(filename,"r");
	fscanf(pf,"%d %d",&(G.vexnum),&(G.arcnum));  /* 读入顶点数和边数 */
	for(i=0;i<G.vexnum;i++)  /* 建立有n个顶点的顶点表 */
	{   
//		printf("输入第%d个顶点的信息：",i+1);
		fscanf(pf,"%s",&(G.vertices[i].data)) ;    /* 读入顶点信息 */
		G.vertices[i].firstarc=NULL;  /* 顶点的边表头指针设为空 */
	}
	for(k=0;k<G.arcnum;k++ ) /* 建立边表 */
	{   
//		printf("输入一条边依附的两个顶点和边上的权值:");
		fscanf(pf,"%s %s %f",&v1,&v2,&w) ;  /* 读入边<Vi，Vj>的顶点对应序号 */
		i = LocateVex1(G, v1);	
		j = LocateVex1(G, v2);
		if (i==-1 || j==-1)
		{printf("输入的边不正确\n"); exit(0);}
		p=(ArcNode*)malloc(sizeof(ArcNode) );  /* 生成新边表结点p */
		p->adjvex=j;                                /* 邻接点序号为j */
		p->info =w;
		p->nextarc=G.vertices[i].firstarc;  /* 将新边表结点p插入到顶点Vi的链表头部 */
		G.vertices[i].firstarc=p;
		p=(ArcNode*)malloc(sizeof(ArcNode) );  /* 生成新边表结点p */
		p->adjvex=i;                                /* 邻接点序号为i */
		p->info =w;
		p->nextarc=G.vertices[j].firstarc;  /* 将新边表结点p插入到顶点Vj的链表头部 */
		G.vertices[j].firstarc=p;
	} 
	fclose(pf);
	return G; 
}  /*CreateALGraph*/ 

void VisitFunc(char *ch)//输出顶点的信息
{
	printf("%s ",ch);
}

void DFS(ALGraph G, int v ) {
	int  j;
	ArcNode *p;
	VisitFunc(G.vertices[v].data);    // 访问第v个顶点
	visited[v]=TRUE;           // 设置访问标志为TRUE(已访问)
	for(p=G.vertices[v].firstarc; p;p=p->nextarc)
	{
		j=p->adjvex;
		if( !visited[j] ) DFS(G, j); 
	}
}

void DFSTraverse( ALGraph G){//图的深度优先遍历算法
	int v;
	printf("\n图的深度优先遍历:\n");
	for(v=0; v<G.vexnum; v++)
		visited[v]=FALSE;      // 访问标志数组初始化(未被访问)
	for(v=0;v<G.vexnum;v++)
		if(!visited[v])
		DFS(G,v);               // 对尚未访问的顶点调用DFS
}

void BFSTraverse(ALGraph G) //图的广度优先遍历算法
{ 
	int v,j,u ;
	ArcNode *p;
	LinkQueue Q; 
	printf("\n图的广度优先遍历:\n");
	Q=InitQueue(Q);  // 置空的辅助队列Q
	for(v=0; v<G.vexnum; v++)
		visited[v]=FALSE; // 置初值
	for(v=0; v<G.vexnum; v++)
		if(!visited[v]){
		visited[v]=TRUE;  // 设置访问标志为TRUE(已访问)
		VisitFunc(G.vertices[v].data);
		EnQueue( &Q, v );        // v入队列
		while(!QueueEmpty(&Q)){
			DeQueue(&Q,&u);     // 队头元素出队并置为u 
			for(p=G.vertices[u].firstarc; p;p=p->nextarc)
			{
				j=p->adjvex;
				if( !visited[j] ) 
				{visited[j]=TRUE;
				VisitFunc(G.vertices[j].data);
				EnQueue(&Q, j);
				}
			}           
		}
	}
		DestroyQueue( &Q );
		
}
//实现建立有向网的邻接矩阵和邻接表的函数
MGraph  CreateGraph_DN( MGraph G,char*filename ){//建立有向网G的邻接矩阵
	int  i, j,k;
	float  w;
	VertexType v1[100], v2[100];
//	printf("输入顶点数,数边数：");
	FILE *pf = fopen(filename,"r");
	fscanf(pf,"%d %d", &G.vexnum, &G.arcnum);
	for(i=0; i<G.vexnum; i++)	  // 读入所有的顶点 
	{   
//		printf("输入第%d个顶点的信息：",i+1);
		fscanf(pf,"%s", &G.vexs[i]);	
	}
	for(i=0; i <G.vexnum; i++)	  //初始化邻接矩阵 
		for(j=0; j<G.vexnum; j++)  
		G.arcs[i][j].adj=INFINITY;
		for(k=0; k<G.arcnum; k++) { 	  // 输入所有的边 
			//printf("输入第%d条边依附的两个顶点和边上的权值:",k+1);
			fscanf(pf,"%s %s %f", &v1, &v2, &w);	
			// 查询两个顶点在图中存储的位置 
			i = LocateVex(G, v1);	
			j = LocateVex(G, v2);
			if (i==-1 || j==-1)
			{printf("输入的边不正确\n"); exit(0);}
			G.arcs[i][j].adj = w;
			//G.arcs[j][i].adj = G.arcs[i][j].adj;	
		}
	fclose(pf);
	return G;
}

//建立有向网G的邻接表
ALGraph CreateALGraph_DN(ALGraph G,char*filename ){  
	int i,j,k;
	float w;
	ArcNode * p;
	VertexType v1[100], v2[100];
//	printf("输入顶点数,数边数：");
	FILE *pf = fopen(filename,"r");
	fscanf(pf,"%d %d",&(G.vexnum),&(G.arcnum));  /* 读入顶点数和边数 */
	for(i=0;i<G.vexnum;i++)  /* 建立有n个顶点的顶点表 */
	{   
//		printf("输入第%d个顶点的信息：",i+1);
		fscanf(pf,"%s",&(G.vertices[i].data)) ;    /* 读入顶点信息 */
		G.vertices[i].firstarc=NULL;  /* 顶点的边表头指针设为空 */
	}
	for(k=0;k<G.arcnum;k++ ) /* 建立边表 */
	{   
//		printf("输入一条边依附的两个顶点和边上的权值:");
		fscanf(pf,"%s %s %f",&v1,&v2,&w) ;  /* 读入边<Vi，Vj>的顶点对应序号 */
		i = LocateVex1(G, v1);	
		j = LocateVex1(G, v2);
		if (i==-1 || j==-1)
		{printf("输入的边不正确\n"); exit(0);}
		p=(ArcNode*)malloc(sizeof(ArcNode) );  /* 生成新边表结点p */
		p->adjvex=j;                                /* 邻接点序号为j */
		p->info =w;
		p->nextarc=G.vertices[i].firstarc;  /* 将新边表结点p插入到顶点Vi的链表头部 */
		G.vertices[i].firstarc=p;
		
//		p=(ArcNode*)malloc(sizeof(ArcNode) );  /* 生成新边表结点p */
//		p->adjvex=i;                                /* 邻接点序号为i */
//		p->info =w;
//		p->nextarc=G.vertices[j].firstarc;  /* 将新边表结点p插入到顶点Vj的链表头部 */
//		G.vertices[j].firstarc=p;
	} 
	fclose(pf);
	return G;
}

void Print_MGraph(MGraph G)//输出图的邻接矩阵表示
{
	int i,j;
	printf("图的邻接矩阵表示:\n");
	for(i=0;i<G.vexnum;i++)	{ 
		for(j=0;j<G.vexnum;j++){
			if(G.arcs[i][j].adj==INFINITY)
				printf("%8s","∞");
			else
				printf("%8.2f ",G.arcs[i][j].adj );  /*邻接矩阵*/
		}
		printf("\n\n");
	}     
}

void Print_ALGraph(ALGraph G) //输出图的邻接表表示
{
	int i,j;
	ArcNode *p;
	printf("图的邻接表表示:\n");
	for(i=0;i<G.vexnum;i++)  
	{   
		printf("%s",G.vertices[i].data );    /* 顶点信息 */
		p=G.vertices[i].firstarc ;
		while(p!=NULL)                       /* 表节点信息 */
		{
			printf("->%s",G.vertices[p->adjvex ].data);
			p=p->nextarc ;
		}                	   /* 顶点的边表头指针设为空 */
		printf("\n");  
	}
}

void FindInDegree(ALGraph G, int *indegree)
{
	int i,k;ArcNode *p;    	 
	for (i=0; i<G.vexnum; ++i)
	{
		for (p=G.vertices[i].firstarc;  p;  p=p->nextarc) {
			{k = p->adjvex;indegree[k]++;  }              
		}
	}
}

//===================拓扑排序==============================
int TopologicalSort(ALGraph G) {  
	// 有向图G采用邻接表存储结构。
	// 若G无回路，则输出G的顶点的一个拓扑序列并返回OK，否则ERROR。
	int SqStack[MAX_VERTEX_NUM],top=0;
	int count,k,i;
	ArcNode *p;
	int  indegree[MAX_VERTEX_NUM];
	printf("\n图的拓扑排序:\n");
	for (i=0;i<MAX_VERTEX_NUM;i++) indegree[i]=0;
	FindInDegree(G, indegree);   // 对各顶点求入度indegree[0..vernum-1]
	for (i=0; i<G.vexnum; ++i)       // 建零入度顶点栈S
		if (!indegree[i]) {SqStack[top]=i;top++;}  // 入度为0者进栈
		count = 0;                       // 对输出顶点计数
		while (top) {
			top--;
			i=SqStack[top];
			printf("%s-> ", G.vertices[i].data);  ++count;  // 输出i号顶点并计数
			for (p=G.vertices[i].firstarc;  p;  p=p->nextarc) {
				k = p->adjvex;               // 对i号顶点的每个邻接点的入度减1
				if (!(--indegree[k])) {SqStack[top]=k;top++;}  // 若入度减为0，则入栈
			}
		}
		if (count<G.vexnum) { printf("存在回路！");return ERROR;} // 该有向图有回路
		else return OK;
} // TopologicalSort
//======================拓扑排序=====================
int main()
{
	printf("\n图1-----------------:\n");
	MGraph G1,G3;
	ALGraph G2,G4;
	G1=CreateGraph_UDN( G1,"G1.txt");
	Print_MGraph(G1);
	system("pause");
	
	G2=CreateALGraph_UDN (G2,"G2.txt");
	Print_ALGraph(G2);
	DFSTraverse(G2);
	BFSTraverse(G2) ;
	system("pause");
	//建立有向网G3的邻接矩阵
	G3=CreateGraph_DN(G3,"G3.txt");
	//输出有向网G3邻接矩阵
	Print_MGraph(G3);
	system("pause");
	//建立有向网G4的邻接表
	G4=CreateALGraph_DN(G4,"G4.txt");
	//输出有向网G4邻接表
	Print_ALGraph(G4);
	//深度优先和广度优先遍历有向网G4
	DFSTraverse( G4);
	BFSTraverse( G4) ;
	TopologicalSort(G4);//求邻接表表示的有向图的拓扑排序
	system("pause");
	
	return 0;
}
