//PFWDSA plugin head file DSA11.h
#ifndef DSA11_H
#define DSA11_H

#include<stdio.h> 
#include<stdlib.h> 
#include<windows.h> 
#include<time.h> 
#include <malloc.h >

void DSAInterface(void);
extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

#define MAXSIZE 20 

typedef int ElemType;

//顺序表
typedef struct
{
	ElemType r[MAXSIZE+1];
	int length;
}SortList;

//静态链表
typedef struct
{
	ElemType key;
	int next;
}SLNode;

typedef struct
{
	SLNode r[MAXSIZE+1];
	int length;
}SLinkList;

//单链表
typedef struct node
{
	ElemType key;
	struct node *next;
}SLink;

void CreateSLList ( SLinkList *SL );
void PrintSLList ( SLinkList SL );
void AdjustSLLink ( SLinkList *SL );

void SLInsertSort ( SLinkList *SL );

void CreateSortList ( SortList *L );
void PrintSortListA ( SortList *L );
void PrintSortListB ( SortList *L );
void AdjustSortTree ( SortList *L, int n, int k );

void BinInsertSort ( SortList *L );
void BubbleSort ( SortList *L );
void CountSort ( SortList *L );
void AdjustTree ( SortList *L, int n, int k );
void HeapSort ( SortList *L );
void HoareSort ( SortList * L, int low, int high );
void InsertSort ( SortList *L );
void Merge ( SortList *SR, SortList *TR, int i, int m, int n );
void MergeSort ( SortList *SR, SortList *TR, int s, int t );

SLink *CreateSLink ( int n );
void PrintLnkList ( SLink *L );
SLink *RadixSort ( SLink *L );

void SelectSortList ( SortList *L );
void ShellInsertSort ( SortList *L,  int d[],  int t );

SortList CreateInitTree ( SortList *L );
ElemType MaxTree ( SortList *L );
void TreeSort ( SortList *L );

void TwoInsertSort ( SortList *L );

#endif
