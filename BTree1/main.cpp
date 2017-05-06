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

//�������������������������ɶ�����,#��ʾ�սڵ㣩
void CreateBiTree(BiTree *T)
{
	char ch;
	scanf("%c",&ch);
	getchar();/*�س�����ÿ������һ���ַ������ûس�����*/
	if(ch=='#')
	{
		printf("������������\n");
		*T=NULL;
	}
	else
	{
		if(!(*T=(BiTNode *)malloc(sizeof(BiTNode))))
		{
			printf("����ռ�ʧ��");
			return;
		}//����һ���½ڵ�
		(*T)->data = ch;
		printf("��������������\n");
		CreateBiTree(&((*T)->lchild));                           
		CreateBiTree(&((*T)->rchild));                          
	}
}

//�ݹ�ǰ�����
void Preorder(BiTNode *T)
{
	if(T)
	{
		printf("%c ",T->data);
		Preorder(T->lchild);                                
		Preorder(T->rchild);                              
	}
}

//�ݹ��������
void Inorder(BiTNode *T)
{
	if(T)
	{
		Inorder(T->lchild);
		printf("%c ",T->data);                   
		Inorder(T->rchild); 
	} 
}

//�ݹ�������
void Postorder(BiTNode *T)
{
	if(T)
	{
		Postorder(T->lchild);                 
		Postorder(T->rchild); 
		printf("%c ",T->data);  
	} 
}

//��α���������
void Translever(BiTNode *T)
{
	struct node
	{
		BiTNode *vec[MaxSize];
		int f,r;                //rΪ��β��fΪ��ͷ
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
//���������ʽ���������
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
	
	printf("��������Խ��н������������ݹ��������򡢺����������������α������������������������չ���еĲ�����\n");
	printf("�뽫���������������������Խ�����������\n");
	printf("������һ��һ���������ַ���\n");
	while(sign)
	{ 
		printf("��ѡ��: \n");
		printf("1.���ɶ�������#��ʾ�ս�㣩   \n");
		printf("2.�ݹ��������         3.�ݹ��������\n");
		printf("4.�ݹ�������         5.��α���\n");
		printf("6.����������Ĺ������ʽ   \n"); 
		printf("0.�˳�����\n");
		scanf("%d",&j);
		getchar();
		switch(j)
		{
		case 1:
			printf("���ɶ�����:");
			CreateBiTree(&T); 
			printf("\n");
			printf("\n");
			break;
			
		case 2:
			if(T)
			{
				printf("�ݹ��������������:");
				Preorder(T);
				printf("\n");
				printf("\n");
			}
			else 
			   printf("������Ϊ��!\n");
			break;
		case 3:
			if(T)
			{
				printf("�ݹ��������������:");
				Inorder(T);
				printf("\n");
				printf("\n");
			}
			else printf("������Ϊ��!\n");
			break;
		case 4:
			if(T)
			{
				printf("�ݹ�������������:");
				Postorder(T);
				printf("\n");
				printf("\n");
			}
			else printf("������Ϊ��!\n");
			break;
		case 5:
			if(T)
			{
				printf("��α���������:");
				Translever(T);
				printf("\n");
				printf("\n");
			}
			else printf("������Ϊ��!\n");
			break;
		case 6:
			if(T)
			{
				printf("���������:");
				Disptree(T);
				printf("\n");
				printf("\n");
			}
			else printf("������Ϊ��!\n");
			break;
		default:
			sign=0;
			printf("�������н�������������˳�!\n");
		}
	}
}

int main()
{
	testThreadBTree();
//	testBTree();
	return 0;
}
