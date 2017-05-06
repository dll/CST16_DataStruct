#include "stdio.h"
#include "malloc.h"
#define OK 1
#define ERROR 0
//#define MAXQSIZE 10 	/*�����г���+1*/
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
	if( (Q->rear+1)%MaxQSize == Q->front ) // ������
		return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = ( Q->rear + 1 ) % MaxQSize;
	return OK;
}


int DeQueue(SqQueue *Q, QElemType *e)
{ 
	if(Q->front == Q->rear)     // ���п�
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
{	/*�Ӷ�ͷ����β���δ�ӡ����Q��ÿ��Ԫ��*/
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
	printf("��ѭ���������ɴ��%d��Ԫ��\n",MaxQSize-1);
	printf("�س�����������������д�С��\n");
	if(getchar()=='\n')
		scanf("%d",&MaxQSize);
	
	InitQueue(&q);	//��ʼ��ѭ������
	printf("��ѭ���������ɴ��%d��Ԫ��\n",MaxQSize-1);
	printf("����������Ԫ�صĸ���n \n");
	scanf("%d",&n);
	printf("\n������%d������\n",n);
	/*��������*/
	for(i=1;i<=n;i++)
	{
		scanf("%d",&e);
		EnQueue(&q,e);       //���
	}
	printf("q=");
	QueueTraverse(q);     //���ѭ������q������
	fflush(stdin);//ˢ�»�����
	printf("\n���������Ԫ��e\n");
	scanf("%d",&e);
	EnQueue(&q,e);      //���
	printf("q=");
	QueueTraverse(q);          //���ѭ������q������
	fflush(stdin);//ˢ�»�����
	printf("\nִ�г��Ӳ���\n");
	DeQueue(&q,&e);          //����
	printf("����Ԫ����%d\n",e);//�������Ԫ��ֵ
	printf("q=");
	QueueTraverse(q);;           //���ѭ������q������
	DestoryQueue(&q);
}
void testYHTriangle()
{
	int i,j,h,m,n;
	printf("����������ǵ�������");
	scanf("%d",&h);
	SqQueue q;
	InitQueue(&q);
	EnQueue(&q,0);        //��ʼ����0���
	EnQueue(&q,1);         //��ʼ����1���
	DeQueue(&q,&m);        //���ӵ�m
	for(i=0;i<h;i++)        //��h��
	{
		EnQueue(&q,0);        //ÿ�������0
		for(j=0;j<i+2;j++)    //��i����i+2����������0����������i+1������
		{
			n=m;                    //ȡ��һ�ֵ�m
			DeQueue(&q,&m);        //���ӵ�m
			EnQueue(&q,m+n);    //��m+n���
			if(n!=0)                    //��n��0�����
				printf("%d ",n);
		}
		printf("\n");                //һ�ֽ���������
	}
}
void testMonkeyKing(){
	int e,step=3;
	MaxQSize=42;
	SqQueue q;
	printf("���뱨����");
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
