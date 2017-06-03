#include"DSA09.h"


extern int count=0;
extern FILE *fp=NULL;

void LevelTraverseTree(SeqBinTree SBT){
	int i, j;
	i=1;
	printf("分层打印\n");
	while(i<=SBT[0]){
		for(j=i; j<2*i; j++){
			if(SBT[j]==VIRNODE)
				printf("%c ",'*');//虚结点
			else
				printf("%c ", SBT[j]);
		}
		printf("\n");
		i=2*i;
	}
}
void LevelPrintTree(SeqBinTree SBT){
	int i, j=1, t=0,t1=0,t2=0,t3=0;
	i=1;
	t=GetSBTreeHigh(SBT);
	t1=(int)pow(2,t)-1;
	t2=(int)pow(2,t+1)-1;
	t3=(int)pow(2,t-1);
	printf("分层树型打印\n");
	while(i<=SBT[0]){
		for(; t1>0; t1--)
			printf(" ");
		for(j=i; j<2*i; j++){
			if(SBT[j]==VIRNODE)
				printf("%c",'*');//虚结点
			else
				printf("%c", SBT[j]);	
			for(;t2>0;t2--)
				printf(" ");
			t2=(int)pow(2,t+1)-1;
		}
		printf("\n");
		t--;
		t1=(int)pow(2,t)-1;
		t2=(int)pow(2,t+1)-1;
		t3=(int)pow(2,t-1);
		i=2*i;
	}
	printf("\n");
}
void LevelPrintTree1(SeqBinTree SBT){
	int i, j=1, t=0,t1=0,t2=0,t3=0;
	i=1;
	t=GetSBTreeHigh(SBT);
	t1=(int)pow(2,t)-1;
	t2=(int)pow(2,t+1)-1;
	t3=(int)pow(2,t-1);
	printf("分层树型无枝打印\n");
	while(i<=SBT[0]){
		for(; t1>0; t1--)
			printf(" ");
		for(j=i; j<2*i; j++){
			if(SBT[j]==VIRNODE)
				printf("%c",'*');//虚结点
			else
				printf("%c", SBT[j]);	
			for(;t2>0;t2--)
				printf(" ");
			t2=(int)pow(2,t+1)-1;
		}
		for(;t3>=0;t3--)
		printf("\n");
		t--;
		t1=(int)pow(2,t)-1;
		t2=(int)pow(2,t+1)-1;
		t3=(int)pow(2,t-1);
		i=2*i;
	}
	printf("\n");
}
void LevelPrintTree2(SeqBinTree SBT){
	int i, j=1;//i,j变量结点和层数
	int t=0;//二叉树的高度
	int t1=0;//结点或s树枝/左边的空格
	int t2=0;//结点左右树枝中的空格
	int t3=0;//两层结点之间的高度
	int a=0;//每层行数:两结点层之间，树枝的行数
	int b=0;//每行结点：每行中的结点数
	i=1;
	t=GetSBTreeHigh(SBT);
	t1=(int)pow(2,t)-1;
	t2=(int)pow(2,t+1)-1;
	t3=(int)pow(2,t-1);
	printf("分层树型有枝打印\n");
	while(i<=SBT[0]){
		for(; t1>0; t1--)
			printf(" ");
		for(j=i; j<2*i; j++){
			if(SBT[j]==VIRNODE)
				printf("%c",'*');//虚结点
			else
				printf("%c", SBT[j]);	
			for(;t2>0;t2--)
				printf(" ");
			t2=(int)pow(2,t+1)-1;
		}
		printf("\n");
		a=0;
		b=1;
		
		t1=(int)pow(2,t)-1;
		t2=(int)pow(2,t+1)-1;
		for(;t3>0;t3--){//树枝行数	
			for(j=i; j<2*i; j++){//树枝个数（左右为一组，可以看成树枝结点）
				for(; t1>1; t1--)
					printf(" ");
				printf("/");
				for(t1=0;t1<2*b-1;t1++)
					printf(" ");
				printf("\\");
				t1=(int)pow(2,t)-1;//恢复t1,在每层树枝间
				t1 =t1-a;//t1向下减小a
				for(; t1>0; t1--)
					printf(" ");
				t1=(int)pow(2,t)-1;//恢复t1,在每层树枝间
				t1 =t1-a;//t1向下减小a
				t2=(int)pow(2,t+1)-1;//恢复t2,在每层结点间
			}
			a++;
			b++;
			t1=(int)pow(2,t)-1;	//恢复t1,在每层结点间
			t2=(int)pow(2,t+1)-1;//恢复t2,在每层结点间
			t1 =t1-a;//t1向下减小a
			printf("\n");
		}
		t--;//从根结点逐层向下打印，高度减小1
		t1=(int)pow(2,t)-1;
		t2=(int)pow(2,t+1)-1;
		t3=(int)pow(2,t-1);
		i=2*i;//计算每层结点数，是上一层的2倍（包括虚结点）
	}
	printf("\n");
}
void LevelPrintTree3(SeqBinTree SBT){
	int i, j=1;//i,j变量结点和层数
	int t=0;//二叉树的高度
	int t1=0;//结点或s树枝/左边的空格
	int t2=0;//结点左右树枝中的空格
	int t3=0;//两层结点之间的高度
	int a=0;//每层行数:两结点层之间，树枝的行数
	int b=0;//每行结点：每行中的结点数
	i=1;
	t=GetSBTreeHigh(SBT);
	t1=(int)pow(2,t)-1;
	t2=(int)pow(2,t+1)-1;
	t3=(int)pow(2,t-1);
	printf("分层树型有枝无虚结点打印\n");
	while(i<=SBT[0]){
		for(; t1>0; t1--)
			printf(" ");
		for(j=i; j<2*i; j++){
			if(SBT[j]==VIRNODE)
				printf("%c",' ');//虚结点
			else
				printf("%c", SBT[j]);	
			for(;t2>0;t2--)
				printf(" ");
			t2=(int)pow(2,t+1)-1;
		}
		printf("\n");
		a=0;
		b=1;
		
		t1=(int)pow(2,t)-1;
		t2=(int)pow(2,t+1)-1;
		for(;t3>0;t3--){//树枝行数	
			for(j=i; j<2*i; j++){//树枝个数（左右为一组，可以看成树枝结点）
				if(SBT[j]==VIRNODE)
				{
					for(; t1>1; t1--)
						printf(" ");
					printf(" ");
					for(t1=0;t1<2*b-1;t1++)
						printf(" ");
					printf(" ");
					t1=(int)pow(2,t)-1;//恢复t1,在每层树枝间
					t1 =t1-a;//t1向下减小a
					for(; t1>0; t1--)
						printf(" ");
					t1=(int)pow(2,t)-1;//恢复t1,在每层树枝间
					t1 =t1-a;//t1向下减小a
					t2=(int)pow(2,t+1)-1;//恢复t2,在每层结点间
				}
				else{
					for(; t1>1; t1--)
						printf(" ");
					printf("/");
					for(t1=0;t1<2*b-1;t1++)
						printf(" ");
					printf("\\");
					t1=(int)pow(2,t)-1;//恢复t1,在每层树枝间
					t1 =t1-a;//t1向下减小a
					for(; t1>0; t1--)
						printf(" ");
					t1=(int)pow(2,t)-1;//恢复t1,在每层树枝间
					t1 =t1-a;//t1向下减小a
					t2=(int)pow(2,t+1)-1;//恢复t2,在每层结点间
				}
			}
			a++;
			b++;
			t1=(int)pow(2,t)-1;	//恢复t1,在每层结点间
			t2=(int)pow(2,t+1)-1;//恢复t2,在每层结点间
			t1 =t1-a;//t1向下减小a
			printf("\n");
		}
		t--;//从根结点逐层向下打印，高度减小1
		t1=(int)pow(2,t)-1;
		t2=(int)pow(2,t+1)-1;
		t3=(int)pow(2,t-1);
		i=2*i;//计算每层结点数，是上一层的2倍（包括虚结点）
	}
	printf("\n");
}

