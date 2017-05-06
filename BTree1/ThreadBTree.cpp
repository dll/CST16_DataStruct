#include"ThreadBTree.h"

bitTree pre;

void testThreadBTree() 
{  
	bitTree P,T;  
	int level =1; //表示该结点的深度  
	char *arr="ab d  ce   "; //构造二叉树所需结点(按前序遍历方式输入)  
	create_tree(&T,&arr); //构造二叉树  
	printf("pre-order-traverse\n");  
	pre_order_traverse(T,level); //前序遍历输出二叉树  
	printf("in-order-traverse\n");  
	in_thread(&P,T); //二叉树线索化  
	in_order_traverse(P); //输出线索化后的二叉树  
}  

/* 
创建二叉树，其输入必须按照前序遍历的次序。 
T：二叉树根节点 
arr：按照前序遍历次序排列的各节点的值。无孩子结点时用空格代替 
*/  
void create_tree(bitTree *T,char **arr)  
{  
	char c;  
	sscanf(*arr,"%c",&c); //读入一个结点值  
	(*arr)++;  
	if(' '==c) //如果是空格，表示空结点  
	{  
		*T=NULL;  
	}  
	else   
	{  
		*T=(bitTree)malloc(sizeof(bitNode)); //构造新结点  
		(*T)->data=c;  
		(*T)->ltag=Link;  
		(*T)->rtag=Link;  
		create_tree(&(*T)->lchild,arr);//构造新结点的左孩子  
		create_tree(&(*T)->rchild,arr);//构造新结点的右孩子  
	}  
}  

/* 
前序遍历访问二叉树 
*/  
void pre_order_traverse(bitTree T,int level)  
{  
	if(T)  
	{  
		visit(T);  
		pre_order_traverse(T->lchild,level+1);  
		pre_order_traverse(T->rchild,level+1);  
	}  
}  

/* 
中序遍历二叉树，对其进行线索化 
*/  
void in_order_threading(bitTree T)  
{  
	if(T)  
	{  
		in_order_threading(T->lchild); //左孩子线索化  
		if(!T->lchild) //如果左孩子为空，则将其指向直接前驱  
		{  
			T->lchild=pre;  
			T->ltag=Thread;  
		}  
		if(!pre->rchild) //如果上一个结点的右孩子为空，则将其指向直接后继。（注意：只有访问到下一个结点时，才会知道本结点的后继是谁）  
		{  
			pre->rchild=T;  
			pre->rtag=Thread;  
		}  
		pre=T;  
		in_order_threading(T->rchild); //右孩子线索化  
	}  
}  

/* 
加入一个头结点，使二叉线索树成一个封闭环 
P：带有头结点的二叉树。头结点的左孩子指向二叉树T；右孩子指向T树中的最后一个叶子结点 
T：不带有头结点的二叉树。 
*/  
void in_thread(bitTree *P,bitTree T)  
{  
	(*P)=(bitTree)malloc(sizeof(bitNode)); //构造新加入的头结点  
	(*P)->ltag=Link;  
	(*P)->rtag=Thread;  
	(*P)->rchild=*P;  
	if(!T) //如果二叉树为空，则P的孩子指向自己。  
	{  
		(*P)->lchild=*P;  
	}  
	else  
	{  
		(*P)->lchild=T;  
		pre=*P;  
		in_order_threading(T); //对二叉树进行线索化  
		(*P)->rchild=pre; //将头结点右孩子指向最后一个叶子结点  
		pre->rtag=Thread; //将最后一个叶子结点的右孩子指向头结点。这样，环就形成了。  
		pre->rchild=*P;  
	}  
}  

/* 
非递归方式：中序遍历二叉树(树必须带有头结点，且已经线索化) 
P:带有头结点的二叉树 
*/  
void in_order_traverse(bitTree P)  
{  
	bitTree T;  
	T=P->lchild;  
	while(T!=P) //判断是否空树  
	{  
		while(T->ltag==Link) //从左孩子开始，直到叶子结点  
		{  
			T=T->lchild;  
		}  
		visit(T);  
		while(T->rtag==Thread && T->rchild!=P) //根据线索，访问后继结点。并且后继结点不是指向头结点的  
		{  
			T=T->rchild;  
			visit(T);  
		}  
		T=T->rchild;  
	}  
}  

/* 
访问结点信息 
*/  
void visit(bitTree T)  
{  
	printf("%d-%c-%d\n",T->ltag,T->data,T->rtag);  
}  
