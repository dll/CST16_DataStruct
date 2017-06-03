/*
*文件：DSA01.C
*插件文件，实现通用排序
*作者：刘东良
*日期: 2012-09-10
*/

#include "DSA01.h"

void Swap(int *a, int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

void SelectSort(int a[], int n) {
	int i, j, k;
   // 将 a 中整数序列重新排列成自小至大有序的整数序列。
	for ( i = 0;  i< n-1;  ++i ) {
		j = i;   // 选择第 i 个最小元素
		for ( k = i+1;  k < n;  ++k )
			if (a[k] < a[j] )  j = k;
			if ( j != i )  Swap(&a[j], &a[i]);
	}		
} // select_sort

void BubbleSort(int a[], int n) {
	int i, j;
	BOOL change;
    // 将 a 中整数序列重新排列成自小至大有序的整数序列。
	for (i=n-1, change=TRUE;  i>1 && change;  --i)
	{  
		change = FALSE;  // change 为元素进行交换标志
		  for (j=1;  j<i;  ++j)
			 if (a[j] > a[j+1]) 
			 {
					Swap(&a[j], &a[j+1]);
					change = TRUE;
			 }
	} // 一趟冒泡
} // bubble_sort

/////////////////////////////////////////////////
int SelectMin(ElementType e[], int i, int n){ 
	/* 返回在L.r[i..L.length]中key最小的记录的序号 */ 
	ElementType min;
	int j,k;
	k=i; /* 设第i个为最小 */ 
	min=e[i]; 
	for(j=i+1; j<n; j++) 
		if(e[j]<min) /* 找到更小的 */ 
		{
			k=j;
			min=e[j];
		}
	return k;
}
/* 简单选择排序 */
void DATSelectSort(ElementType e[], int n){
	int i,j;
	ElementType t;
	for(i=0; i<n; i++) { /* 选择第i小的记录，并交换到位 */ 
		j=SelectMin(e,i,n); /* 在L.r[i..L.length]中选择key最小的记录 */
		if(i!=j) { /* 与第i个记录交换 */ 
			t=e[i];
			e[i]=e[j];
			e[j]=t;
		}
	}
}

/////////////////////////////////////////////////
//通用的选择排序（泛型编程思想）
void DSA_SelectSort(void* *a, int n, char * typeName, int(*Cmp)(void *, void *)) {
	int    i, j, k, type;
	int    *aa = (int*)a;
	float  *ab = (float*)a;
	double *ac = (double*)a;
	char   *ad = (char*)a;

	if(strcmp("int",typeName) == 0)type=1;
	else if(strcmp("float",typeName)  == 0) type=2;
		else if(strcmp("double",typeName)  == 0) type=3;
			else type=4;

	switch(type){
		case 1:
				for ( i = 0;  i< n-1;  i++ ) {
					j = i;   // 选择第 i 个最小元素
					for ( k = i+1;  k < n;  ++k )
						if (Cmp((void*)(aa+k), (void*)(aa+j) )==-1 )
							j = k;
						if ( j != i )
							VSwap((void*)(aa+j), (void*)(aa+i), sizeof(int));
				}
			break;
		case 2:
				for ( i = 0;  i< n-1;  i++ ) {
					j = i;   // 选择第 i 个最小元素
					for ( k = i+1;  k < n;  ++k )
						if (Cmp((void*)(ab+k), (void*)(ab+j) )==-1 )
							j = k;
						if ( j != i )
							VSwap((void*)(ab+j), (void*)(ab+i), sizeof(float));
				}
			break;
		case 3:
				for ( i = 0;  i< n-1;  i++ ) {
					j = i;   // 选择第 i 个最小元素
					for ( k = i+1;  k < n;  ++k )
						if (Cmp((void*)(ac+k), (void*)(ac+j) )==-1 )
							j = k;
						if ( j != i )
							VSwap((void*)(ac+j), (void*)(ac+i), sizeof(double));
				}
			break;
		case 4:
				for ( i = 0;  i< n-1;  i++ ) {
					j = i;   // 选择第 i 个最小元素
					for ( k = i+1;  k < n;  ++k )
						if (Cmp((void*)(ad+k), (void*)(ad+j) )==-1 )
							j = k;
						if ( j != i )
							VSwap((void*)(ad+j), (void*)(ad+i), sizeof(char));
				}
			break;
	}
}
//逐步进化，更好的...
void DSASelectSort(void* *a, int n, int size, int(*Cmp)(void *, void *)) {
	int  i, j, k;
	//这里是关键：将字符型作为基本的内存单位：1个字节，
	//其它类型则是size倍就可以啦！理解内存使用和管理能大大地提高编程质量和效率
	//对比DSASelectSort与DSA_SelectSort两个函数吧，好好理解！
	char *aa = (char*)a;//!! 
	for ( i = 0;  i< n-1;  i++) {
		j = i;   // 选择第 i 个最小元素
		for ( k = i+1;  k < n;  ++k )
			if (Cmp((void*)(aa+k*size), (void*)(aa+j*size) )==-1 )
				j = k;
		if ( j != i )
			VSwap((void*)(aa+j*size), (void*)(aa+i*size), size);
	}
		
} // DSA_select_sort
void DSABubbleSort(void* *a, int n, int size, 
					int(*fcmp)(void *, void *)) {
	int i, j;
	BOOL change;
	int *aa = (int*)a;
    // 将 a 中整数序列重新排列成自小至大有序的整数序列。
	for (i=n-1, change=TRUE;  i>1 && change;  --i)
	{  
		change = FALSE;  // change 为元素进行交换标志
		  for (j=0;  j<i;  ++j)
			 if (fcmp((void*)(aa+j),  (void*)(aa+j+1) )==1) 
			 {
					VSwap((void*)(aa+j), (void*)(aa+j+1) , size);
					change = TRUE;
			 }
	} // 一趟冒泡
} // DSA_bubble_sort

/////////////////////////////////////////////////
//MS快速排序
static int Partition(void* arr, int(*cmp)(void*, void*), int left, int right, int size)  
{  
	char* tmp = (char*)malloc(size);  
	memcpy(tmp, (char*)arr + left * size, size);  
	while (left < right)  
	{  
		while (left < right && cmp((char*)arr + right * size, (char*)tmp) >= 0)
			--right;  
		memcpy((char*)arr + left * size, (char*)arr + right * size, size);  
		while (left < right && cmp((char*)arr + left * size, (char*)tmp) <= 0)
			++left;  
		memcpy((char*)arr + right * size, (char*)arr + left * size, size);  
	}  
	memcpy((char*)arr + right * size, (char*)tmp, size);  
	return right;  
}  
  
static void QSort(void* arr, int(*cmp)(void*, void*), int left, int right, int size)  
{ 
	int part;
	if (right <= left)  
		return;  
	part = Partition(arr, cmp, left, right, size);  
	QSort(arr, cmp, left, part - 1, size);  
	QSort(arr, cmp, part + 1, right, size);  
}  
  
void DSAQuickSort(void* arr, int n, int size, int(*cmp)(void*, void*))  
{  
	QSort(arr, cmp, 0, n - 1, size);  
}  
