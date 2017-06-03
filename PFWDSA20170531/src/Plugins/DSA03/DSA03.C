/*
*文件：DSA03.C
*插件文件，实现链表的所有操作
*作者：刘东良
*日期: 2012-09-10
*/

#include "DSA03.h"

//在[min, max]之间生成n个随机整数数组
ElemType RandElem(ElemType min, ElemType max){
	ElemType x;
	int minValue=min, maxValue=max;
	//time_t tx;
	srand((unsigned) time(NULL));
	x = min+(int)max*(rand() % (maxValue-minValue+1))/max;
	return x;
}
// SL是带头结点的链表的头指针，以 x 返回第 i 个元素
int GetLinkListElem(LinkList LL, int i, ElemType *x) {
	LinkNode* p = LL->next;
	int j = 1;  // p指向第一个结点，j为计数器
	while (p && j<i)  {
		p = p->next;
		++j;
	}
	// 顺指针向后查找，直到 p 指向第 i 个元素或 p 为空
	if ( !p || j>i )
		return 0;  //第 i 个元素不存在
	*x = p->data;  //  取得第 i 个元素
	return 1;//成功
} // GetElem
 
int InsertLinkListElem(LinkList LL, int i, ElemType x, int speed) {
     // SL 为带头结点的单链表的头指针，本算法
     // 在链表中第i 个结点之前插入新的元素 x
	int ii;
	LinkNode *s, *q=LL;
	LinkNode *p = LL;
    int j = 0;
	
	printf("\n动画显示插入操作过程：在%d 位置前插入%d 元素...\n", i, x);
	PrintLinkList(LL);
	printf("正在后移指针^\n");
	Sleep(speed);
	while (p && j < i-1) {
		system("CLS");
		printf("动画显示插入操作过程：在%d 位置前插入%d 元素...\n", i, x);
		PrintLinkList(LL);
		printf("正在后移指针^\n\n");
		Sleep(speed);
		p = p->next;
		for(ii=0;ii<GetLinkListLength(LL);ii++){
			q=q->next;
			if(ii%10==0 && ii!=0 )printf("\n");
				if(ii==j)
					printf("%5d->^ ", q->data);
				else
					printf("%5d-> ", q->data);
		}
		q=LL;
		Sleep(speed);
		++j;
	}   // 寻找第 i-1 个结点
	system("CLS");
	printf("找到%d(%d)位置!\n", i, i-1);

	if (!p || j > i-1)
		return 0;   // i 大于表长或者小于1
	Sleep(speed/10);
	printf("申请新结点空间 ");
	s = (LinkNode*) malloc ( sizeof (LinkNode));  // 申请新结点
	s->data = x; 
	Sleep(speed/10);
	printf(" 新结点入链 ");
	s->next = p->next;
	Sleep(speed/10);
	printf(" 断链及重新拉链 ");
	p->next = s; // 插入
	Sleep(speed/10);
	printf(" 链表%d插入%d完成! \n", i, x);
	return 1;

} // LinstInsert

int DeleteLinkListElem(LinkList LL, int i, ElemType *x, int speed) {
   // 删除以 LL 为头指针(带头结点)的单链表中第 i 个结点
	LinkNode* p;
	LinkNode* q;
	LinkNode* t;
	int j, ii;
	p = LL;
    t = LL;
	j = 0;

	printf("\n动画显示删除操作过程：删除在%d 位置上%d 元素...\n", i, *x);
	PrintLinkList(LL);
	printf("正在后移指针^\n");
	Sleep(speed);

	while (p->next && j < i-1) {
		system("CLS");
		printf("动画显示删除操作过程：在%d 位置上插入%d 元素...\n", i, *x);
		PrintLinkList(LL);
		printf("正在后移指针^\n\n");
		Sleep(speed/2);
		
		p = p->next;
		
		for(ii=0;ii<GetLinkListLength(LL);ii++){
			t=t->next;
			if(ii%10==0 && ii!=0 )printf("\n");
				if(ii==j)
					printf("%5d->^ ", t->data);
				else
					printf("%5d-> ", t->data);
		}
		t=LL;
		Sleep(speed);
		++j;
	} 
	system("CLS");
	printf("找到%d(%d)位置!\n", i, i-1);
	Sleep(speed/10);
	// 寻找第 i 个结点，并令 p 指向其前趋
	if  (!(p->next) || j > i-1) 
		return 0;  // 删除位置不合理

	printf("链表定位 ");
	q = p->next;
	Sleep(speed/10);
	printf("待结点脱链 ");
	p->next = q->next;  // 删除结点
	*x = q->data;
	Sleep(speed/2);
	printf("释放结点空间 ");
	free(q);//释放结点

	Sleep(speed/10);
	printf(" 链表%d位置上删除%d完成! \n", i, *x);
	return 1;
} // LinkListDelete

