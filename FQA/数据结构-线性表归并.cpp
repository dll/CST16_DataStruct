//Fan student Question!

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
	LinkList p,q;
	L=(LinkList)malloc(sizeof(LNode));
	L->data=0;
	L->next=NULL;
	q=L;
	for(i=n;i>0;--i){
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		if(q->data>p->data){
			printf("LinkList is Non-Decreasing!!");
			exit(0);
		}
		p->next=NULL;
		q->next=p;
		q=p;
	}
	
}

void printf1(LinkList L){
	LinkList p;
	p=L->next;
	while(p){
		printf("%d -->",p->data);
		p=p->next;
	}
	printf("\n");
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
}
int main(){
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
	printf("After Merge List:\n");
	MergeList(La,Lb,Lc);
	printf1(Lc);
	
	return 0;
}

/*
Enter the number of La:
3
2 3 33
2 -->3 -->33 -->
Enter the number of Lb:
2
1 22
1 -->22 -->
After Merge List:
1 -->2 -->3 -->22 -->33 -->

*/
