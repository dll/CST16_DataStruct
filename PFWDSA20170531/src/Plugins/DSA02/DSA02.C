/*
*文件：DSA02.C
*插件文件，实现顺序列表的所有操作
*作者：刘东良
*日期: 2012-09-10
*/

#include "DSA02.h"

//使用静态数组实现顺序表
void  InitSeqList( SeqListA SL,  int n)
{  
    int  i;
    for ( i=0; i<n ; i++){
	printf("请输入第 %d 个元素: ",i);
        scanf("%d", &SL[i]);
    }
}
//使用动态数组实现顺序表
void InitSeqList2( SeqList* SL ) {
	// 构造一个空的线性表 
	SL->data = (ElemType*) malloc (INITSIZE*sizeof (ElemType));
	SL->length = 0;
	SL->listsize = INITSIZE;
} // InitSeqList

//二级指针为参数的，也可以返回一级指针的函数
//SeqList* SL InitSeqList3( SeqList * SL)
//本次实验跳过
void  InitSeqList3( SeqList ** SL){
	(*SL)->data = (ElemType*) malloc (INITSIZE*sizeof (ElemType));
	(*SL)->length = 0;
	(*SL)->listsize = INITSIZE;
}
//销毁并重新分配
void ClearSeqList( SeqList * SL){
	int i;
	if(SL->length==0){
		printf("顺序表为空表!\n");
		return;
	}
	else{
		printf("顺序表里有数据，默认保存到DSA021.tmp文件中[y/n]? \t");flushall();
		if(getchar()=='y'){
			SeqListSave(SL, ".\\Temp\\DSA021.tmp");
			system(".\\Temp\\DSA021.tmp");
			printf("\n关闭保存文件后自动返回...\n");
		}
		free(SL->data);//释放顺序表里的存储数据的空间
		InitSeqList2(SL);//需要重新初始化，否则顺序表的数据为不确定的数据
	}
}
int  SeqListInsert(SeqList *SL, int i, ElemType x, int speed)
{
	int j, ii;
	if (i<1 || i>SL->length+1){
		printf("i值溢出！\n");
		return 0;//失败
	}
	if(SL->length==SL->listsize)
	{
		printf("顺序表空间不足！重置存储空间(增加一个元素空间)\n");
		SL->data=(ElemType*)realloc(SL->data, (SL->listsize + 1) * sizeof(ElemType));
		SL->listsize++;
	}
	for (j=SL->length-1; j>=i-1; j--){
		system("CLS");
		printf("动画显示插入操作过程：在%d 位置上插入%d 元素...\n", i, x);
		SeqListPrint2(SL);
		SL->data[j+1]=SL->data[j];//后移
		printf("正在后移%d元素%d位置->%d位置\n", SL->data[j], j+1, j+2 );
		Sleep(speed);
		
		for(ii=0;ii<SL->length;ii++){
			if(ii%10==0 && ii!=0 )printf("\n");
				if(ii==j)
					printf("%5d-> ", SL->data[ii]);
				else
					printf("%5d ", SL->data[ii]);
		}
		printf("%5d*", SL->data[SL->length]);
		Sleep(speed);
	}
	system("CLS");
	printf("插入完成!\n",i, x);
	SL->data[i-1] = x;
	SL->length++;// 长度加1
	return 1;//成功
}

