#ifndef POLYHEADER
#define POLYHEADER

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#include<windows.h>//DllMain

extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

typedef struct { // ��ı�ʾ
    float  coef; // ϵ��coefficient 
    int    expn; // ָ��exponential
} term, ElemType;  

typedef struct tagOrderedLinkList{// ��������ı�ʾ
    term  data; // �����򣨽ṹ��Ƕ�ף� 
    struct tagOrderedLinkList * next; // ָ����
} OrderedLinkList; //��ָ����С�������������

typedef  OrderedLinkList   polynomial; // �ô���ͷ�������������ʾ����ʽ

#define POLY 21//���԰�������
int nPoly;
//��������
//////////////////////////////////////////////////

//��Ҫ����
int CreatePolynFromFile ( polynomial **p, char * filename);
int AddPoly (polynomial **Pc, polynomial *Pa, polynomial *Pb);
void PrintPolyn(polynomial *p);
int IsExistElem (polynomial *p, ElemType e);
int InsAfter( polynomial * p, ElemType e);
void SelectSortPoly(polynomial *p);
void DestroyPoly(polynomial *p);
int cmp(ElemType e1, ElemType e2);
void SavePolyn(FILE *pf, polynomial *p);
int IsEqualPoly(polynomial *a, polynomial *b);

#endif