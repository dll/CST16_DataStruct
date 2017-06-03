/*
*文件：DSA06.h
*插件文件，串的头文件
*作者：刘东良
*日期: 2012-09-10
*/

#ifndef STRING_HEADER
#define STRING_HEADER

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
#define INITSTRLEN 100
typedef struct {
	char *ch;
	int length;
	int strsize;
}SeqString;

typedef struct node{
	char ch;
	struct node * next;
}LinkString;

/*
函数声明
*/
void InitSeqString(SeqString * SS );
void SeqStringAssign(SeqString * SS, char *s);
void PrintSeqString(SeqString * SS);
int StringBFIndex(SeqString *SS, SeqString *ST, int pos, int *o);

void  GetNext(SeqString *SS, int next[]);
void  GetNextValue(SeqString *SS, int nextval[]);
int StringKMPIndex(SeqString *s, SeqString *t, int pos, int *o);
int StringKMPIndex2(SeqString *s, SeqString *t, int pos, int *o);
void MaxComSubStr(SeqString *s, SeqString *t);

LinkString * InitLinkString(void);
void LinkStringAssign(LinkString * LS, char *s);
void PrintLinkString(LinkString * LS);
int LinkStrBFSeek(LinkString * LS, LinkString * LT, int Pos, int *o);

void FirstUpr(LinkString * LS);
void DestroyLinkString(LinkString * LS);

#endif