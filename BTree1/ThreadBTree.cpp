#include"ThreadBTree.h"

bitTree pre;

void testThreadBTree() 
{  
	bitTree P,T;  
	int level =1; //��ʾ�ý������  
	char *arr="ab d  ce   "; //���������������(��ǰ�������ʽ����)  
	create_tree(&T,&arr); //���������  
	printf("pre-order-traverse\n");  
	pre_order_traverse(T,level); //ǰ��������������  
	printf("in-order-traverse\n");  
	in_thread(&P,T); //������������  
	in_order_traverse(P); //�����������Ķ�����  
}  

/* 
��������������������밴��ǰ������Ĵ��� 
T�����������ڵ� 
arr������ǰ������������еĸ��ڵ��ֵ���޺��ӽ��ʱ�ÿո���� 
*/  
void create_tree(bitTree *T,char **arr)  
{  
	char c;  
	sscanf(*arr,"%c",&c); //����һ�����ֵ  
	(*arr)++;  
	if(' '==c) //����ǿո񣬱�ʾ�ս��  
	{  
		*T=NULL;  
	}  
	else   
	{  
		*T=(bitTree)malloc(sizeof(bitNode)); //�����½��  
		(*T)->data=c;  
		(*T)->ltag=Link;  
		(*T)->rtag=Link;  
		create_tree(&(*T)->lchild,arr);//�����½�������  
		create_tree(&(*T)->rchild,arr);//�����½����Һ���  
	}  
}  

/* 
ǰ��������ʶ����� 
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
���������������������������� 
*/  
void in_order_threading(bitTree T)  
{  
	if(T)  
	{  
		in_order_threading(T->lchild); //����������  
		if(!T->lchild) //�������Ϊ�գ�����ָ��ֱ��ǰ��  
		{  
			T->lchild=pre;  
			T->ltag=Thread;  
		}  
		if(!pre->rchild) //�����һ�������Һ���Ϊ�գ�����ָ��ֱ�Ӻ�̡���ע�⣺ֻ�з��ʵ���һ�����ʱ���Ż�֪�������ĺ����˭��  
		{  
			pre->rchild=T;  
			pre->rtag=Thread;  
		}  
		pre=T;  
		in_order_threading(T->rchild); //�Һ���������  
	}  
}  

/* 
����һ��ͷ��㣬ʹ������������һ����ջ� 
P������ͷ���Ķ�������ͷ��������ָ�������T���Һ���ָ��T���е����һ��Ҷ�ӽ�� 
T��������ͷ���Ķ������� 
*/  
void in_thread(bitTree *P,bitTree T)  
{  
	(*P)=(bitTree)malloc(sizeof(bitNode)); //�����¼����ͷ���  
	(*P)->ltag=Link;  
	(*P)->rtag=Thread;  
	(*P)->rchild=*P;  
	if(!T) //���������Ϊ�գ���P�ĺ���ָ���Լ���  
	{  
		(*P)->lchild=*P;  
	}  
	else  
	{  
		(*P)->lchild=T;  
		pre=*P;  
		in_order_threading(T); //�Զ���������������  
		(*P)->rchild=pre; //��ͷ����Һ���ָ�����һ��Ҷ�ӽ��  
		pre->rtag=Thread; //�����һ��Ҷ�ӽ����Һ���ָ��ͷ��㡣�����������γ��ˡ�  
		pre->rchild=*P;  
	}  
}  

/* 
�ǵݹ鷽ʽ���������������(���������ͷ��㣬���Ѿ�������) 
P:����ͷ���Ķ����� 
*/  
void in_order_traverse(bitTree P)  
{  
	bitTree T;  
	T=P->lchild;  
	while(T!=P) //�ж��Ƿ����  
	{  
		while(T->ltag==Link) //�����ӿ�ʼ��ֱ��Ҷ�ӽ��  
		{  
			T=T->lchild;  
		}  
		visit(T);  
		while(T->rtag==Thread && T->rchild!=P) //�������������ʺ�̽�㡣���Һ�̽�㲻��ָ��ͷ����  
		{  
			T=T->rchild;  
			visit(T);  
		}  
		T=T->rchild;  
	}  
}  

/* 
���ʽ����Ϣ 
*/  
void visit(bitTree T)  
{  
	printf("%d-%c-%d\n",T->ltag,T->data,T->rtag);  
}  
