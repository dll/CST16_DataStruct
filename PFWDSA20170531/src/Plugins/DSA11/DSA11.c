//PFWDSA plugin source file DSA11.c
#include "DSA11.h"

//插入排序
void CreateSortList ( SortList *L ){
	int i = 0;   ElemType x;

	printf ( "\t请输入第[%d]个排序数据,[-1]结束: ", i+1 );
	scanf ( "%d", &x );

	while ( x != -1 )
	{
		if ( i > MAXSIZE )
		{
			--i;   break;
		}

		L->r[++i] = x;
		printf ( "\t请输入第[%d]个排序数据,[-1]结束: ", i+1 );
		scanf ( "%d", &x );
	} 

	L->length = i;

}

void PrintSortListB ( SortList *L )
{
	int i;

	printf("\t排序前\n");
	for ( i=1; i <= L->length; i++ )
		printf ( "\t%5d", i );

	printf ( "\n" );

	for ( i=1; i <= L->length; i++ )
		printf ( "\t%5d", L->r[i] );

	printf ( "\n" );
}
void PrintSortListA ( SortList *L )
{
	int i;

	printf("\t排序后\n");
	for ( i=1; i <= L->length; i++ )
		printf ( "\t%5d", i );

	printf ( "\n" );

	for ( i=1; i <= L->length; i++ )
		printf ( "\t%5d", L->r[i] );

	printf ( "\n" );
}
//直接插入排序算法
void InsertSort ( SortList *L )
{
	int i,  j;

	for ( i=2; i <= L->length; i++ ){
		L->r[0]  =  L->r[i];//将待插入记录暂时存入监视哨位置

		for ( j=i-1; L->r[0] < L->r[j]; j-- )
			L->r[j+1] = L->r[j];//比待插入记录关键字大的记录后移
		
		L->r[j+1] = L->r[0];//插入空位置
	}

}
//折半插入排序
void BinInsertSort ( SortList *L ){
	int i,  j,  low,  high,  mid;

	for ( i=2; i < L->length; ++i )	{
		L->r[0] = L->r[i];
		low = 1;   high = i - 1;

		while ( low <= high ){
			mid  = ( low + high ) / 2;

			if ( L->r[0] < L->r[mid] )
				high = mid - 1;
			else
				low = mid + 1;
		}

		for ( j = i-1; j >= high+1;  --j )
			L->r[j+1] = L->r[j];
		
		L->r[high+1] = L->r[0];
	}
}
//2路插入排序
void TwoInsertSort ( SortList *L ){
	int i,  j,  final,  first,  low,  high,  mid;

	ElemType * d;

	d = ( ElemType * ) malloc ( sizeof ( ElemType ) * ( L->length + 1 ) );

	first = L->length + 1 ;   final = 1;
	d[1] = L->r[1];

	for ( i=2; i <= L->length; i++ )
		if ( L->r[i] >= d[1] )
		{
			low = 1;   high = final;

			while ( low <= high )
			{
				mid = ( low + high ) / 2;

				if ( L->r[i] < d[mid] )
					high = mid - 1;
				else
					low = mid + 1;
			}

			for ( j = final; j >= low; --j )
				d[j+1] = d[j];

			d[low] = L->r[i];
			final++;
		}
		else{
			low = first;  high = L->length;

			while ( low <= high )
			{
				mid = ( low + high ) / 2;

				if ( L->r[i] < d[mid] )
					high = mid - 1;
				else
					low = mid + 1;
			}

			for ( j = first ; j <= high; ++j )
				d[j-1] = d[j];

			d[high] = L->r[i];
			first--;

		}

	i = 1;

	for ( j = first; j <= L->length; j++ )
		L->r[i++] = d[j];

	for ( j = 1; j <= final; j++ )
		L->r[i++] = d[j];

}
//表插入排序
void CreateSLList( SLinkList *SL ){
	int i = 0;  ElemType x;

	printf ( "\t请输入第[%d]个排序数据,[-1]结束: ", i+1 );
	scanf ( "%d", &x );

	while ( x != -1){
		if ( i > MAXSIZE )
		{
			--i;   break;
		}

		SL->r[++i].key = x;
		printf ( "\t请输入第[%d]个排序数据,[-1]结束: ", i+1 );
		scanf ( "%d", &x );
	}

	SL->length = i;
}

void PrintStaticLnkList ( SLinkList SL ){
	int i;

	for ( i=1; i <= SL.length; i++ )
		printf ( "%5d", i );

	printf ( "\n" );

	for ( i=1; i <= SL.length; i++ )
		printf ( "%5d", SL.r[i].key );

	printf ( "\n\n" );
}

