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

typedef struct { // 项的表示
    float  coef; // 系数coefficient 
    int    expn; // 指数exponential
} term, ElemType;  

typedef struct tagOrderedLinkList{// 有序链表的表示
    term  data; // 数据域（结构体嵌套） 
    struct tagOrderedLinkList * next; // 指针域
} OrderedLinkList; //按指数由小到大排序的链表

typedef  OrderedLinkList   polynomial; // 用带表头结点的有序链表表示多项式

#define POLY 21//测试案例数量
int nPoly;
//函数声明
//////////////////////////////////////////////////

//主要函数
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