void CreateSeqBinTree(SeqBinTree SBT, int n){
	int i, j, m;
	i=1;m=0;
	while(m<n){
		for(j=i; j<2*i; j++){
			scanf("%c", SBT+j);
			if(SBT[j]!=VIRNODE)
				m++;
		} 
		i=2*i;
	}
	SBT[0]=i-1;
	SBT[i]='\0';
}

void CreateSeqBinTreeFromFile(SeqBinTree SBT){
	int i, j, m, n;
	FILE *pf;
	if((pf=fopen("Data/DSA092.dat","r"))==NULL){
		printf("打开文件DSA092.dat失败!\n");exit(0);
	}
	for(i=0;i<MAXTREESIZE;i++)
		SBT[i]='\0';

	i=1;m=0;
	fscanf(pf, "%d\n", &n);

	while(m<n){
		for(j=i; j<2*i; j++){
			fscanf(pf, "%c", SBT+j);
			if(SBT[j]!=VIRNODE)
				m++;
		} 
		i=2*i;
	}
	SBT[0]=i-1;
	fclose(pf);
}
int GetSBTreeHigh(SeqBinTree SBT){
	int i,h;
	i=1;h=0;
	while(i<=SBT[0]){
		h++;
		i=2*i;
	}
	return h;
}

LinkBinTree* CreateDLRLDR(char DLR[], char LDR[], int n){
	LinkBinTree* t;
	int k;
	if(n<=0) return NULL;
	for(k=0; DLR[0] != LDR[k];k++);
	t=(LinkBinTree* )malloc(sizeof(LinkBinTree*));
	t->data=DLR[0];
	t->lChild=CreateDLRLDR(DLR+1, LDR, k);
	t->rChild=CreateDLRLDR(DLR+1+k, LDR+1+k, n-k-1);
	return t;
}

