#ifndef ARRAYANDGLIST_H
#define ARRAYANDGLIST_H

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

/*
类型声明
*/
#define MAXARRAYSIZE 100
#define M 3
#define N 4

typedef int iElemType;
typedef struct{
	int i, j;
	iElemType e;
}TupleType;

typedef struct{
	int rownum;
	int colnum;
	int nznum;
	TupleType data[MAXARRAYSIZE];
}TupleSeqList;

typedef char ElemType;
//头尾表示法headtail

typedef struct node{
	int tag;
	union{
		ElemType data;
		struct {
			struct node * hp;
			struct node * tp;
		}ptr;
	}val;
}GLHTNode;

#define Max ((M)>(N)?(M):(N))

typedef struct mtxn{
	int row;
	int col;
	struct mtxn * right, *down;
	union{
		int value;//data
		struct mtxn *link;//next
	}tag;
}MatrixNode, AcrossLinker;

/*
函数声明
*/

void CreateTSL(TupleSeqList * m, iElemType A[M][N]);
void PrintTupleSeqList(TupleSeqList * m);
void Translate(TupleSeqList *T, TupleSeqList *m);

void SubString(char* sub, char* S, int i, int j);
void SplitStrServe(char *str, char * hstr);
GLHTNode * CreateGL(char *S);
int GetGLDepth(GLHTNode *h);
void PrintGL(GLHTNode *h);
GLHTNode * CopyGL(GLHTNode *h);
GLHTNode * GetGLHead(GLHTNode *h);
GLHTNode * GetGLTail(GLHTNode *h);

AcrossLinker* CreateAcrossLinker(AcrossLinker *h[], int A[M][N]);
void PrintAcrossLinker(AcrossLinker *h);
AcrossLinker* PreNode(AcrossLinker *h[], int i, int j);
void MatrixAdd(AcrossLinker *ha, AcrossLinker *hb, AcrossLinker *h[]);


#endif