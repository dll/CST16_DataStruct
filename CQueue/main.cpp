#include "stdio.h"
#include "malloc.h"
#define OK 1
#define ERROR 0
//#define MAXQSIZE 10 	/*最大队列长度+1*/
int MaxQSize=10;//int size;
typedef int QElemType;
typedef struct { 
	QElemType *base; 
	int  front;  
	int  rear; 
} SqQueue;


int InitQueue(SqQueue *Q){
	Q->base=(QElemType *)malloc(MaxQSize*sizeof(QElemType));
	if(!Q->base)  return ERROR;
	Q->front = Q->rear = 0;
	return OK;
}


int EnQueue(SqQueue *Q,QElemType e) { 
	if( (Q->rear+1)%MaxQSize == Q->front ) // 队列满
		return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = ( Q->rear + 1 ) % MaxQSize;
	return OK;
}


int DeQueue(SqQueue *Q, QElemType *e)
{ 
	if(Q->front == Q->rear)     // 队列空
		return ERROR;
	*e = Q->base[Q->front];//e = &Q->base[Q->front];
	Q->front = ( Q->front + 1 ) % MaxQSize;
	return OK;
}

int QueueLength(SqQueue Q)
{ 
	return (Q.rear-Q.front+MaxQSize)%MaxQSize;
}
void QueueTraverse(SqQueue Q)
{	/*从队头到队尾依次打印队列Q中每个元素*/
   	for(int i=Q.front;i<Q.rear;i++)
		printf("%d ",Q.base[i]);
	printf("\n");
} 
int DestoryQueue(SqQueue *Q){
	if(Q->base){
		free(Q->base);
		return OK;
	}
	else
	   return ERROR;
	return OK;
}
void testCQueue(){
	int n,e,i;
	SqQueue q;
	printf("该循环队列最多可存放%d个元素\n",MaxQSize-1);
	printf("回车继续，否则输入队列大小！\n");
	if(getchar()=='\n')
		scanf("%d",&MaxQSize);
	
	InitQueue(&q);	//初始化循环队列
	printf("该循环队列最多可存放%d个元素\n",MaxQSize-1);
	printf("请输入数据元素的个数n \n");
	scanf("%d",&n);
	printf("\n请输入%d个整数\n",n);
	/*创建队列*/
	for(i=1;i<=n;i++)
	{
		scanf("%d",&e);
		EnQueue(&q,e);       //入队
	}
	printf("q=");
	QueueTraverse(q);     //输出循环队列q的内容
	fflush(stdin);//刷新缓冲区
	printf("\n请输入入队元素e\n");
	scanf("%d",&e);
	EnQueue(&q,e);      //入队
	printf("q=");
	QueueTraverse(q);          //输出循环队列q的内容
	fflush(stdin);//刷新缓冲区
	printf("\n执行出队操作\n");
	DeQueue(&q,&e);          //出队
	printf("出队元素是%d\n",e);//输出出队元素值
	printf("q=");
	QueueTraverse(q);;           //输出循环队列q的内容
	DestoryQueue(&q);
}
void testYHTriangle()
{
	int i,j,h,m,n;
	printf("输入杨辉三角的行数：");
	scanf("%d",&h);
	SqQueue q;
	InitQueue(&q);
	EnQueue(&q,0);        //初始化，0入队
	EnQueue(&q,1);         //初始化，1入队
	DeQueue(&q,&m);        //出队到m
	for(i=0;i<h;i++)        //共h行
	{
		EnQueue(&q,0);        //每行先入队0
		for(j=0;j<i+2;j++)    //第i行有i+2个数，其中0不输出（输出i+1个数）
		{
			n=m;                    //取上一轮的m
			DeQueue(&q,&m);        //出队到m
			EnQueue(&q,m+n);    //将m+n入队
			if(n!=0)                    //若n非0就输出
				printf("%d ",n);
		}
		printf("\n");                //一轮结束，换行
	}
}
void testMonkeyKing(){
	int e,step=3;
	MaxQSize=42;
	SqQueue q;
	printf("输入报数：");
	scanf("%d",&step);
	
	InitQueue(&q);
	for(int i=0;i<MaxQSize;i++)
		EnQueue(&q,i+1);
	QueueTraverse(q);
	int j=q.front;
	while(QueueLength(q)!=1){
		for(j=1;j<step;j++){
			DeQueue(&q,&e);
			EnQueue(&q,e);
		}
		DeQueue(&q,&e);
		printf("%d ", e);
	}
	DeQueue(&q,&e);
	printf("\nThe MonkeyKing is :%d ", e);
	DestoryQueue(&q);
}
int main()
{
//	testCQueue();
	testYHTriangle();
//	testMonkeyKing();
	
	return 0;
}      