LinkStack * InitLinkStack(void){
	LinkStack *  LS;
	LS = (LinkStack *)malloc(sizeof(LinkStack));
	LS->next = NULL;
	return LS;
}
int EmptyLinkStack(LinkStack * LS){
	if(LS->next==NULL) return 1;
	else return 0;
}
int LinkPush(LinkStack * LS, LinkBinTree *x){
	LinkStack * p;
	p = (LinkStack *)malloc(sizeof(LinkStack));
	if(!p)return 0;
	p->data=x;
	p->next = LS->next;
	LS->next = p;
	return 1;
}

LinkBinTree * LinkPop(LinkStack * LS){
	LinkStack * p;
	LinkBinTree *e;
	if(LS->next==NULL) return NULL;
	p = LS->next;
	e = p->data;
	LS->next = p->next;
	free(p);
	return e;
}

void PreOrderTree(LinkBinTree * LBT){
	if(LBT!=NULL){
		printf("%c", LBT->data);
		PreOrderTree(LBT->lChild);
		PreOrderTree(LBT->rChild);
	}
}
LinkBinTree * CreateLinkBinTree(void){
	LinkBinTree *LBT;
	ElemType x;
	printf("请输入二叉树的结点数据(#为虚结点):\t");flushall();
	scanf("%c", &x);
	if(x=='#')LBT=NULL;
	else{
		LBT=(LinkBinTree*)malloc(sizeof(LinkBinTree));
		LBT->data=x;
		LBT->lChild=CreateLinkBinTree();
		LBT->rChild=CreateLinkBinTree();
	}
	return LBT;
}
int GetLBTreeHigh(LinkBinTree *LBT){
	int H, H1, H2;
	if(LBT==NULL)H=0;
	else{
		H1=GetLBTreeHigh(LBT->lChild);
		H2=GetLBTreeHigh(LBT->rChild);
		H=(H1>H2 ? H1 : H2)+1;
	}
	return H;
}
void PreOrderNuReserveTraverse(LinkBinTree *LBT){
	LinkStack * LS; 
	LinkBinTree * p;
	LS=InitLinkStack();
	LinkPush(LS,LBT);
	while(!EmptyLinkStack(LS)){
		p=LinkPop(LS);
		while(p){
			printf("%c", p->data);
			if(p->rChild)LinkPush(LS, p->rChild);
			p=p->lChild;
		}
	}
}

LinkBinTree* LBTLChild(LinkBinTree *t)
{
 if(t->lChild==NULL)
    return NULL;
 else
    return t->lChild;
}

LinkBinTree* LBTRChild(LinkBinTree *t)
{
 if(t->rChild==NULL)
    return NULL;
 else
    return t->rChild;
}

void DestroyLinkBinTree(LinkBinTree *t)
{
	if((t!=NULL)&&t->lChild!=NULL)
		DestroyLinkBinTree(LBTLChild(t->lChild));
	if((t!=NULL)&&t->rChild!=NULL)
		DestroyLinkBinTree(LBTRChild(t->rChild));
	free(t);
}


//函数定义
int Max(int a,int b){
	return a>b?a:b;
}

//访问二叉树结点
void Visit(BintreeNode *t){
	if(t) printf("%c",t->Data);
}
//删除二叉树结点
void DeleteNode(BintreeNode *t){
	if(t) free(t);
}
//保存二叉树数据到文件中
void WriteDataToFile(BintreeNode *t){
	if(t)	{
		putc(t->Data,fp);
		WriteDataToFile(t->lChild);
		WriteDataToFile(t->rChild);
	}
	else
		putc('#',fp);//虚结点
}

//键盘输入
char InputFromKeyboard(){
	return getche();
}
//文件输入
char InputFromFile(){
	return getc(fp);
}
//创建二叉树
//根据InOperation的不同进行键盘和文件两种不同方式创建二叉树
void CreateBintree(BintreeNode **t,char (*InOperation)()){
	char ch;
	ch=InOperation();
	if(ch=='#')
		*t=NULL;
	else
	{
		*t=(BintreeNode*)malloc(sizeof(BintreeNode));
		if(!*t)
			exit(OVERFLOW);
		(*t)->Data=ch;
		CreateBintree(&(*t)->lChild,InOperation);
		CreateBintree(&(*t)->rChild,InOperation);
	}
}
//销毁二叉树
void DeleteBintree(BintreeNode *t){
	PostOrder(t,DeleteNode);
}
//前序遍历二叉树
void PreOrder(BintreeNode *t,void (*visit)(BintreeNode *t)){
	if(t){
		visit(t);
		PreOrder(t->lChild,visit);
		PreOrder(t->rChild,visit);
	}
}
//中序遍历二叉树
void InOrder(BintreeNode *t,void (*visit)(BintreeNode *t)){
	if(t){
		InOrder(t->lChild,visit);
		visit(t);
		InOrder(t->rChild,visit);
	}
}
//后序遍历二叉树
void PostOrder(BintreeNode *t,void (*visit)(BintreeNode *t)){
	if(t){
		PostOrder(t->lChild,visit);
		PostOrder(t->rChild,visit);
		visit(t);
	}
}
//设置结点内容
void SetContent(BintreeNode *t,int iOX,int iOY){
	t->OX=iOX;
	t->OY=iOY;
	t->Left=iOX-R;
	t->Top=iOY-R;
	t->Right=iOX+R;
	t->Bottom=iOY+R;
}
//显示叶子结点
void ShowLeavesNode(BintreeNode *t,void (*visit)(BintreeNode *t)){
	if(t){
		if(t->lChild==NULL && t->rChild==NULL)
			visit(t);
		ShowLeavesNode(t->lChild,visit);
		ShowLeavesNode(t->rChild,visit);
	}
}

