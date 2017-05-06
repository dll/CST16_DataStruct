# include<stdio.h>
# include<stdlib.h>
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode  *next;
}LNode,*LinkList;
void CreatList(LinkList &L,int n)
{
	int i;
	LinkList p;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	for(i=n;i>0;--i){
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		
		p->next=L->next;
		L->next=p;
	}
	
}

void printf1(LinkList L){
LinkList p;
	p=L->next;
	while(p){
		printf("%d ",p->data);
		p=p->next;
	}
}

void MergeList(LinkList &La,LinkList &Lb,LinkList  &Lc){
LinkList pa,pb,pc;
	pa=La->next;
    pb=Lb->next;
	Lc=pc=La;
	while(pa&&pb){
		if(pa->data<=pb->data){
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}
		else
		{
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
	}
	pc->next=pa?pa:pb;

	free(Lb);
	Lb=NULL;
	printf1(Lc);
}
void main(){
	int s,m;
	LinkList Lc,La,Lb;
	printf("Enter the number of La:\n");
	scanf("%d",&s);
	CreatList(La,s);
	printf1(La);
    printf("Enter the number of Lb:\n");
	scanf("%d",&m);
	CreatList(Lb,m);
	printf1(Lb);
	MergeList(La,Lb,Lc);
	//printf1(Lc);

}

