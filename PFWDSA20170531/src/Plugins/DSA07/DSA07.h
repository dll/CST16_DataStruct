#ifndef STACKANDQUEUEHEADER
#define STACKANDQUEUEHEADER

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
#define  INITSIZE 100

typedef char ElemType;

typedef struct{
	ElemType * base;
	int top;
	int stacksize;

}SeqStack;


#define  MAXCQSIZE 100

typedef int iElemType;

typedef struct{
	iElemType * base;
	int front;
	int rear;
}SeqCycleQueue;

//typedef char ElemType;

typedef struct node{
	ElemType data;
	struct node * next;
}LinkStack;

/*
函数声明
*/

void InitSeqStack(SeqStack * SS);
int GetSeqTop(SeqStack * SS, ElemType * e);
int SeqPush(SeqStack * SS, ElemType x);
int SeqPop(SeqStack * SS, ElemType * e);
int EmptySeqStack(SeqStack * SS);
void PrintSeqStack(SeqStack * SS);
int Match(ElemType *exps);

LinkStack * InitLinkStack(void);
int GetLinkTop(LinkStack * LS, ElemType * e);
int LinkPush(LinkStack * LS, ElemType x);
int GetLinkTop(LinkStack * LS, ElemType * e);
int LinkPush(LinkStack * LS, ElemType x);
int LinkPop(LinkStack * LS, ElemType * e);
int EmptyLinkStack(LinkStack * LS);
void PrintLinkStack(LinkStack * LS);
int Palindrome(ElemType *str);

void InitSeqCycleQueue(SeqCycleQueue * SQ);
int GetSeqQueueFront(SeqCycleQueue * SQ, iElemType * e);
int EnSeqCycleQueue(SeqCycleQueue * SQ, iElemType x);
int OutSeqCycleQueue(SeqCycleQueue * SQ, iElemType * e);
int EmptySeqCycleQueue(SeqCycleQueue * SQ);
void PrintSeqCycleQueue(SeqCycleQueue * SQ);
void PlusMinusQueue(void);
void myPlusMinusQueue(void);
void PlusMinusQueueFromFile(void);

#endif