//绘制叶子结点
void DrawLeaves(BintreeNode *t){
	char s[2];
	HANDLE hOut;//标准输出句柄
	DrawRect(t->OX,t->OY,R);
	s[0]=t->Data;
	s[1]='\0';
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);//RED
	OutTextXY(t->OX,t->OY,s);
	SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );//WHITE
}

//绘制直线连接结点及其叶子结点
void ConnectLeaves(BintreeNode *t1,BintreeNode *t2){
	DrawLine(t1->OX,t1->Bottom,t2->OX,t2->Top);
}
//获得二叉树高度
int GetBintreeHeight(BintreeNode *t){
	if(t==NULL)
		return 0;
	else
		return 1+Max(GetBintreeHeight(t->lChild),GetBintreeHeight(t->rChild));
}

//初始化队列
void InitQueue(DrawingQueue *qu){
	qu->pHead=qu->pTail=NULL;
	qu->Length=0;
}
//入队
void EnQueue(DrawingQueue *qu,BintreeNode *t){
	LeavesPtrNode *p=NULL;
	p=(LeavesPtrNode*)malloc(sizeof(LeavesPtrNode));
	p->LeavesPtr=t;
	p->Next=NULL;
	if(qu->Length==0){
		qu->pTail=qu->pHead=p;
	}else
	{
		qu->pTail->Next=p;
		qu->pTail=qu->pTail->Next;
	}
	qu->Length++;
}
//出队
void DeQueue(DrawingQueue *qu,BintreeNode **t){
	LeavesPtrNode *p=qu->pHead;
	if(qu->Length==0){
		*t=NULL;
		return;
	}
	if(qu->Length==1)
		qu->pHead=qu->pTail=NULL;
	else
		qu->pHead=qu->pHead->Next;
	*t=p->LeavesPtr;
	free(p);
	qu->Length--;
}
//绘制整个二叉树
void DrawTree(BintreeNode *t,int TreeWidth,int RootX,int RootY){
	int NextLevelY;
	int CurrentLevelLeaves=0,NextLevelLeaves=0,Distance,CurrentLevel=0;
	BintreeNode *pLeaves;
	DrawingQueue queue;

	InitQueue(&queue);
	EnQueue(&queue,t);
	SetContent(t,RootX,RootY);
	CurrentLevelLeaves++;
	CurrentLevel++;  //CurrentLevel=1;
	while(queue.Length>0)
	{
		Distance=TreeWidth/(int)pow(2,CurrentLevel-1);
		NextLevelY=RootY+2*(2*CurrentLevel)*2*R;
		while(CurrentLevelLeaves>0)
		{
			DeQueue(&queue,&pLeaves);
			DrawLeaves(pLeaves);
			//printf(" %c",pLeaves->Data);
			if(pLeaves->lChild!=NULL)
			{
				SetContent(pLeaves->lChild,pLeaves->OX-Distance/2,NextLevelY);
				ConnectLeaves(pLeaves,pLeaves->lChild);
				EnQueue(&queue,pLeaves->lChild);
				NextLevelLeaves++;
			}
			if(pLeaves->rChild!=NULL)
			{
				SetContent(pLeaves->rChild,pLeaves->OX+Distance/2,NextLevelY);
				ConnectLeaves(pLeaves,pLeaves->rChild);
				EnQueue(&queue,pLeaves->rChild);
				NextLevelLeaves++;
			}
			CurrentLevelLeaves--;
		}
		CurrentLevelLeaves=NextLevelLeaves;
		NextLevelLeaves=0;
		CurrentLevel++;
	}
}
//定位函数，行列屏幕坐标，单位像素
void OutTextXY(int x, int y, const char * s){ //x为列坐标,y为行坐标
	COORD pos = {x,y};//定义坐标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//设置一个句柄
	SetConsoleCursorPosition(hOut, pos);
	if(s!=NULL)
		printf("%s", s);
} 
//绘制矩形的二叉树结点
void DrawRect(int x, int y, int r){
	DrawLine(x-r,y-r, x+r,y-r);
	DrawLine(x+r,y-r, x+r,y+r);
	DrawLine(x+r,y+r, x-r,y+r);
	DrawLine(x-r,y+r, x-r,y-r);
}
//绘制直线段
void DrawLine(int xa,int ya,int xb,int yb){
	int Dx=xb-xa,Dy=yb-ya,steps,k; 
	float xin,yin,X=(float)xa,Y=(float)ya; 
	if(abs(Dx)>abs(Dy)) 
		steps=abs(Dx); 
	else 
		steps=abs(Dy); 

	xin=Dx/(float)steps; 
	yin=Dy/(float)steps; 
	OutTextXY(ROUND(X),ROUND(Y),"");
	printf("%c",001);

	for(k=0;k<steps;k++){ 
		X=X+xin; 
		Y=Y+yin; 
		OutTextXY(ROUND(X),ROUND(Y),"");
		printf("%c",001);
	} 
}
//获得控制台窗口的最大X值
int GetMaxX(){
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // 窗口缓冲区信息
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//设置一个句柄
	GetConsoleScreenBufferInfo(hOut, &bInfo); //获取窗口缓冲区信息
	return bInfo.dwSize.X;
}
//获得控制台窗口的最大Y值
int GetMaxY(){
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // 窗口缓冲区信息
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//设置一个句柄
	GetConsoleScreenBufferInfo(hOut, &bInfo); //获取窗口缓冲区信息
	return bInfo.dwSize.Y;
}

