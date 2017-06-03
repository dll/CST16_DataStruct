//PFWDSA plugin head file DSA10.h
#ifndef DSA10_H
#define DSA10_H

#include<stdio.h> 
#include<stdlib.h> 
#include<windows.h> 
#include<time.h> 


void DSAInterface(void);
extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

#define MAXVERTEX 10
typedef char ElemType;
//图的邻接矩阵类型定义
typedef struct{
	int vexnum, arcnum, kind;
	ElemType vex[MAXVERTEX];
	int arc[MAXVERTEX][MAXVERTEX];
}AdjMatrixGraph;

//图的邻接表类型定义
typedef struct node{
	int num;
	struct node*next;
}EdgeLinkNode;
typedef struct{
	struct {
		ElemType vertex;
		EdgeLinkNode *first;
	}VertexNode[MAXVERTEX];
	int vex, edge, tag;
}AdjLinkListGraph;


void CreateAdjMatrixGraph(AdjMatrixGraph *G);
void CreateAdjMatrixGraphFromFile(AdjMatrixGraph *G, const char *gname);
void PrintAdjMatrixGraph(AdjMatrixGraph*G);
void FindAdjVex(AdjMatrixGraph * G);
void CreateAdjLinkListGraph(AdjLinkListGraph *G, int n, int m);
void CreateAdjLinkListGraphFromFile(AdjLinkListGraph *G, const char * gname, int n, int m);
void PrintAdjLinkListGraph(AdjLinkListGraph *G);
void VisitedAdjLinkListGraphDFS(AdjLinkListGraph *G, int v, int visited[]);
void DFSVisitGraph(AdjLinkListGraph * G);
void VisitedAdjLinkListGraphBFS(AdjLinkListGraph *G, int v, int visited[]);
void BFSVisitGraph(AdjLinkListGraph * G);

#define MAXEDGES 30
typedef struct edges{
	int bVertex, eVertex, weight;
}Edges;

typedef Edges EdgeSet[MAXEDGES];

int Seek(int set[], int v);
void KruskalMST(EdgeSet ge, int n, int e);
int cmp( const void *a ,const void *b);

#define MAXVERTEXES 20
#define MAXCOST 10000
void PrimMST(int c[MAXVERTEXES][MAXVERTEXES], int n);

typedef struct{
	struct {
		ElemType vertex;
		EdgeLinkNode *first;
		int count;
	}VertexNode[MAXVERTEX];
	int vex, edge, tag;
}AdjLinkListGraphTopSort;

void CreateAdjLinkListGraphTopSort(AdjLinkListGraphTopSort *G, int n, int m);
void TopSort(AdjLinkListGraphTopSort *G);
void PrintAdjLinkListGraphTopSort(AdjLinkListGraphTopSort *G);

#define INFINITY 10000 //无穷大

void CreateAdjMatrixGraphDijkstra(AdjMatrixGraph *G);
void PrintAdjMatrixGraphDijkstra(AdjMatrixGraph*G);
void Dijkstra(AdjMatrixGraph *G, int n, int v0, int d[]);

void CreateAdjMatrixGraphFloyd(AdjMatrixGraph *G);
void PrintAdjMatrixGraphFloyd(AdjMatrixGraph*G);
void Floyd(int cost[][MAXVERTEX], int n, int weight[][MAXVERTEX], int path[][MAXVERTEX]);


#endif
