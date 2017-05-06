#ifndef THREADBTREE_H
#define THREADBTREE_H

#include <stdio.h>  
#include <stdlib.h>  

typedef char ElemType; //数据类型  
typedef enum {Link,Thread} childTag; //Link表示结点，Thread表示线索  
typedef struct bitNode  
{  
	ElemType data;  
	struct bitNode *lchild,*rchild;  
	int ltag,rtag;  
} bitNode ,*bitTree;  

void create_tree(bitTree *T,char **arr); //创建二叉树  
void pre_order_traverse(bitTree T,int level); //前序遍历二叉树  
void in_order_threading(bitTree T); //中序遍历线索化  
void in_thread(bitTree *P,bitTree T); //新加入一个头结点，让二叉树成一个封闭环  
void in_order_traverse(bitTree T); //中序遍历二叉树(带有头结点)  
void visit(bitTree T); //访问结点信息  
void testThreadBTree();

//bitTree pre; //表示上次刚刚访问的结点  

#endif
