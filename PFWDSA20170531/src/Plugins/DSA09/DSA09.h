#ifndef TREEHEADER
#define TREEHEADER

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include<math.h>

extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

/*
类型声明
*/

#define VIRNODE '0'
#define MAXTREESIZE 20
typedef char ElemType;
typedef ElemType SeqBinTree[MAXTREESIZE];

//typedef char ElemType;
typedef struct Node
{
	ElemType data;
	struct Node * lChild, *rChild;
}LinkBinTree;


typedef struct node{
	LinkBinTree * data;
	struct node * next;
}LinkStack;

typedef struct {
	char ch;
	double weight;//权重应为实数类型
	unsigned int lchild, rchild, parent;
}HTNode, *HuffmanTree;

typedef char ** HuffmanCode;
char hcodes[26][26];

//孩子兄弟表示法
typedef struct CSNode{
	ElemType data;
	struct CSNode * firstChild, *nextSibling;
}CSNode, *CSTree;

#define MAXSIZE 100
CSTree	q[MAXSIZE];
int count;

//宏函数
#define ROUND(val) (int)(val+0.5) 
#define R 1
//全局变量
FILE *fp;
char FileName[20];

//二叉树类型定义
typedef struct BintreeNode{
	char Data;
	struct BintreeNode *lChild,*rChild;
	int Left,Top,Right,Bottom,OX,OY;
}BintreeNode;

typedef struct LeavesPtrNode{
	struct BintreeNode *LeavesPtr;
	struct LeavesPtrNode *Next;
}LeavesPtrNode;

typedef struct DrawingQueue{
	struct LeavesPtrNode *pHead,*pTail;
	int Length;
}DrawingQueue;

/*
函数声明
*/
int GetSBTreeHigh(SeqBinTree SBT);
void LevelTraverseTree(SeqBinTree SBT);
void LevelPrintTree(SeqBinTree SBT);
void LevelPrintTree1(SeqBinTree SBT);
void LevelPrintTree2(SeqBinTree SBT);
void LevelPrintTree3(SeqBinTree SBT);
void CreateSeqBinTree(SeqBinTree SBT, int n);
void CreateSeqBinTreeFromFile(SeqBinTree SBT);
int GetSBTreeHigh(SeqBinTree SBT);


LinkBinTree* CreateDLRLDR(char DLR[], char LDR[], int n);
LinkStack * InitLinkStack(void);
int LinkPush(LinkStack * LS, LinkBinTree * x);
LinkBinTree * LinkPop(LinkStack * LS);
int EmptyLinkStack(LinkStack * LS);
void DestroyLinkBinTree(LinkBinTree *t);
LinkBinTree* LBTRChild(LinkBinTree *t);
LinkBinTree* LBTLChild(LinkBinTree *t);
LinkBinTree * CreateLinkBinTree(void);
int GetLBTreeHigh(LinkBinTree *LBT);
void PreOrderNuReserveTraverse(LinkBinTree *LBT);

void OutTextXY(int x, int y, const char * s);
void DrawRect(int x, int y, int r);
void DrawLine(int xa,int ya,int xb,int yb);
int GetMaxX();
int GetMaxY();
int Max(int a,int b);
void PostOrder(BintreeNode *t,void (*visit)(BintreeNode *));
void PrintTree(BintreeNode *bt,int nLayer);
void DeleteNodeX(BintreeNode **bt, char x);
void SearchNode(BintreeNode *bt, char x, BintreeNode **p, BintreeNode**f);
BintreeNode * InsertRightNode(BintreeNode * LBT, char v);
BintreeNode * InsertLeftNode(BintreeNode *LBT, char v);
BintreeNode * LChild(BintreeNode *t);
BintreeNode * RChild(BintreeNode *t);

void PrintBinTree(BintreeNode * t, int n);
void InitQueue(DrawingQueue *qu);
void EnQueue(DrawingQueue *qu,BintreeNode *t);
void DrawTree(BintreeNode *t,int TreeWidth,int RootX,int RootY);
void DeQueue(DrawingQueue *qu,BintreeNode **t);


void HuffmanCoding(HuffmanTree HT, HuffmanCode HC, double *w, int n);
void HuffmanCoding2(HuffmanTree HT, HuffmanCode HC, double *w, int n);
void HuffmanCoding3(HuffmanTree HT, HuffmanCode HC, double *w, int n);
void EncodeHC(void);
int ReleaseHuffCode(HuffmanTree ht, char *str,char* code);
void  DecodeHC(HuffmanTree ht);
void HuffmanCoding4(HuffmanTree *HT, double *w, int n);


void InitCSTree(CSTree *T); 
void DestroyCSTree(CSTree *T);
void CreateCSTree(CSTree *T);
void PrintCSTree(CSTree *T);
void DestroyCSTree(CSTree *T);

char InputFromKeyboard(void);
char InputFromFile(void);
void Visit(BintreeNode *t);

#endif