#include<stdio.h>
#include<malloc.h>
#include <math.h >
#include"ThreadBTree.h"

#define  MaxSize 20
#define OK 1

//typedef int ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

//建立二叉树（按先序序列生成二叉树,#表示空节点）
void CreateBiTree(BiTree *T)
{
	char ch;
	scanf("%c",&ch);
	getchar();/*回车键（每次输入一个字符后，需敲回车键）*/
	if(ch=='#')
	{
		printf("不产生子树。\n");
		*T=NULL;
	}
	else
	{
		if(!(*T=(BiTNode *)malloc(sizeof(BiTNode))))
		{
			printf("分配空间失败");
			return;
		}//生成一个新节点
		(*T)->data = ch;
		printf("产生左右子树。\n");
		CreateBiTree(&((*T)->lchild));                           
		CreateBiTree(&((*T)->rchild));                          
	}
}

//递归前序遍历
void Preorder(BiTNode *T)
{
	if(T)
	{
		printf("%c ",T->data);
		Preorder(T->lchild);                                
		Preorder(T->rchild);                              
	}
}

//递归中序遍历
void Inorder(BiTNode *T)
{
	if(T)
	{
		Inorder(T->lchild);
		printf("%c ",T->data);                   
		Inorder(T->rchild); 
	} 
}

//递归后序遍历
void Postorder(BiTNode *T)
{
	if(T)
	{
		Postorder(T->lchild);                 
		Postorder(T->rchild); 
		printf("%c ",T->data);  
	} 
}

//层次遍历二叉树
void Translever(BiTNode *T)
{
	struct node
	{
		BiTNode *vec[MaxSize];
		int f,r;                //r为队尾，f为队头
	}queue;
	BiTNode *p;
	p=T;
	queue.f=0;
	queue.r=0;
	if(T)
		printf("%c ", p->data);
	queue.vec[queue.r]=p;
	queue.r=queue.r+1;
	while(queue.f<queue.r)
	{
		p=queue.vec[queue.f];
		queue.f=queue.f+1;
		if(p->lchild)
		{
			printf("%c ",p->lchild->data);
			queue.vec[queue.r]=p->lchild;
			queue.r=queue.r+1;
		}
		if(p->rchild)
		{
			printf("%c ",p->rchild->data);
			queue.vec[queue.r]=p->rchild;
			queue.r=queue.r+1;
		}
	}
	printf("\n");
}
//按广义表形式输出二叉树
void Disptree(BiTNode *T)
{
	if(T)
	{
		printf("%c",T->data);
		if(T->lchild || T->rchild)
		{
			printf("(");
			Disptree(T->lchild);
			if(T->rchild)
				printf(",");
			Disptree(T->rchild);
			printf(")");
		}
	}
}

void testBTree(){
	BiTree T=NULL;
	int j;
	int sign = 1;
	int num;
	
	printf("本程序可以进行建立二叉树、递归先序、中序、后序遍历二叉树、层次遍历二叉树、输出二叉树的扩展序列的操作。\n");
	printf("请将二叉树的先序序列输入以建立二叉树。\n");
	printf("您必须一个一个地输入字符。\n");
	while(sign)
	{ 
		printf("请选择: \n");
		printf("1.生成二叉树（#表示空结点）   \n");
		printf("2.递归先序遍历         3.递归中序遍历\n");
		printf("4.递归后序遍历         5.层次遍历\n");
		printf("6.输出二叉树的广义表形式   \n"); 
		printf("0.退出程序\n");
		scanf("%d",&j);
		getchar();
		switch(j)
		{
		case 1:
			printf("生成二叉树:");
			CreateBiTree(&T); 
			printf("\n");
			printf("\n");
			break;
			
		case 2:
			if(T)
			{
				printf("递归先序遍历二叉树:");
				Preorder(T);
				printf("\n");
				printf("\n");
			}
			else 
			   printf("二叉树为空!\n");
			break;
		case 3:
			if(T)
			{
				printf("递归中序遍历二叉树:");
				Inorder(T);
				printf("\n");
				printf("\n");
			}
			else printf("二叉树为空!\n");
			break;
		case 4:
			if(T)
			{
				printf("递归后序遍历二叉树:");
				Postorder(T);
				printf("\n");
				printf("\n");
			}
			else printf("二叉树为空!\n");
			break;
		case 5:
			if(T)
			{
				printf("层次遍历二叉树:");
				Translever(T);
				printf("\n");
				printf("\n");
			}
			else printf("二叉树为空!\n");
			break;
		case 6:
			if(T)
			{
				printf("输出二叉树:");
				Disptree(T);
				printf("\n");
				printf("\n");
			}
			else printf("二叉树为空!\n");
			break;
		default:
			sign=0;
			printf("程序运行结束，按任意键退出!\n");
		}
	}
}

int main()
{
	testThreadBTree();
//	testBTree();
	return 0;
}