BintreeNode* LChild(BintreeNode *t){
	 if(t->lChild==NULL)
		return NULL;
	 else
		return t->lChild;
}

BintreeNode* RChild(BintreeNode *t){
	 if(t->rChild==NULL)
		return NULL;
	 else
		return t->rChild;
}

void DestroyBinTree(BintreeNode *t){
	if((t!=NULL)&&t->lChild!=NULL)
		DestroyBinTree(LChild(t->lChild));
	if((t!=NULL)&&t->rChild!=NULL)
		DestroyBinTree(RChild(t->rChild));
	free(t);
}
/*btree depth*/
int Depth(BintreeNode *T){
	int dep1,dep2;
	if(T==NULL)
		return(0);
	else
	{
		dep1=Depth(T->lChild);
		dep2=Depth(T->rChild);
		if(dep1>dep2)
			return(dep1+1);
		else
			return(dep2+1);
	}
}
//中序遍历，二叉树的凹凸表表示法
void PrintBinTree(BintreeNode * t, int n){
	int i;
	if(t==NULL)return;/*exit*/
	PrintBinTree(t->rChild,n+1);
	for(i=0;i<n-1;i++)
		printf("  ");
	if(n>0){
		printf("--");
		printf("%c\n",t->Data);
	}
	PrintBinTree(t->lChild,n+1);
}
//先序遍历，二叉树的广义表表示法
void PrintBinTreeGL(BintreeNode * t){
	if(t==NULL)return;/*exit*/
	printf("(");
	printf("%c", t->Data);
	PrintBinTreeGL(t->lChild);
	PrintBinTreeGL(t->rChild);
	printf(")");
}
/*current node insert left note*/
BintreeNode * InsertLeftNode(BintreeNode *LBT, char v)
{
	BintreeNode *s, *t;
	if(LBT==NULL) return NULL;
	s=LBT->lChild;
	t = (BintreeNode*)malloc(sizeof(BintreeNode)); 
	t->Data = v;
	t->lChild = s;
	t->rChild =NULL;
	
	LBT->lChild = t;	
    return LBT->lChild;
}

/*current node insert right note*/
BintreeNode * InsertRightNode(BintreeNode * LBT, char v)
{
	BintreeNode* s, *t;
	if(LBT==NULL) return NULL;
	s=LBT->rChild;
	t = (BintreeNode*)malloc(sizeof(BintreeNode)); 
	t->Data = v;
	t->rChild = s;
	t->lChild =NULL;
	
	LBT->rChild = t;	
    return LBT->rChild;
}

void SearchNode(BintreeNode *bt, char x, BintreeNode **p, BintreeNode**f){
	if(bt!=NULL)
		if(bt->Data==x){
			*p=bt;
		}
		else{
			*f=bt;
			SearchNode(bt->lChild, x, p, f);
			*f=bt;
			SearchNode(bt->rChild, x, p, f);
		}
}
void DeleteNodeX(BintreeNode **bt, char x){
	BintreeNode *p, *f, *q, *s;
	p=f=NULL;
	SearchNode(*bt, x, &p, &f);
	if(p!=NULL)
		if(p->lChild!=NULL){
			q=p->lChild;
			s=q;
			while(s->rChild!=NULL){q=s; s=s->rChild;}
			if(s!=q)q->rChild=s->lChild;
			else p->lChild=q->lChild;
			p->Data=s->Data;
			free(s);
		}
		else{
			if(f!=NULL)
				if(p==f->lChild)f->lChild=p->rChild;
				else f->rChild=p->rChild;
			else *bt=(*bt)->rChild;
			free(p);
		
		}
	else
		printf("结点%c不在二叉树中!\n",x);
}

/*按树的形状打印竖向二插树*/
void PrintTree(BintreeNode *bt,int nLayer)

