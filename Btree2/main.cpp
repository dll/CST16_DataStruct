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
		CreateBiTree(&((*T)->lchild)) ;                           
		CreateBiTree(&((*T)->rchild))  ;                           
	}
}

int Count_Tree(BiTree t)//计算二叉树的结点个数。
{
	
	int lcount,rcount;
	if(t==NULL) return 0;
	lcount=Count_Tree(t->lchild);
	rcount=Count_Tree(t->rchild);
	return lcount+rcount+1;
}

int Height(BiTree t) //计算二叉树的高度
{
	int h1,h2;
	if(t==NULL) return 0;
	else
	{
		h1=Height(t->lchild); //求左子树的高度
		h2=Height(t->rchild);
		if(h1>h2) return h1+1; //求右子树的高度
		return h2+1;
	}
}

void Countleaf(BiTree t,int * count) //计算二叉树的叶子结点的个数
{
	if(t==NULL) *count=0;
	if(t->lchild==0 && t->rchild==0) (*count)++;
	if(t->lchild!=0) Countleaf(t->lchild,count);
	if(t->rchild!=0) Countleaf(t->rchild,count);
}

void Swapbitree(BiTree t) //交换二叉树的左右子树
{
	BiTree p;
	if(t==NULL) return;
	Swapbitree(t->lchild); Swapbitree(t->rchild);
	p=t->lchild; t->lchild=t->rchild; t->rchild=p;
}

void Copybitree(BiTree t1,BiTree *t2) //复制一棵二叉树
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
	printf("本程序可以建立二叉树、求二叉树的结点个数、高度、叶子结点个数，交换二叉树的左右子树，复制一棵二叉树。\n");
	printf("请将二叉树的先序序列输入以建立二叉树。\n");
	printf("您必须一个一个地输入字符。\n");
	while(sign)
	{ 
		printf("请选择: \n");
		printf("1.生成二叉树（#表示空结点）   \n");
		printf("2.递归求结点个数               3.递归求高度\n ");
		printf("4.递归求叶子结点个数           5.递归交换二叉树左右子树\n");
		printf("6.递归复制一棵二叉树           7.输出二叉树\n");
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
			{	printf("递归求二叉树的结点个数：\n");
			printf("二叉树的结点个数为：%d\n",Count_Tree(T));
			
			}
			else 
			   printf("二叉树为空!\n");
			break;
		case 3:
			if(T)
			{
				printf("递归求二叉树的高度：\n");
				printf("二叉树的高度为：%d\n",Height(T));
			}
			else printf("二叉树为空!\n");
			break;
		case 4:
			if(T)
			{
				printf("递归求二叉树的叶子结点个数：\n");
				Countleaf(T,&count);
				printf("二叉树的叶子结点个数为：%d\n",count);
			}
			else printf("二叉树为空!\n");
			break;
		case 5:
			if(T)
			{
				printf("递归交换二叉树左右子树：\n");
				Swapbitree(T);
				Preorder(T);
				printf("\n");
			}	
			else printf("二叉树为空!\n");
			break;
		case 6:
			if(T)
			{
				printf("递归复制二叉树左右子树：\n");
				Copybitree(T,&T1) ;
				Preorder(T1);
				printf("\n");
			}
			else printf("二叉树为空!\n");
			break;
		case 7:
			if(T)
			{
				printf("二叉树的遍历序列为：");
				Preorder(T);
				printf("\n");
			}
			else printf("二叉树为空!\n");
			break;
		default:
			sign=0;
			printf("程序运行结束，按任意键退出!\n");
		}
	}
	return 0;
}
