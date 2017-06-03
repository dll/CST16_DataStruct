/*
*�ļ���DSA01.C
*����ļ���ʵ��ͨ������
*���ߣ�������
*����: 2012-09-10
*/

#include "DSA01.h"

void Swap(int *a, int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

void SelectSort(int a[], int n) {
	int i, j, k;
   // �� a �����������������г���С����������������С�
	for ( i = 0;  i< n-1;  ++i ) {
		j = i;   // ѡ��� i ����СԪ��
		for ( k = i+1;  k < n;  ++k )
			if (a[k] < a[j] )  j = k;
			if ( j != i )  Swap(&a[j], &a[i]);
	}		
} // select_sort

void BubbleSort(int a[], int n) {
	int i, j;
	BOOL change;
    // �� a �����������������г���С����������������С�
	for (i=n-1, change=TRUE;  i>1 && change;  --i)
	{  
		change = FALSE;  // change ΪԪ�ؽ��н�����־
		  for (j=1;  j<i;  ++j)
			 if (a[j] > a[j+1]) 
			 {
					Swap(&a[j], &a[j+1]);
					change = TRUE;
			 }
	} // һ��ð��
} // bubble_sort

/////////////////////////////////////////////////
int SelectMin(ElementType e[], int i, int n){ 
	/* ������L.r[i..L.length]��key��С�ļ�¼����� */ 
	ElementType min;
	int j,k;
	k=i; /* ���i��Ϊ��С */ 
	min=e[i]; 
	for(j=i+1; j<n; j++) 
		if(e[j]<min) /* �ҵ���С�� */ 
		{
			k=j;
			min=e[j];
		}
	return k;
}
/* ��ѡ������ */
void DATSelectSort(ElementType e[], int n){
	int i,j;
	ElementType t;
	for(i=0; i<n; i++) { /* ѡ���iС�ļ�¼����������λ */ 
		j=SelectMin(e,i,n); /* ��L.r[i..L.length]��ѡ��key��С�ļ�¼ */
		if(i!=j) { /* ���i����¼���� */ 
			t=e[i];
			e[i]=e[j];
			e[j]=t;
		}
	}
}

/////////////////////////////////////////////////
//ͨ�õ�ѡ�����򣨷��ͱ��˼�룩
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
					j = i;   // ѡ��� i ����СԪ��
					for ( k = i+1;  k < n;  ++k )
						if (Cmp((void*)(aa+k), (void*)(aa+j) )==-1 )
							j = k;
						if ( j != i )
							VSwap((void*)(aa+j), (void*)(aa+i), sizeof(int));
				}
			break;
		case 2:
				for ( i = 0;  i< n-1;  i++ ) {
					j = i;   // ѡ��� i ����СԪ��
					for ( k = i+1;  k < n;  ++k )
						if (Cmp((void*)(ab+k), (void*)(ab+j) )==-1 )
							j = k;
						if ( j != i )
							VSwap((void*)(ab+j), (void*)(ab+i), sizeof(float));
				}
			break;
		case 3:
				for ( i = 0;  i< n-1;  i++ ) {
					j = i;   // ѡ��� i ����СԪ��
					for ( k = i+1;  k < n;  ++k )
						if (Cmp((void*)(ac+k), (void*)(ac+j) )==-1 )
							j = k;
						if ( j != i )
							VSwap((void*)(ac+j), (void*)(ac+i), sizeof(double));
				}
			break;
		case 4:
				for ( i = 0;  i< n-1;  i++ ) {
					j = i;   // ѡ��� i ����СԪ��
					for ( k = i+1;  k < n;  ++k )
						if (Cmp((void*)(ad+k), (void*)(ad+j) )==-1 )
							j = k;
						if ( j != i )
							VSwap((void*)(ad+j), (void*)(ad+i), sizeof(char));
				}
			break;
	}
}
//�𲽽��������õ�...
void DSASelectSort(void* *a, int n, int size, int(*Cmp)(void *, void *)) {
	int  i, j, k;
	//�����ǹؼ������ַ�����Ϊ�������ڴ浥λ��1���ֽڣ�
	//������������size���Ϳ������������ڴ�ʹ�ú͹����ܴ�����߱��������Ч��
	//�Ա�DSASelectSort��DSA_SelectSort���������ɣ��ú����⣡
	char *aa = (char*)a;//!! 
	for ( i = 0;  i< n-1;  i++) {
		j = i;   // ѡ��� i ����СԪ��
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
    // �� a �����������������г���С����������������С�
	for (i=n-1, change=TRUE;  i>1 && change;  --i)
	{  
		change = FALSE;  // change ΪԪ�ؽ��н�����־
		  for (j=0;  j<i;  ++j)
			 if (fcmp((void*)(aa+j),  (void*)(aa+j+1) )==1) 
			 {
					VSwap((void*)(aa+j), (void*)(aa+j+1) , size);
					change = TRUE;
			 }
	} // һ��ð��
} // DSA_bubble_sort

/////////////////////////////////////////////////
//MS��������
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