{
	int i;
	if(bt==NULL) return;
	PrintTree(bt->rChild, nLayer+4);
	for(i=0;i<nLayer;i++)
		printf(" ");
	printf("%c\n",bt->Data);/*按逆中序输出结点，用程次决定左右位置*/
	PrintTree(bt->lChild, nLayer+4);
}
void HuffmanCoding(HuffmanTree HT, HuffmanCode HC, double *w, int n)
{
	int i, j, m, start, s1, s2, f;
	unsigned int c;
	HuffmanTree p;
	char *cd;

	if(n<=1)exit(0);
	m=2*n-1;//哈夫曼树结点总数

	//构造哈夫曼树
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(p=HT, i=1; i<=n; i++){//n个字符
		p[i].weight=w[i];
		p[i].parent=0;
		p[i].lchild=0;
		p[i].rchild=0;
	}

	for(; i<=m; i++){//初始化n个后的结点
		p[i].weight=0;
		p[i].parent=0;
		p[i].lchild=0;
		p[i].rchild=0;
	}
	for(i=n+1; i<=m; i++){//生成哈夫曼树
		j=1;
		p=HT;
		while(j<=i-1 && p[j].parent!=0)j++;
		s1=j;
		while(j<=i-1){
			if(p[j].parent==0 && p[j].weight < p[s1].weight) s1=j;
			j++;
		}
		p[s1].parent=i;
		j=1;
		p=HT;
		while(j<=i-1 && p[j].parent!=0)j++;
		s2=j;
		while(j<=i-1)
		{
			if(p[j].parent==0 && p[j].weight < p[s2].weight) s2=j;
			j++;
		}
		
		if(s1>s2)
		{	j=s1; s1=s2; s2=j;}

		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight + HT[s2].weight;
	}
	
	//哈夫曼编码
	HC=(HuffmanCode)malloc(sizeof(char*)*(n+1));
	cd=(char*)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;i++){
		start=n-1;
		for(c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent)
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
			HC[i]=(char*)malloc((n-start)*sizeof(char));
			strcpy(HC[i],cd+start);
	}
	free(cd);
}

