#ifndef THREADBTREE_H
#define THREADBTREE_H

#include <stdio.h>  
#include <stdlib.h>  

typedef char ElemType; //��������  
typedef enum {Link,Thread} childTag; //Link��ʾ��㣬Thread��ʾ����  
typedef struct bitNode  
{  
	ElemType data;  
	struct bitNode *lchild,*rchild;  
	int ltag,rtag;  
} bitNode ,*bitTree;  

void create_tree(bitTree *T,char **arr); //����������  
void pre_order_traverse(bitTree T,int level); //ǰ�����������  
void in_order_threading(bitTree T); //�������������  
void in_thread(bitTree *P,bitTree T); //�¼���һ��ͷ��㣬�ö�������һ����ջ�  
void in_order_traverse(bitTree T); //�������������(����ͷ���)  
void visit(bitTree T); //���ʽ����Ϣ  
void testThreadBTree();

//bitTree pre; //��ʾ�ϴθոշ��ʵĽ��  

#endif
