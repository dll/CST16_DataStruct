#include <windows.h> 

#include "../include/DSATestServices.h"

//返回从[min,max)之间的一个随机整型数
int RandInt(const int min, const int max)
{
	int i;
	time_t tx;	
	srand((unsigned) time(&tx));//srand函数是随机数发生器的初始化函数。参数为随机数种子
	return min+(int)(rand() % (max-min));//伪整型随机数发生器
}

//在[min, max]之间生成n个随机整型数组a
void RandIntArray(const int min, const int max, int a[], int n){
	int i;
	time_t tx;	
	srand((unsigned) time(&tx));
	for(i=0;i<n;i++)
		a[i] = min+(int)(rand() % (max-min+1));
}

// 返回从[min,max)之间的一个随机浮点数
double RandDouble(const double min, const double max){
	int i;
	time_t tx;	
	if(fabs(min-max)<1e-6){
		printf("区间相等!");
		return 0.0;
	}
	srand((unsigned) time(&tx));//srand函数是随机数发生器的初始化函数。参数为随机数种子
	return min+rand() / (double)(RAND_MAX/(max-min));//伪浮点随机数发生器
}

//在[min, max]之间生成n个随机浮点数组a
void RandDoubleArray(const double min, const double max, double a[], int n){
	int i;
	time_t tx;
	if(fabs(min-max)<1e-6){//
		printf("区间相等!");
		return;
	}	
	srand((unsigned) time(&tx));
	for(i=0;i<n;i++)
		a[i] = min+rand() / (double)(RAND_MAX/(max-min));
}

//每次调用update函数，相当于时间过了1ms 
void UpdateTime(struct tms *t){
	(*t).milliseconds++; //1ms单位时间加1  
	cnt++; 
	if ((*t).milliseconds==1000){ //计时满1秒进位 
		(*t).milliseconds=0;  
		(*t).seconds++;  
	}  
	if ((*t).seconds==60){ //计时满1分进位 
		(*t).seconds=0;  
		(*t).minutes++;  
	}  
	if ((*t).minutes==60){ //计时满1小时进位
		(*t).minutes=0;  
		(*t).hours++;  
	}  
	if((*t).hours==24)
		(*t).hours=0;  
	Sleep(1);  //Sleep是windows提供的函数，作用是暂停程序，单位毫秒，此处暂停1ms 
}  

//此处输出计时结果，r为回车不换行，一直在同一行更新时间
void DisplayTime(struct tms *t){    	 
	printf("\t%d:",(*t).hours);  
	printf("%d:",(*t).minutes);  
	printf("%d:",(*t).seconds); 
	printf("%d",(*t).milliseconds);
	printf("\t按ESC键退出!\r");
}  

//初始化时间
void InitTime(){
	timec.hours=timec.minutes=timec.seconds=timec.milliseconds=0; 
} 

//定时计时闹钟，从0计时到mseconds时返回字符'm'，按空格键显示分段计时
char TimeClock(int mseconds)  
{ 
	char m;   
	InitTime(); 
	cnt = 0; 
	while(1){ 
		if(kbhit()) //此处检查是否有键盘输入 
		{ 
			m=getch();  
			if(m == '\r')  //1 如果等于回车，那么计时结束，跳出循环 
				break; 
			else if(m == ' '){  //2 如果等于空格，显示此次计时，初始化计时器 
				tmpc = timec; //记录上一段计时器结果 
				InitTime(); 
				printf("\n"); 
			} 
			else if(m == VK_ESCAPE)//3 ESC键，返回ESC
				return m;
			else {//4 其它键 
				printf("输入错误,仅支持输入回车键或者空格或ESC键!\n"); 
			}  
		} 
		UpdateTime(&timec);  //更新计时器 
		if(timec.milliseconds>=mseconds-1)
			return 'm';
		DisplayTime(&timec); //显示计时器时间 
	} 
	return m;
}
//2013-03-11
void RandCharArray(char min, char max, char a[], int n){
	int i;
	char minValue=min, maxValue=max;
	srand((unsigned) time(NULL));
	for(i=0;i<n;i++)
		a[i] = minValue+(char)(rand() % (maxValue-minValue+1));
}
void PrintiArray(int a[], int n){
	int i=0;
	for(i=0;i<n;i++){
		if(i%10==0 && i!=0 )//10个数换行
			printf("\n");
		printf("%5d ", a[i]);//5位，对齐

	}
	printf("\n");
}
void PrintdArray(double a[], int n){
	int i=0;
	for(i=0;i<n;i++){
		if(i%10==0 && i!=0 )//10个数换行
			printf("\n");
		printf("%5.2f ", a[i]);//5位，其中2位小数

	}
	printf("\n");
}
void PrintcArray(char a[], int n){
	int i=0;
	for(i=0;i<n;i++){
		if(i%10==0 && i!=0 )//10个数换行
			printf("\n");
		printf("%c ", a[i]);

	}
	printf("\n");
}
//通用比较函数
 int ICmp(const void *a, const void *b) {
	 /*int *aa=(int *)a,*bb=(int *)b;
	 if(*aa > *bb)return 1; 
	 else if(*aa == *bb)return 0;
	 	else return -1;*/	 
	 return *(int *)a > *(int *)b ? 1 : -1;//可以这样写，代替上面的四行	 
 } 
int CCmp( const void *a , const void *b )
{
	char *aa=(char *)a,*bb=(char *)b;
	if(*aa > *bb)return 1; 
	else if(*aa == *bb )return 0;
		else return -1;
	//return(*(char *)a-*(char *)b);//可以这样写，代替上面的四行	 
}
 int DCmp(const void *a, const void *b) {
	 double *aa=(double *)a,*bb=(double *)b;
	 if(*aa > *bb)return 1; 
	 else if( fabs(*aa - *bb)<1e-6)return 0;
	 	else return -1;
	 //return *(double *)a > *(double *)b ? 1 : -1;//可以这样写，代替上面的四行	 
 }
 int FCmp(const void *a, const void *b) {
	 float *aa=(float *)a,*bb=(float *)b;
	 if(*aa > *bb)return 1; 
	 else if(fabs(*aa - *bb)<1e-6)return 0;
	 	else return -1;
	 //return *(float *)a > *(float *)b ? 1 : -1;//可以这样写，代替上面的四行	 
 }
//通用交换函数
void VSwap(void * vp1, void *vp2, int size){
	char *buffer =(char*)malloc(sizeof(char)*size) ;
	memcpy(buffer, vp1, size);
	memcpy(vp1, vp2, size);
	memcpy(vp2, buffer, size);
	free(buffer);
}