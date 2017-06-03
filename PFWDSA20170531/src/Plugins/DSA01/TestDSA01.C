/*
*文件：TestDSA01.C
*插件文件，实现通用选择排序的测试文件，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include "DSA01.h"

//const int N=1000;
#define N 1000
#define RANMIN 1
#define RANMAX 10000

char gVersion[20];
char gInterface[20];
//插件信息
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			strcpy(gVersion,"1.0.0");
			strcpy(gInterface,"DSAInterface");
			break;
		case DLL_THREAD_ATTACH:	
		case DLL_THREAD_DETACH:		
		case DLL_PROCESS_DETACH:	
			break;
    }
    return TRUE;
}
char* GetPluginVersion(){
	return gVersion;
}
char* GetPluginInterface(){
	return gInterface;
}
//插件框架的接口

void TestDSABubbleSort(void);
void TestDSASelectSort(void);
void TestDSASort(void);

void DSAInterface(void){
	char s;
	while(1){
		printf("\n\t请输入字母b冒泡 s选择 a通用排序 x退出:");flushall();
		scanf("%c", &s);
		switch(s)
		{
			case 'x':
				return;
			case 'b':
				TestDSABubbleSort();
				break;
			case 's':
				TestDSASelectSort();
				break;
			case 'a':
				TestDSASort();
				break;
			default:
				printf("\t输入字母无效!");		
				break;			
		}
	}
}
void TestDSABubbleSort(void){
	int arr[N];
	clock_t start, finish;
	double duration;
	int i=0;
	RandIntArray(1,N, arr, N);
	for(i=0;i<N;i++){
		if(i%10==0 && i!=0)printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n");
	start = clock();
	DSABubbleSort((void**)arr, N, sizeof(int), ICmp);
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("\nDSABubbleSort RandIntArray[%d] time is %f second\n", N, duration);
	for(i=0;i<N;i++){
		if(i%10==0 && i!=0 )printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\nDSABubbleSort RandIntArray[%d] time is %f second\n", N, duration);
}
void TestDSASelectSort(void){
	int arr[N];
	clock_t start, finish;
	double duration;
	int i=0;
	RandIntArray(1,N, arr, N);
	for(i=0;i<N;i++){
		if(i%10==0 && i!=0)printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n");
	start = clock();
	DSASelectSort((void**)arr, N, sizeof(int), ICmp);
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("DSASelectSort RandIntArray[%d] time is %f second\n", N, duration);
	for(i=0;i<N;i++){
		if(i%10==0 && i!=0 )printf("\n");
		printf("%5d ", arr[i]);
	}
}
void TestDSASort(void){
	long i;
	FILE *pf;//文件对象变量
	int* tArray, *sArray;
  
	//_int64 dTime, dTime1, dTime2;
	unsigned dTime, dTime1, dTime2;
	LARGE_INTEGER m_nFreq;
    LARGE_INTEGER m_nBeginTime;
    LARGE_INTEGER nEndTime;


	int* iArray = (int*)malloc(sizeof(int)*N);
	double* dArray = (double*)malloc(sizeof(double)*N);
	char* cArray = (char*)malloc(sizeof(char)*N);

	RandIntArray(RANMIN, RANMAX, iArray, N);

	printf("SelectSort(iArray, N)排序前...\n");
	PrintiArray(iArray,N);
	QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
    QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
	//SelectSort(iArray, N);
	//DSA_SelectSort((void**)iArray, N, "int", ICmp);
	DSASelectSort((void**)iArray, N, sizeof(int), ICmp);
	QueryPerformanceCounter(&nEndTime);
    dTime = (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
	printf("SelectSort(iArray, N)排序后...\n");
	PrintiArray(iArray,N);
	printf("选择排序耗时%d 毫秒！\n",dTime);

	//////////////////////////////////////////////
	system("PAUSE");//暂停
	system("CLS");//清屏CLean Screen=>CLS
	printf("DSA_SelectSort((void**)dArray, N, \"double\", DCmp)排序前...\n");
	RandDoubleArray(3.14, 96.54, dArray, N);
	PrintdArray(dArray,N);
	//DSA_SelectSort((void**)dArray, N, "double", DCmp);
	DSASelectSort((void**)dArray, N, sizeof(double), DCmp);
	printf("DSA_SelectSort((void**)dArray, N, \"double\", DCmp)排序后...\n");
	PrintdArray(dArray,N);

	system("PAUSE");
	system("CLS");
	printf("DSA_SelectSort(cArray, N);排序前...\n");
	RandCharArray('a', 'z', cArray, N);
	PrintcArray(cArray,N);
	//DSA_SelectSort((void**)cArray, N, "char", CCmp);
	DSASelectSort((void**)cArray, N, sizeof(char), CCmp);
	printf("DSA_SelectSort(cArray, N);排序后...\n");
	PrintcArray(cArray,N);
	system("PAUSE");
	system("CLS");
	pf=fopen("Temp\\DSA011.tmp", "w");//打开文件
	//i运行到小于其最大值时范围内：0xffffffffUL(16) 4294967295(10) 约42亿，
	//排序可以计算到1,10,100,1000,1000,10000,10万,到100万个整数排序时就不能等了
	//通过对比可以发现c语言标准库里的快速排序函数qsort在0.062秒排序10万整数，
	//而我们写的DSA_SelectSort函数则要111.328秒。其中，选择排序为大O（n2） 而快速排序
	//则为O（nlogn），算法决定一切，决定你的选择！
	fprintf(pf, "%8s %8s %8s %8s\n", "数据规模", "选择排序", "冒泡排序", "快速排序");
	for(i=1;i<ULONG_MAX/10000;i*=10){

		tArray=(int*)malloc(sizeof(int)*i);
		sArray=(int*)malloc(sizeof(int)*i);
		RandIntArray(RANMIN, RANMAX, tArray, i);
		memcpy(sArray, tArray, sizeof(int)*i);

		QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
		DSASelectSort((void**)sArray, i, sizeof(int), ICmp);
		QueryPerformanceCounter(&nEndTime);
		dTime = (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
		printf("%8d 整型数选择排序耗时 %8d 毫秒！\n", i, dTime);

		memcpy(sArray, tArray, sizeof(int)*i);

		QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
		DSABubbleSort((void**)sArray, i, sizeof(int), ICmp);
		QueryPerformanceCounter(&nEndTime);
		dTime1 = (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
		printf("%8d 整型数冒泡排序耗时 %8d 毫秒！\n", i, dTime1);

		memcpy(sArray, tArray, sizeof(int)*i);	
		QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
		//qsort(sArray, i ,sizeof(int), ICmp);
		DSAQuickSort(sArray, i ,sizeof(int), ICmp);
		QueryPerformanceCounter(&nEndTime);
		dTime2 = (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
		printf("%8d 整型数快速排序耗时 %8d 毫秒！\n\n", i, dTime2);
		
		fprintf(pf, "%8d %8d %8d %8d\n", i, dTime, dTime1, dTime2);
		free(tArray);//释放由malloc分配的堆内存空间
		free(sArray);
	}
	fclose(pf);//关闭文件
	system("Temp\\DSA011.tmp");

	free(iArray);
	free(dArray);
	free(cArray);
}