//静态链表插入排序算法
void SLInsertSort ( SLinkList *SL ){
	int i, j, k;

	SL->r[0].key = MAXSIZE;
	SL->r[0].next = 1;
	SL->r[1].next = 0;

	for ( i=2; i <= SL->length; ++i )
	{
		for ( j=0, k = SL->r[0].next;  SL->r[k].key <= SL->r[i].key;  j=k, k = SL->r[k].next );
		SL->r[j].next = i;//结点i插入结点j和结点k之间
		SL->r[i].next = k;
	}

}
//静态链表调整插入排序算法
void AdjustSLLink ( SLinkList *SL ){
	int p, i, q;   SLNode t;

	p = SL->r[0].next;

	for ( i=1; i < SL->length; ++i ){
		while ( p < i )
			p = SL->r[p].next;

		q = SL->r[p].next;

		if ( p != i ){
			t = SL->r[p];
			SL->r[p] = SL->r[i];
			SL->r[i] = t;
			SL->r[i].next = p;
		}

		p = q;
	}
}
//希尔插入排序算法
void ShellInsertSort ( SortList *L,  int d[],  int t )
{
	int i, j, k;

	for ( k=0; k<t; k++ )
		for ( i=d[k]+1; i <= L->length; ++i )
			if ( L->r[i] < L->r[i-d[k]] )
			{
				L->r[0] = L->r[i];

				for ( j = i-d[k];   j>0  &&  L->r[0] < L->r[j];   j-=d[k] )
					L->r[j+d[k]] = L->r[j];

				L->r[j+d[k]] = L->r[0];
			}

}
//交换排序
//冒泡排序算法
void BubbleSort ( SortList *L ){
	int i, j;   ElemType t;

	for ( i=1; i < L->length; i++ )
		for ( j=1; j <= L->length; j++ )
			if ( L->r[j] > L->r[j+1] )
			{
				t = L->r[j];
				L->r[j] = L->r[j+1];
				L->r[j+1] = t;
			}

}
//改进冒泡排序算法
void BetterBubbleSort ( SortList *L ){
	int i, j;  int flag = 1;  ElemType t;

	for ( i=1;   flag  &&  i < L->length;   i++ )
		for ( flag = 0,  j=1;   j <= L->length;   j++ )
			if ( L->r[j] > L->r[j+1] )
			{
				t = L->r[j];
				L->r[j] = L->r[j+1];
				L->r[j+1] = t;
				flag = 1;
			}

}
//快速排序
void HoareSort ( SortList *L, int low, int high ){
	int i, j;

	if ( low < high )
	{
		i = low;   j = high;

		L->r[0] = L->r[i];

		while ( i < j )
		{
			while ( i < j  &&  L->r[j] >= L->r[0] )
				j--;

			L->r[i] = L->r[j];

			while ( i < j  &&  L->r[i] <= L->r[0] )
				i++;

			L->r[j] = L->r[i];
		}

		L->r[i] = L->r[0];

		HoareSort ( L, low, i-1 );
		HoareSort ( L, i+1, high );
	}
}
//选择排序
//简单选择排序
void SimpleSelectSort ( SortList *L ){
	int i, j;   ElemType t;

	for ( i=1;  i < L->length;  i++ )
		for ( j = i+1;  j <= L->length;  j++ )
			if ( L->r[i] > L->r[j] )
			{
				t = L->r[i];
				L->r[i] = L->r[j];
				L->r[j] = t;
			}
}
void BetterSelectSort ( SortList *L )
{
	int i, j, k;   ElemType t;

	for ( i=1;  i < L->length;  i++ )
		for ( k=1,  j = i+1;   j <= L->length;   j++ )
			// if ( L->r[k].key > L->r[j].key )
				// k = j;
			if ( k != i ){
				t = L->r[k];
				L->r[k] = L->r[i];
				L->r[j] = t;
			}
}

//树形选择排序
SortList CreateInitTree ( SortList *L ){
	int i;  SortList Q;

	Q.length  =  2 * L->length - 1;

	for ( i = L->length;  i <= Q.length;  i++ )
		Q.r[i]  =  L->r[i-L->length+1];

	for ( i = L->length-1;  i >= 1;  i-- )
		Q.r[i]  =   ( Q.r[2*i] <= Q.r[2*i+1] )  ?  Q.r[2*i]  :  Q.r[2*i+1];

	return Q;
}

ElemType MaxTree ( SortList *L )
{
	int i;  ElemType m = L->r[1];

	for ( i=1;  i <= L->length;  i++ )
		if ( m < L->r[i] )
			m = L->r[i];

	return m;
}
void TreeSort ( SortList *L )
{
	int i, j;  SortList Q;

	Q = CreateInitTree ( L );

	L->r[1] = Q.r[1];

	for ( i=2;  i <= L->length;  i++ )
	{
		j = 1;

		while ( j < L->length )
			j   =   ( Q.r[2*j] <= Q.r[2*j+1] )  ?  2*j  :  2*j+1;

		Q.r[j] = MaxTree ( L );

		while ( j > 1 )
		{
			j = j / 2;
			Q.r[j]   =   ( Q.r[2*j] <= Q.r[2*j+1] )  ?  Q.r[2*j]  :  Q.r[2*j+1];
		}

		L->r[i] = Q.r[1];
	}
}

