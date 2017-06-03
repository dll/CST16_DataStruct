#include"DSA07.h"


void InitSeqStack(SeqStack * SS){
	SS->base = (ElemType *)malloc(INITSIZE* sizeof(ElemType));
	SS->top=0;
	SS->stacksize=INITSIZE;	
}

int GetSeqTop(SeqStack * SS, ElemType * e){
	if(SS->top==0) return 0;
	*e = SS->base[--SS->top];
	return 1;
}
int SeqPush(SeqStack * SS, ElemType x){
	if(SS->top>=SS->stacksize){
		SS->base = (ElemType *)realloc(SS->base, (SS->stacksize+1)* sizeof(ElemType));
		if(!SS->base)return 0;
		SS->stacksize++;
	}
	SS->base[SS->top++]=x;
	return 1;
}

int SeqPop(SeqStack * SS, ElemType * e){
	if(SS->top==0) return 0;
	*e = SS->base[SS->top-1];
	return 1;
}
int EmptySeqStack(SeqStack * SS){
	if(SS->top==0) return 1;//空
	else return 0;//非空
}

void PrintSeqStack(SeqStack * SS){
	int i;
	for(i=SS->top-1; i>=0; i--)
		printf("%4d ", SS->base[i]);
	printf("\n");
}
int Match(ElemType *exps){

	int i=0, nomatch=0;
	SeqStack SS;
	ElemType x;

	InitSeqStack(&SS);

	while(!nomatch && exps[i]!='\0'){
		switch(exps[i]){
			case '(':
			case '[':
			case '{':
				SeqPush(&SS, exps[i]);
				break;
			case ')':
				GetSeqTop(&SS, &x);
				if(x=='(')SeqPop(&SS, &x);
				else nomatch=1;
				break;
			case ']':
				GetSeqTop(&SS, &x);
				if(x=='[')SeqPop(&SS, &x);
				else nomatch=1;
				break;
			case '}':
				GetSeqTop(&SS, &x);
				if(x=='{')SeqPop(&SS, &x);
				else nomatch=1;
				break;
		}
		i++;
	}
	if(EmptySeqStack(&SS) && !nomatch) return 1;//匹配
	else return 0;//不匹配
}

LinkStack * InitLinkStack(void){
	LinkStack *  LS;
	LS = (LinkStack *)malloc(sizeof(LinkStack));
	LS->next = NULL;
	return LS;
}

int GetLinkTop(LinkStack * LS, ElemType * e){
	if(LS->next==NULL) return 0;
	*e = LS->next->data;
	return 1;
}
int LinkPush(LinkStack * LS, ElemType x){
	LinkStack * p;
	p = (LinkStack *)malloc(sizeof(LinkStack));
	if(!p)return 0;
	p->data=x;
	p->next = LS->next;
	LS->next = p;
	return 1;
}

int LinkPop(LinkStack * LS, ElemType * e){
	LinkStack * p;
	if(LS->next==NULL) return 0;
	p = LS->next;
	*e = p->data;
	LS->next = p->next;
	free(p);
	return 1;
}
int EmptyLinkStack(LinkStack * LS){
	if(LS->next==NULL) return 1;
	else return 0;
}

void PrintLinkStack(LinkStack * LS){
	LinkStack * p=LS->next;
	while(p){
		printf("%4c ", p->data);
		p = p->next;
	}
	printf("\n");
}
int Palindrome(ElemType *str){

	LinkStack *LS;
	ElemType x;
	int len, i;
	int same=1;

	LS = InitLinkStack();
	
	for(len=0; str[len]!='\n'; len++);
	
	for(i=0; i<len/2; i++)
		LinkPush(LS, str[i]);
	
	for(i=(len+1)/2; i<len; i++)
	{
		LinkPop(LS, &x);
		if(x != str[i])
		{ same = 0; break;}
	}

	if(EmptyLinkStack(LS) && same) return 1;
	else return 0;
}