void HuffmanCoding2(HuffmanTree HT, HuffmanCode HC, double *w, int n)
{
	int i, ii, j, m, start, s1, s2, f;
	unsigned int c;
	HuffmanTree p;
	char *cd;

	if(n<=1)exit(0);
	m=2*n-1;//哈夫曼树结点总数

	//构造哈夫曼树
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(p=HT, i=1; i<=n; i++){//n个字符
		p[i].weight=w[i];
		p[i].parent=0;
		p[i].lchild=0;
		p[i].rchild=0;
	}
	printf("哈夫曼树生成前:\n");
	printf("Char\tweight\tparent\tlchild\trchild\n");
	for(i=1;i<=n;i++)
		printf("%c\t%3.2f\t%d\t%d\t%d\n",
		'A'+i-1,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);

	for(; i<=m; i++){//初始化n个后的结点
		p[i].weight=0;
		p[i].parent=0;
		p[i].lchild=0;
		p[i].rchild=0;
	}
	for(i=n+1; i<=m; i++){//生成哈夫曼树
		j=1;
		p=HT;
		while(j<=i-1 && p[j].parent!=0)j++;
		s1=j;
		while(j<=i-1){
			if(p[j].parent==0 && p[j].weight < p[s1].weight) s1=j;
			j++;
		}
		p[s1].parent=i;
		j=1;
		p=HT;
		while(j<=i-1 && p[j].parent!=0)j++;
		s2=j;
		while(j<=i-1)
		{
			if(p[j].parent==0 && p[j].weight < p[s2].weight) s2=j;
			j++;
		}
		
		if(HT[s1].weight>HT[s2].weight)
		//if(s1>s2)
		{	j=s1; s1=s2; s2=j;}

		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight + HT[s2].weight;
			
		printf("哈夫曼树生成%d步:\n", i-n);			
		printf("No.\tchar\tweight\tparent\tlchild\trchild\n");
		for(ii=1;ii<=n;ii++)
			printf("%d\t%c\t%3.2f\t%d\t%d\t%d\n",
			ii,'A'+ii-1,HT[ii].weight,HT[ii].parent,HT[ii].lchild,HT[ii].rchild);
		for(ii=n+1;ii<=i;ii++)
			printf("%d\t%c\t%3.2f\t%d\t%d\t%d\n",
			ii,' ',HT[ii].weight,HT[ii].parent,HT[ii].lchild,HT[ii].rchild);

	}
	printf("哈夫曼树生成后:\n");
	printf("No.\tchar\tweight\tparent\tlchild\trchild\n");
	for(i=1;i<=n;i++)
		printf("%d\t%c\t%3.2f\t%d\t%d\t%d\n",
		i,'A'+i-1,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	for(i=n+1;i<=m;i++)
		printf("%d\t%c\t%3.2f\t%d\t%d\t%d\n",
		i,' ',HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	
	//哈夫曼编码
	HC=(HuffmanCode)malloc(sizeof(char*)*(n+1));
	cd=(char*)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;i++){
		start=n-1;
		for(c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent)
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
			HC[i]=(char*)malloc((n-start)*sizeof(char));
			strcpy(HC[i],cd+start);
	}
	free(cd);

	printf("哈夫曼编码:\n");
	printf("Char\tcode\n");
	for(i=1;i<=n;i++)
		printf("%c\t%s\n",'A'+i-1, HC[i]);

}


void HuffmanCoding3(HuffmanTree HT, HuffmanCode HC, double *w, int n)
{
	int i, ii, j, m, s1, s2, cdlen;
	HuffmanTree p;
	char *cd;

	if(n<=1)exit(0);
	m=2*n-1;//哈夫曼树结点总数

	//构造哈夫曼树
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(p=HT, i=1; i<=n; i++){//n个字符
		p[i].weight=w[i];
		p[i].parent=0;
		p[i].lchild=0;
		p[i].rchild=0;
		p[i].ch = 'a'+i-1;
	}
	printf("哈夫曼树生成前:\n");
	printf("Char\tweight\tparent\tlchild\trchild\n");
	for(i=1;i<=n;i++)
		printf("%c\t%3.2f\t%d\t%d\t%d\n",
		'a'+i-1,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);

	for(; i<=m; i++){//初始化n个后的结点
		p[i].weight=0;
		p[i].parent=0;
		p[i].lchild=0;
		p[i].rchild=0;
		p[i].ch = ' ';
	}
	for(i=n+1; i<=m; i++){//生成哈夫曼树
		j=1;
		p=HT;
		while(j<=i-1 && p[j].parent!=0)j++;
		s1=j;
		while(j<=i-1){
			if(p[j].parent==0 && p[j].weight < p[s1].weight) s1=j;
			j++;
		}
		p[s1].parent=i;
		j=1;
		p=HT;
		while(j<=i-1 && p[j].parent!=0)j++;
		s2=j;
		while(j<=i-1)
		{
			if(p[j].parent==0 && p[j].weight < p[s2].weight) s2=j;
			j++;
		}
		
		if(HT[s1].weight>HT[s2].weight)
		//if(s1>s2)
		{	j=s1; s1=s2; s2=j;}

		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight + HT[s2].weight;
			
		printf("哈夫曼树生成%d步:\n", i-n);			
		printf("No.\tchar\tweight\tparent\tlchild\trchild\n");
		for(ii=1;ii<=n;ii++)
			printf("%d\t%c\t%3.2f\t%d\t%d\t%d\n",
			ii,'a'+ii-1,HT[ii].weight,HT[ii].parent,HT[ii].lchild,HT[ii].rchild);
		for(ii=n+1;ii<=i;ii++)
			printf("%d\t%c\t%3.2f\t%d\t%d\t%d\n",
			ii,' ',HT[ii].weight,HT[ii].parent,HT[ii].lchild,HT[ii].rchild);

	}
	printf("哈夫曼树生成后:\n");
	printf("No.\tchar\tweight\tparent\tlchild\trchild\n");
	for(i=1;i<=n;i++)
		printf("%d\t%c\t%3.2f\t%d\t%d\t%d\n",
		i,'a'+i-1,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	for(i=n+1;i<=m;i++)
		printf("%d\t%c\t%3.2f\t%d\t%d\t%d\n",
		i,' ',HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	
	//哈夫曼编码
	HC=(HuffmanCode)malloc(sizeof(char*)*(n+1));
	cd=(char*)malloc(n*sizeof(char));
	j=m;cdlen=0;
	for(i=1; i<=m; i++)HT[i].weight=0;
	while(j){
		if(HT[j].weight==0){
			HT[j].weight=1;
			if(HT[j].lchild!=0){
				j=HT[j].lchild;cd[cdlen++]='0';
			}
			else if(HT[j].rchild==0){
				cd[cdlen]='\0';
				HC[j]=(char*)malloc((cdlen+1)*sizeof(char));
				strcpy(HC[j], cd);
			}
		}
		else if(HT[j].weight==1){
			HT[j].weight=2;
			if(HT[j].rchild!=0){
				j=HT[j].rchild; cd[cdlen++]='1';
			}
		}
		else{
			HT[j].weight=0;j=HT[j].parent;cdlen--;
		}
	}

	printf("哈夫曼编码:\n");
	printf("Char\tcode\n");
	for(i=1;i<=n;i++){
		printf("%c\t%s\n",'a'+i-1, HC[i]);
		strcpy(hcodes[i-1],HC[i]);
	}
	
}

//用户输入编码字符
void EncodeHC()
{
	int i=0,j,f=1;
	char str[500]={'\0'};
	char code[500]={'\0'};
	printf("\n请输入要编码的字符串(小写，千万不要输错!)\n");
	scanf("%s",str);
	while(str[i]){
		if((str[i]>='a'&&str[i]<='z')){
    		for(j=0;j<26;j++)
	    		if(str[i]==(char)(j+'a')){
		    		strcat(code,hcodes[j]);
			    	break;
			}
	    	i++;
		}else{
			f=0;
			break;
		}
	}
	if(f)
    	puts(code);
	else
		printf("有无码的字符，无法编码！\n");

}
//哈夫曼解码，每次都从根节点开始搜索
int ReleaseHuffCode(HuffmanTree ht, char *str,char* code)
{
	int n=26;
	int root=2*n-1;
	int length=0,i=0;
	while(code[i]){
		if(code[i]=='0'+0)
			root=ht[root].lchild;
		else if(code[i]=='0'+1)
			root=ht[root].rchild;
		else
			return 0;
		if(ht[root].lchild==0 && ht[root].rchild==0){
	    	str[length++]=ht[root].ch;
			root=2*n-1;
		}
		i++;
	}
	str[length]='\0';
	if(root==2*n-1)
		return 1;
	return 0;
}
//用户输入解码字串
void  DecodeHC(HuffmanTree ht)
{
	char str[50];
	char code[500];
	printf("\n请输入要解码的字串(用0和1表示，千万不要输错!)\n");
	scanf("%s",code);
	if(ReleaseHuffCode(ht, str, code))
		puts(str);
	else
		printf("你输入的字串错误！\n");	
}

void HuffmanCoding4(HuffmanTree *HT, double *w, int n)
{
	int i, j, m, s1, s2;
	HTNode *p;

	if(n<=1)exit(0);
	m=2*n-1;//哈夫曼树结点总数

	//构造哈夫曼树
	*HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(i=1; i<=n; i++){//n个字符
		(*HT)[i].weight=w[i];
		(*HT)[i].parent=0;
		(*HT)[i].lchild=0;
		(*HT)[i].rchild=0;
		(*HT)[i].ch = 'a'+i-1;
	}

	for(; i<=m; i++){//初始化n个后的结点
		(*HT)[i].weight=0;
		(*HT)[i].parent=0;
		(*HT)[i].lchild=0;
		(*HT)[i].rchild=0;
		(*HT)[i].ch = ' ';
	}
	for(i=n+1; i<=m; i++){//生成哈夫曼树
		j=1;
		p=*HT;
		while(j<=i-1 && p[j].parent!=0)j++;
		s1=j;
		while(j<=i-1){
			if(p[j].parent==0 && p[j].weight < p[s1].weight) s1=j;
			j++;
		}
		p[s1].parent=i;
		j=1;
		p=*HT;
		while(j<=i-1 && p[j].parent!=0)j++;
		s2=j;
		while(j<=i-1)
		{
			if(p[j].parent==0 && p[j].weight < p[s2].weight) s2=j;
			j++;
		}
		
		if((*HT)[s1].weight>(*HT)[s2].weight)
		{	j=s1; s1=s2; s2=j;}

		(*HT)[s1].parent=i;(*HT)[s2].parent=i;
		(*HT)[i].lchild=s1;(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight + (*HT)[s2].weight;
	}	
}

//初始化
void InitCSTree(CSTree *T){
    (*T)->firstChild = NULL;
    (*T)->nextSibling = NULL;
}

//创建树
void CreateCSTree(CSTree *T){
    int i;CSTree s,temp;
    FILE *fin=fopen("Data/DSA093.dat","r");  
    char fa=' ',ch=' ';
    for( fscanf(fin,"%c%c\n",&fa,&ch); ch!='#'; fscanf(fin,"%c%c\n",&fa,&ch) ) 
    {      
        CSTree p=(CSTree)malloc(sizeof(CSTree)); 
        InitCSTree(&p);
        p->data=ch;
        q[++count]=p;

        if('#' == fa)
            (*T)=p;
        else {
            s = (CSTree)malloc(sizeof(CSTree));
            for(i=1;i<=MAXSIZE;i++){
                if(q[i]->data == fa){
                    s=q[i];
                    break;
                }
            }
            if(! (s->firstChild) ) //如果该双亲结点还没有接孩子节点
                s->firstChild=p;
            else{        //如果该双亲结点已经接了孩子节点
                temp=s->firstChild;
                while(NULL != temp->nextSibling){
                    temp=temp->nextSibling;
                }
                temp->nextSibling=p;
            }
        }
    } 
    fclose(fin);
}
//前序遍历
void PrintCSTree(CSTree *T){
        printf("%c ", (*T)->data);
        if((*T)->firstChild!=NULL)
            PrintCSTree(&(*T)->firstChild);
        if((*T)->nextSibling!=NULL)
            PrintCSTree(&(*T)->nextSibling);
}
//后序遍历销毁
void DestroyCSTree(CSTree *T){
	if(*T==NULL)return;
	if((*T)->firstChild)
		DestroyCSTree(&(*T)->firstChild);
	if((*T)->nextSibling)
		DestroyCSTree(&(*T)->nextSibling);
	free(*T);
	*T=NULL;
}