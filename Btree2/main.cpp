#include<stdio.h>
#include<malloc.h>
#include <math.h >
#define  MaxSize 20
typedef int ElemType;
#define OK 1
int count;
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
		CreateBiTree(&((*T)->lchild)) ;                           
		CreateBiTree(&((*T)->rchild))  ;                           
	}
}

int Count_Tree(BiTree t)//����������Ľ�������
{
	
	int lcount,rcount;
	if(t==NULL) return 0;
	lcount=Count_Tree(t->lchild);
	rcount=Count_Tree(t->rchild);
	return lcount+rcount+1;
}

int Height(BiTree t) //����������ĸ߶�
{
	int h1,h2;
	if(t==NULL) return 0;
	else
	{
		h1=Height(t->lchild); //���������ĸ߶�
		h2=Height(t->rchild);
		if(h1>h2) return h1+1; //���������ĸ߶�
		return h2+1;
	}
}

void Countleaf(BiTree t,int * count) //�����������Ҷ�ӽ��ĸ���
{
	if(t==NULL) *count=0;
	if(t->lchild==0 && t->rchild==0) (*count)++;
	if(t->lchild!=0) Countleaf(t->lchild,count);
	if(t->rchild!=0) Countleaf(t->rchild,count);
}

void Swapbitree(BiTree t) //��������������������
{
	BiTree p;
	if(t==NULL) return;
	Swapbitree(t->lchild); Swapbitree(t->rchild);
	p=t->lchild; t->lchild=t->rchild; t->rchild=p;
}

void Copybitree(BiTree t1,BiTree *t2) //����һ�ö�����
{
	if (t1==NULL) {*t2=NULL; return;} 
	*t2=(BiTNode *)malloc(sizeof(BiTNode)); 
	(*t2)->data=t1->data;
	Copybitree(t1->lchild, &(*t2)->lchild); 
	Copybitree(t1->rchild, &(*t2)->rchild);
}

void Preorder(BiTree T)
{
	if(T)
	{
		printf("%c ",T->data);
		Preorder(T->lchild);                                
		Preorder(T->rchild);                              
	}
}

int main()
{
	BiTree T=NULL,T1=NULL;
	int j;
	int sign = 1;
	int num;
	count=0;
	printf("��������Խ�������������������Ľ��������߶ȡ�Ҷ�ӽ���������������������������������һ�ö�������\n");
	printf("�뽫���������������������Խ�����������\n");
	printf("������һ��һ���������ַ���\n");
	while(sign)
	{ 
		printf("��ѡ��: \n");
		printf("1.���ɶ�������#��ʾ�ս�㣩   \n");
		printf("2.�ݹ��������               3.�ݹ���߶�\n ");
		printf("4.�ݹ���Ҷ�ӽ�����           5.�ݹ齻����������������\n");
		printf("6.�ݹ鸴��һ�ö�����           7.���������\n");
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
			{	printf("�ݹ���������Ľ�������\n");
			printf("�������Ľ�����Ϊ��%d\n",Count_Tree(T));
			
			}
			else 
			   printf("������Ϊ��!\n");
			break;
		case 3:
			if(T)
			{
				printf("�ݹ���������ĸ߶ȣ�\n");
				printf("�������ĸ߶�Ϊ��%d\n",Height(T));
			}
			else printf("������Ϊ��!\n");
			break;
		case 4:
			if(T)
			{
				printf("�ݹ����������Ҷ�ӽ�������\n");
				Countleaf(T,&count);
				printf("��������Ҷ�ӽ�����Ϊ��%d\n",count);
			}
			else printf("������Ϊ��!\n");
			break;
		case 5:
			if(T)
			{
				printf("�ݹ齻������������������\n");
				Swapbitree(T);
				Preorder(T);
				printf("\n");
			}	
			else printf("������Ϊ��!\n");
			break;
		case 6:
			if(T)
			{
				printf("�ݹ鸴�ƶ���������������\n");
				Copybitree(T,&T1) ;
				Preorder(T1);
				printf("\n");
			}
			else printf("������Ϊ��!\n");
			break;
		case 7:
			if(T)
			{
				printf("�������ı�������Ϊ��");
				Preorder(T);
				printf("\n");
			}
			else printf("������Ϊ��!\n");
			break;
		default:
			sign=0;
			printf("�������н�������������˳�!\n");
		}
	}
	return 0;
}