void ClearLinkList(LinkList * LL) {
   // 将单链表重新置为一个空表
    LinkNode* p=*LL;
	while ((*LL)->next) {
        p=(*LL)->next;    (*LL)->next=p->next; 
		free(p);
    }
	(*LL)->next=NULL;
} // ClearLinkList

void CreateLinkList(LinkList *LL, int n) {
    // 逆序输入 n 个数据元素，建立带头结点的单链表	
	LinkNode* p;
	int i;
	*LL = (LinkList) malloc (sizeof (LinkNode));
	(*LL)->next = NULL;    // 先建立一个带头结点的单链表
	for (i = n; i > 0; --i) {
		p = (LinkNode*) malloc (sizeof (LinkNode));
		printf("请输入第 %d 个结点数据:\t", i);
		scanf("%d", &p->data);    // 输入元素值
		p->next = (*LL)->next;
		(*LL)->next = p;  // 插入
	}
} // CreateLinkList

void PrintLinkList(LinkList LL) {
   int i=1;
   LinkNode* p=LL;
   if(GetLinkListLength(LL)==0){
		printf("链表为空表!\n"); return;
   }
   while (p->next) {
        p=p->next;
		//printf("[%d] %5d  %d ", i++,p->data,&p->data);
		printf("%5d->", p->data);
    }
   printf("\n");
} // PrintLinkList

void ReadLinkList(LinkList LL, char * fname){
	int i;
	FILE *pf;//FILE类型的指针变量pf
	ElemType x;

	pf= fopen(fname, "r");//打开文件
	if(!pf){
		printf("打开文件失败!可能该文件不存在\n");
		return;
	}
	//读数前，确保顺序表有空间可用存放数据
	//同时，系统当前只保留从文件中读到的数据
	CreateLinkList(&LL, 0);

	for(i=1;!feof(pf);i++){//feof判断pf指针是否读到文件结尾
		fscanf(pf, "%d\t", &x);//与scanf比较比较
		printf("%d\t", x);
		InsertLinkListElem(LL, i, x, 0);
	}
	fclose(pf);//关闭文件，与fopen配对使用
}
int GetLinkListLength(LinkList LL){
	LinkNode* p;
	int n;
	p=LL->next;n=0;
	while(p){
		n++;
		p=p->next;
	}
	return n;
}
int LocateLinkListElem(LinkList LL, ElemType x){

	int i=1;
	LinkNode* p=LL->next;
	while (p) {
		if(x==p->data) return i;
		else
			i++;
		p=p->next;
    }
	return 0;//失败
}

void SaveLinkList(LinkList LL, char * fname){
	int i;
	LinkNode* p = LL->next;
	FILE *pf;
	pf= fopen(fname, "w");
	if(!pf){
		printf("创建保存文件失败!\n");
		return;
	}

	for(i=0;p;i++){
		if(i%10==0 && i!=0 )printf("\n");
			fprintf(pf, "%5d\t", p->data);//与printf比较比较
		p=p->next;
	}
	fclose(pf);
	printf("\n关闭保存文件后自动返回...\n");
	system(fname);//打开文件
}

void EditLinkListElem(LinkList LL, int i, ElemType x){
	int j=1;
	LinkNode* p = LL->next;
	while(p && j<i){p=p->next;++j;}
	if ( !p || j>i ){ printf("链表中%d 位置上不存在元素", i);   return;}      
	p->data = x;  //  修改第 i 个元素
}
//比较函数
int ElemTypeCmp(ElemType a, ElemType b) {
	if(a==b)
		return 1;
	else
		return 0;
} 