//堆排序
//调整建堆算法
void AdjustSortTree ( SortList *L, int n, int k )
{
	int i, j;  ElemType t;

	i = k;  j = 2 * i;

	L->r[0] = L->r[i];

	while ( j<= n )	{
		if ( j < n  &&  L->r[j+1] > L->r[j] )
			j = j + 1;

		if ( L->r[i] > L->r[j])
			break;

		L->r[i] = L->r[j];
		i = j;   j = 2 * i;
	}

	L->r[i] = L->r[0];
}
//堆排序算法
void HeapSort ( SortList *L )
{
	int i;  ElemType t;

	for ( i = L->length / 2;  i >= 1;  i-- )
		AdjustSortTree ( L, L->length, i );

	for ( i = L->length;  i >= 2;  i-- ){
		t = L->r[i];
		L->r[i] = L->r[1];
		L->r[1] = t;

		AdjustSortTree ( L, i-1, 1 );
	}
}
//归并排序
//递归的归并排序
//有序表合并排序算法
void Merge ( SortList *SR, SortList *TR, int i, int m, int n ){
	int j2 = m + 1, j1 = i, k = i;

	while ( j1 <= m  &&  j2 <= n )
		if ( SR->r[j1] <= SR->r[j2] )
			TR->r[k++] = SR->r[j1++];
		else
			TR->r[k++] = SR->r[j2++];

	while( j1 <= m )
		TR->r[k++] = SR->r[j1++];
	
	while ( j2 <= n )
		TR->r[k++] = SR->r[j2++];

	for ( k=i;  k <= n;  k++ )
		SR->r[k] = TR->r[k];
}
//2路归并排序算法
void MergeSort ( SortList *SR, SortList *TR, int s, int t ){
	int m;

	if ( s == t)
		TR->r[s] = SR->r[s];
	else
	{
		m  =  ( s + t ) / 2;
		MergeSort ( SR, TR, s, m );
		MergeSort ( SR, TR, m+1, t );
		Merge ( SR, TR, s, m, t );
	}
}

//非递归Non-Recursive
void NRecurMSort ( SortList *Q, int b, int d ){
	int i, j;  int k = 0;  ElemType *t;

	t = ( ElemType * ) malloc ( sizeof ( ElemType ) * ( 2 * d ) );
	i = b;   j  =  b + d;

	while ( i < b+d  && j <= Q->length  &&  j < b+2*d )
		if ( Q->r[i] < Q->r[j] )
			t[k++] = Q->r[i++];
		else
			t[k++] = Q->r[j++];

	while ( i < b+d )
		t[k++] = Q->r[j++];

	for ( i=b; i < b+k; i++ )
		Q->r[i] = t[i-b];

}
void NRecurMergeSort ( SortList *Q ){
	int i, j;

	for ( i=1;  i <= Q->length;  i*=2 )	{
		j = 1;

		while ( j < Q->length )	{
			NRecurMSort ( Q, j, i );
			j += 2*i;
		}

	}

}
//计数排序
void CountSort ( SortList *L ){
	SortList Q;  int i, j, *c;

	c = ( int * ) malloc ( ( L->length + 1 ) * sizeof ( int ) );
	Q = *L;

	for ( i=1;  i <= L->length;  i++ )
		c[i] = 1;

	for ( i=1;  i < L->length;  i++ )
		for ( j = i+1;  j <= L->length;  j++ )
			if ( Q.r[i] > Q.r[j] )
				c[i]++;
			else
				c[j]++;

	for ( i=1;  i <= L->length;  i++ )
		L->r[c[i]] = Q.r[i];
}
//基数排序

SLink * CreateSLink ( int n ){
	SLink *s, *L;
	int i;

	L = NULL;
	for ( i=0; i<n; i++ )	{
		s = ( SLink * ) malloc ( sizeof ( SLink ) );
		printf ( "\t请输入第[%d/%d]个排序数据: ", i+1, n );
		scanf ( "%d", &s->key );
		s->next = L;

		L=s;
	}
	return L;
}

void PrintLnkList ( SLink *L ){
	SLink *p;

	p = L;
	while ( p != NULL )	{
		printf ( "\t%3d", p->key );
		p = p->next;
	}
	printf ( "\n" );
}

SLink *RadixSort ( SLink *L ){
	int i, k;  int w=1, flag=1;
	SLink *front[10], *rear[10];

	while ( flag != 0 ){
		for ( i=0; i<10; i++ )
			front[i] = NULL;

		flag = 0;
		while ( L != NULL )	{
			k = L->key / w % 10;

			if ( k != 0 )
				flag = 1;

			if ( front[k] == NULL )
				front[k] = rear[k] = L;
			else{
				rear[k]->next = L;
				rear[k] = L;
			}

			L = L->next;
		}
		L = NULL;
		for ( i=9;  i >= 0; i-- )
			if ( front[i] != NULL )	{
				rear[i]->next = L;
				L = front[i];
			}
		w *= 10;
	}
	return L;
}
void DestroyLnkList ( SLink *L ){
	SLink *p;
	while ( L != NULL )	{
		p=L;
		L=L->next;
		free(p);
	}
}