int  SeqListDelete(SeqList *SL, int i, ElemType* x, int speed)
{   
	int j, ii;
	if (i<1 || i>SL->length){
		printf("i值溢出！\n");
		return 0;
	}
	*x = SL->data[i-1];
	for (j=i; j<SL->length; j++){
		system("CLS");
		printf("动画显示删除操作过程：在%d 位置上删除%d 元素...\n", i, *x);
		SeqListPrint2(SL);	
		SL->data[j-1]=SL->data[j];//前移
		printf("正在前移%d元素%d位置->%d位置\n", SL->data[j], j+1, j );
		Sleep(speed);
		//SeqListPrint2(SL);
		for(ii=0;ii<SL->length;ii++){
			if(ii%10==0 && ii!=0 )printf("\n");
			if(ii==j)
				printf("  <-%5d ", SL->data[ii]);
			else
				printf(" %5d ", SL->data[ii]);
		}
		Sleep(speed);
		SeqListPrint2(SL);
	}
	system("CLS");
	printf("删除完成!\n",i, x);
	SL->length--;// 长度减1
	return 1;	
}
int  SeqListEdit(SeqList *SL, int i, ElemType x)
{   
	if (i<1 || i>SL->length){
		printf("i值溢出！\n");
		return 0;
	}
	SL->data[i-1]=x;//修改指定位序上的数据元素
	return 1;	
}
void ReadSeqList(SeqList *SL, char * fname){
	int i;
	FILE *pf;//FILE类型的指针变量pf
	ElemType x;

	system(fname);//打开文件
	printf("\n关闭文件后自动返回...\n");

	pf= fopen(fname, "r");//打开文件
	if(!pf){
		printf("打开文件失败!可能该文件不存在\n");
		return;
	}
	//读数前，确保顺序表有空间可用存放数据
	//同时，系统当前只保留从文件中读到的数据
	InitSeqList2(SL);

	//多读一行的原因很复杂！google去吧
	//加一个\t,即按写时的格式读取，轻松解决
	for(i=1;!feof(pf);i++){//feof判断pf指针是否读到文件结尾

		fscanf(pf, "%d\t", &x);//与scanf比较比较
		SeqListInsert(SL, i, x, 0);
	}
	fclose(pf);//关闭文件，与fopen配对使用
}
void SeqListSave(SeqList *SL, char * fname){
	int i;
	FILE *pf;
	pf= fopen(fname, "w");
	if(!pf){
		printf("创建保存文件失败!\n");
		return;
	}

	for(i=0;i<SL->length;i++){
		if(i%10==0 && i!=0 )printf("\n");
			fprintf(pf, "%5d\t", SL->data[i]);//与printf比较比较
	}
	//fprintf(pf, "%s ", "\n关闭该文件后自动返回到系统...\n");
	fclose(pf);
	printf("\n关闭保存文件后自动返回...\n");
	system(fname);//打开文件
}
void SeqListPrint(SeqListA SL, int n){
	int i;
	for(i=0;i<n;i++){
		if(i%10==0 && i!=0 )printf("\n");
			printf("%5d ", SL[i]);
	}
	printf("\n");
}
void SeqListPrint2(SeqList *SL){
	char p;
	int i=0;
	if(SL->length==0){
		printf("顺序表为空表!\n");
		return;
	}
	printf("请输入y/Y打印顺序表元素的数值和地址，否则（直接回车）不打印地址![y/n]?\n");
	flushall();
	if((p=getchar())=='y'|| (p=getchar())=='Y'){
		for(i=0;i<SL->length;i++){
			if(i%10==0 && i!=0 )printf("\n");
			printf("[%2.2d] %5d %10d  ",i+1, SL->data[i], &SL->data[i]);
		}
		printf("\n");
	}
	else{
		for(i=0;i<SL->length;i++){
			if(i%10==0 && i!=0 )printf("\n");
			printf("[%2.2d] %5d ",i+1, SL->data[i]);
		}
		printf("\n");
	}
}
//在[min, max]之间生成1个随机整数
ElemType RandElem(ElemType min, ElemType max){
	ElemType x;
	int minValue=min, maxValue=max;
	time_t tx;
	srand((unsigned) time(&tx));
	x = min+(int)max*(rand() % (maxValue-minValue+1))/max;
	return x;
}
//在[min, max]之间生成n个随机整数数组
void RandArray(ElemType min, ElemType max, SeqListA SL, int n){
	int i;
	int minValue=min, maxValue=max;
	srand((unsigned) time(NULL));
	for(i=0;i<n;i++)
		SL[i] = min+(int)max*(rand() % (maxValue-minValue+1))/max;
}

int GetSeqListLength(SeqList *SL)
{
	int len;
	len = SL->length;
	return len;
}
int GetSeqListElem(SeqList *SL, int i, ElemType *x){
	if(i<1 || i>SL->length)
	{
		printf("i值溢出！\n");
		return 0;
	}
	*x = SL->data[i-1];

	return 1;
}

int LocateSeqListElem(SeqList *SL,  ElemType x){
	int i=0;
	while(i<SL->length+1){
		if(SL->data[i]==x)
			return i+1;
		else
			i++;
	}
	return 0;//顺序表中没有x数据元素
}
//比较函数
 int ElemTypeCmp(ElemType a, ElemType b) {
	 if(a==b)
		 return 1;
	 else
		 return 0;
 } 

int LocateSeqListElem2(SeqList *SL,  ElemType x, int(* Cmp)(ElemType a, ElemType b)){
	int i=0;
	while(i<SL->length){
		if(Cmp(SL->data[i],x)==1)
			return 1;
		i++;
	}
	return 0;
}
//P18例2.2
void MoveOddEven(SeqList *SL){

}
void UnionSeqList(SeqList *La, SeqList *Lb) {//merge
	int i, La_len, Lb_len, pos;
	ElemType x;
	La_len = GetSeqListLength(La);    // 求线性表的长度
    	Lb_len = GetSeqListLength(Lb);   
	for (i = 1;  i <= Lb_len;  i++) {
		GetSeqListElem(Lb, i, &x); // 取Lb中第i个数据元素赋给x
		pos = LocateSeqListElem(La, x);
		if (pos>La_len || pos<1) 
			SeqListInsert(La, ++La_len, x, 100);// La中不存在和 x 相同的数据元素，则插入之
	}
}

void UnionSeqList2(SeqList *La, SeqList *Lb) {//merge
	int i, La_len, Lb_len;
	ElemType x;

	InitSeqList2(La);
	La_len = GetSeqListLength(La);    // 求线性表的长度
    	Lb_len = GetSeqListLength(Lb);   
	for (i = 1;  i <= Lb_len;  i++) {
		if(GetSeqListElem(Lb, i, &x)==1) // 取Lb中第i个数据元素赋给x
			if(LocateSeqListElem2(La, x, ElemTypeCmp)==0)
				SeqListInsert(La, ++La_len, x, 100);// La中不存在和 x 相同的数据元素，则插入之
	}
}