void InitSeqCycleQueue(SeqCycleQueue * SQ){
	SQ->base = (iElemType *)malloc(MAXCQSIZE* sizeof(iElemType));
	SQ->front=0;
	SQ->rear=0;	
}

int GetSeqQueueFront(SeqCycleQueue * SQ, iElemType * e){
	if(SQ->front==SQ->rear) return 0;
	*e = SQ->base[SQ->front];
	return 1;
}
int EnSeqCycleQueue(SeqCycleQueue * SQ, iElemType x){
	if((SQ->rear+1)%MAXCQSIZE == SQ->front)return 0;
	SQ->base[SQ->rear]=x;
	SQ->rear=(SQ->rear+1)%MAXCQSIZE;
	return 1;
}

int OutSeqCycleQueue(SeqCycleQueue * SQ, iElemType * e){
	if(SQ->front==SQ->rear) return 0;
	*e = SQ->base[SQ->front];
	SQ->front=(SQ->front+1)%MAXCQSIZE;
	return 1;
}
int EmptySeqCycleQueue(SeqCycleQueue * SQ){
	if(SQ->front==SQ->rear) return 1;
	else return 0;
}

void PrintSeqCycleQueue(SeqCycleQueue * SQ){
	int i;
	i=SQ->front;
	while(i!=SQ->rear){
		printf("%4d ", SQ->base[i]);
		i = (i+1)%MAXCQSIZE;
	}
	printf("\n");
}
void PlusMinusQueue(void){
	
	SeqCycleQueue SQ;
	iElemType x;

	InitSeqCycleQueue(&SQ);
	printf("随机输入一个整数序列(输入0结束):\n");
	scanf("%d", &x);
	while(x!=0){
		if(x>0){
			if(!EnSeqCycleQueue(&SQ, x)){
				printf("循环队列已满!\n");break;
			}
		}
		else if(!OutSeqCycleQueue(&SQ, &x)){
			printf("循环队列已空!\n");break;
		}
		scanf("%d", &x);
	}
	PrintSeqCycleQueue(&SQ);
}
void myPlusMinusQueue(void){
	
	SeqCycleQueue SQ, PMSQ, MSQ;//MSQ存放负数,PMSQ存放所有数据
	iElemType x, mx;

	InitSeqCycleQueue(&SQ);
	InitSeqCycleQueue(&PMSQ);//初始化PMSQ
	InitSeqCycleQueue(&MSQ);//初始化MSQ
	printf("随机输入一个整数序列(输入0结束):\n");
	scanf("%d", &x);
	while(x!=0){
		mx=x;
		EnSeqCycleQueue(&PMSQ, x);
		if(x>0){
			if(!EnSeqCycleQueue(&SQ, x)){
				printf("循环队列已满!\n");break;
			}
		}
		else if(!EnSeqCycleQueue(&MSQ, mx) && !OutSeqCycleQueue(&SQ, &x)){
			printf("循环队列已空!\n");break;
		}
		scanf("%d", &x);
	}
	PrintSeqCycleQueue(&PMSQ);
	PrintSeqCycleQueue(&SQ);
	PrintSeqCycleQueue(&MSQ);
}
void PlusMinusQueueFromFile(void){
	
	SeqCycleQueue SQ;
	iElemType x;
	FILE *pf;
	pf=fopen("Plugins/DSA074.dat", "r");

	while(!feof(pf)){
		InitSeqCycleQueue(&SQ);
		printf("从文件中读取一个整数序列(输入0结束):\n");
		fscanf(pf, "%d", &x);
		while(x!=0){
			if(x>0){
				if(!EnSeqCycleQueue(&SQ, x)){
					printf("循环队列已满!\n");break;
				}
			}
			else if(!OutSeqCycleQueue(&SQ, &x)){
				printf("循环队列已空!\n");break;
			}
			fscanf(pf, "%d", &x);
		}
		PrintSeqCycleQueue(&SQ);

	}
	fclose(pf);
}
