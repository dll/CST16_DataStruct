/*
*文件：DSA02.H
*顺序列表的头文件
*作者：刘东良
*日期: 2012-09-10
*/
#ifndef DSA02_H
#define DSA02_H

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>


extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);


ULONG dTime, dTime1, dTime2;
LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;

typedef  int ElemType;
#define  INITSIZE 100
//const int INITSIZE=100;

typedef  struct
{ 
	ElemType  *data;
	int	length;
	int	listsize;
}SeqList;

typedef ElemType SeqListA[INITSIZE]; //extra

void  InitSeqList( SeqListA SL,  int n);//extra
void  InitSeqList2( SeqList * SL);
void  InitSeqList3( SeqList ** SL);//extra
void  ClearSeqList( SeqList * SL);

int  SeqListInsert(SeqList *SL, int i, ElemType x, int speed);
int  SeqListDelete(SeqList *SL, int i, ElemType* x, int speed);
int  SeqListEdit(SeqList *SL, int i, ElemType x);
void ReadSeqList(SeqList *SL, char * fname);
void SeqListSave(SeqList *SL, char * fname);
void SeqListPrint(SeqListA SL, int n);
void SeqListPrint2(SeqList *SL);//extra

ElemType RandElem(ElemType min, ElemType max);//extra
void RandArray(ElemType min, ElemType max, SeqListA SL, int n);//extra


int GetSeqListLength(SeqList *SL);
int GetSeqListElem(SeqList *SL, int i, ElemType *x);
int LocateSeqListElem(SeqList *SL,  ElemType x);
void UnionSeqList(SeqList *La, SeqList *Lb);

int  ElemTypeCmp(ElemType a, ElemType b);
int  LocateSeqListElem2(SeqList *SL,  ElemType x, int(* Cmp)(ElemType a, ElemType b));
void UnionSeqList2(SeqList *La, SeqList *Lb);
void MoveOddEven(SeqList *SL);

#endif
