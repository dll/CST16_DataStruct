#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<memory.h>
#include<assert.h>

#define DEBUG_SORT

#ifdef DEBUG_SORT
#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

struct IndexNode {
	int index;
	int key;
	IndexNode* next;
};
// 冲突发生时，继续进行探查的方式
enum Conflict_Resolution
{
	Conflict_Resolution_Linear		= 0,	// 线性探查
	Conflict_Resolution_Quadratic	= 1,	// 线性探查
	Conflict_Resolution_Double_Hash	= 2,	// 双重散列探查
};

// hash 函数
typedef int (*Hash_Function)(int key, int hashTableLength);
struct Hash_Node{
	int key;
	Hash_Node* next;
};

struct BSTNode {
	int key;
	BSTNode* leftChild;
	BSTNode* rightChild;
};

typedef BSTNode* BSTree;
// 定义 B 树的最小度数
// 每个节点中关键字的最大数目 BTree_N = 2 * BTree_T - 1
#define	BTree_T		2
#define BTree_N		(BTree_T * 2 - 1)

struct BTNode {
	int	keynum;						// 结点中关键字的个数，keynum <= BTree_N
	int key[BTree_N];				// 关键字向量为key[0..keynum - 1]
	BTNode* child[BTree_T * 2];		// 孩子指针向量为child[0..keynum]
	bool isLeaf;					// 是否是叶子节点的标志
};

typedef BTNode* BTree;				// B树的类型

enum RBColor{
	RB_Red,
	RB_Black,
};

struct RBNode 
{
	RBColor color;
	int key;
	RBNode* leftChild;
	RBNode* rightChild;
	RBNode* parent;
};

typedef RBNode* RBTree;

RBNode* RBTree_nil();

// 直接插入排序
//
void insert_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, j, temp;
	for (i = 1; i < length; ++i) {
		temp = array[i];
		j = i - 1;
		
		while (j >= 0 && temp < array[j]) {
			array[j + 1] = array[j];
			--j;
		}
		
		array[j + 1] = temp;
	}
}

// 希尔排序
//
void shell_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, j , temp;
	int increment = length;
	
	do {
		increment = increment / 3 + 1;
		
		// 希尔排序中的一趟排序，increment 为当前增量
		// 将 [increment, length - 1] 之间的记录分别插入各组当前的有序区
		for (i = increment; i < length; ++i) {
			temp = array[i];
			j = i - increment;
			
			while (j >= 0 && temp < array[j]) {
				array[j + increment] = array[j];
				j -= increment;
			}
			
			array[j + increment] = temp;
		}
	} while (increment > 1);
}

// 冒泡排序
//
void bubble_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, j, temp;
	bool exchange;
	
	for (i = 1; i < length; ++i) {
		exchange = false;
		
		for (j = length - 1; j >= i; --j) {
			if (array[j] < array[j - 1]) {
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				
				exchange = true;
			}
		}
		
		if (!exchange) {
			break;
		}
	}
}

// 冒泡排序改进版
//
void bubble_sort_opt(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, j, temp;
	bool exchange;
	int lastExchange = 1;
	
	for (i = 1; i < length;) {
		exchange = false;
		
		for (j = length - 1; j >= i; --j) {
			if (array[j] < array[j - 1]) {
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				
				lastExchange = j;
				exchange = true;
			}
		}
		
		if (!exchange) {
			break;
		}
		
		i = lastExchange + 1;
	}
}


// 对 [low, high] 做划分，并返回基准记录的位置
int quick_partition(int* array, int low, int high)
{
	assert(array && low >= 0 && low <= high);
	
	int pivot = array[low]; // 用区间的第 1 个记录作为基准
	
	while (low < high) {
		while (low < high && array[high] >= pivot) {
			--high;
		}
		
		if (low < high) {
			array[low++] = array[high];
		}
		
		while (low < high && array[low] <= pivot) {
			++low;
		}
		
		if (low < high) {
			array[high--] = array[low];
		}
	}
	
	array[low] = pivot;
	
	return low;
}

void quick_sort_impl(int* array, int low, int high)
{
	if (low < high) {
		int pivotPos = quick_partition(array, low, high);
		
		quick_sort_impl(array, low, pivotPos - 1);
		quick_sort_impl(array, pivotPos + 1, high);
	}
}

// 快速排序
//
void quick_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	quick_sort_impl( array, 0, length - 1);
}


// 直接选择排序
//
void selection_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, j, k, temp;
	
	for (i = 0; i < length - 1; ++i) {
		k = i;
		
		for (j = i + 1; j < length; ++j) {
			if (array[j] < array[k]) {
				k = j;
			}
		}
		
		if (k != i) {
			temp = array[i];
			array[i] = array[k];
			array[k] = temp;
		}
	}
}


// 筛选法调整堆，除 [low] 之外，[low] 的两个孩子均已是大根堆
void adjust_heap(int* heap, int low, int high)
{
	assert(heap);
	
#if 1	// 循环实现
	
	int i = low;
	int j = 2 * i;
	int temp = heap[i];
	
	while (j <= high) {
		// 若有两个孩子，j 为孩子中大的那个的下标
		if (j < high && heap[j] < heap[j + 1]) {
			j = j + 1;
		}
		
		// 已是堆
		if (temp >= heap[j]) {
			break;
		}
		
		// 继续筛选
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * i;
		}
	}
	
	heap[i] = temp;
	
#else	// 递归实现
	
	int i = low;
	int j = 2 * i;
	int temp = heap[i];
	
	if (j >= high) {
		return;
	}
	
	// 若有两个孩子，j 为孩子中大的那个的下标
	if (j < high && heap[j + 1] > heap[j]) {
		j = j + 1;
	}
	
	// 已经为堆，无需调整
	if (heap[low] >= heap[j]) {
		return;
	}
	
	heap[i] = heap[j];
	heap[j] = temp;
	
	// 调整之后，[j, high] 可能不满足堆了，需继续调整
	adjust_heap(heap, j, high);
	
#endif
}

// 只有一个结点的树是堆，而在完全二叉树中，所有序号 i > n/2 的结点都是叶子，
// 因此以这些结点为根的子树均已是堆。这样，我们只需依次将以序号为
// n/2, n/2 - 1, …, 0 的结点作为根的子树都调整为堆即可。
void build_heap(int* heap, int length)
{
	assert(heap && length >= 0);
	
	int i;
	
	for(i = length / 2; i >= 0; --i) {
		adjust_heap(heap, i, length - 1);
	}
}


// 堆排序
//
void heap_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, temp;
	
	// 将 [0, length - 1] 建成初始堆
	build_heap(array, length);
	
	// 对当前无序区 [0, i - 1] 进行堆排序，共做 length - 1 趟。
	for(i = length - 1; i > 0; --i) {
		// 将堆顶和堆中最后一个记录交换
		temp = array[0];
		array[0] = array[i];
		array[i]= temp;
		
		// 将 [0, i - 1] 重新调整为堆，仅有 [0] 可能违反堆性质
		adjust_heap(array, 0, i - 1);
	}
}


void merge(int* array, int low, int mid, int high)
{
	assert(array && low >= 0 && low <= mid && mid <= high);
	
	int* temp = (int*)malloc((high - low + 1) * sizeof(int));
	if (!temp) {
		printf("Error:out of memory!");
		return;
	}
	
	int i = low;
	int j = mid + 1;
	int index = 0;
	
	while (i <= mid && j <= high) {
		if (array[i] <= array[j]) {
			temp[index++] = array[i++];
		}
		else {
			temp[index++] = array[j++];
		}
	}
	
	while (i <= mid) {
		temp[index++] = array[i++];
	}
	
	while (j <= high) {
		temp[index++] = array[j++];
	}
	
	memcpy((void*)(array + low), (void*)temp, (high - low + 1) * sizeof(int)) ;
	
	free(temp);
}

// 对 [0, length - 1] 做一趟归并长度为 n  的归并排序
void merge_pass(int* array, int length, int n)
{
	assert(array && length >= 1 && n >= 1);
	
	int i;
	int sortLength = 2 * n;
	
	// 归并长度为 n 的两个相邻子序列
	for(i = 0; i + sortLength - 1 < length; i = i + sortLength) {
		merge(array, i, i + n - 1, i + sortLength - 1);
	}
	
	// 若 i + n - 1 < length - 1，则剩余一个子文件轮空，无须归并。
	// 尚有两个子序列，其中后一个长度小于 n, 归并最后两个子序列。
	if (length - 1 > i + n - 1) {
		merge(array, i, i + n - 1, length - 1);
	}
}

// 用分治法自下向上进行二路归并排序
//
void merge_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int n;
	
	for(n = 1; n < length; n = (n << 1)) {
		merge_pass(array, length, n);
	}
}


void merge_sort_dc_impl(int* array, int low, int high)
{
	assert(array && low >= 0);
	
	int mid;
	if (low < high) {
		mid = (low + high) >> 1;
		
		merge_sort_dc_impl(array, low, mid);
		merge_sort_dc_impl(array, mid + 1, high);
		
		merge(array, low, mid, high);
	}
}

// 用分治法自上向下进行排序
void merge_sort_dc(int* array, int length)
{
	assert(array && length >= 0);
	
	merge_sort_dc_impl(array, 0, length - 1);
}

// array 中记录的值必须界于范围 [0, k] 之间。
//
void counting_sort(int* array, int length, int k)
{
	int* temp = NULL;	// a copy of array.
	int* counts = NULL;	// for counting.
	int i;
	
	temp = (int*)malloc(sizeof(int) * length);
	if (!temp) {
		printf("Error: out of memory!\n");
		return;
	}
	
	counts = (int*)calloc(sizeof(int), k + 1);
	if (!counts) {
		printf("Error: out of memory!\n");
		
		if (temp) {
			free(temp);
		}
		return;
	}
	
	memcpy(temp, array, sizeof(int) * length);
	
	// 计数
	for (i = 0; i < length; ++i) {
		++counts[temp[i]];
	}
	
	// 确定顺序
	for (i = 1; i <= k; ++i) {
		counts[i] += counts[i - 1];
	}
	
	// 排序
	for (i = 0; i < length; ++i) {
		array[counts[temp[i]] - 1] = temp[i];
		--counts[temp[i]];
	}
	
	if (temp) {
		free(temp);
	}
	
	if (counts) {
		free(counts);
	}
}

// 箱/桶排序和基数排序：以空间换时间
//
struct bucket_node {
	int key;
	bucket_node* next;
};

// 取得数组中最大数的位数
int get_max_digital_count(int* array, int length)
{
	assert(array && length > 0);
	
	int i = 0;
	int max = array[0];
	int maxDigitalCount = 1;
	
	for (i = 1; i < length; i++) {
		if (max < array[i]) {
			max = array[i];
		}
	}
	
	while ((max / 10) > 0) {
		max %= 10;
		++maxDigitalCount;
	}
	
	return maxDigitalCount;
}

// 取得数 num 中从低到高第 n 位上的数字
int get_ditital_at(int num, int n)
{
	while (--n > 0) {
		num /= 10;
	}
	
	return (num % 10);
}

// 箱/桶排序
//
void bucket_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	if (length <= 1) {
		return;
	}
	
	int i, index;
	bucket_node* temp = NULL;
	bucket_node bucket[10] = {0, };	// 根据数字个数 0 ~ 9 建立 10 个桶
	
	int count = get_max_digital_count(array, length);
	
	// 建立数据节点
	bucket_node* data = (bucket_node*)malloc(length * sizeof(bucket_node));
	if (!data) {
		printf("Error: out of memory!\n");
		return;
	}
	
	for (i = 0; i < length; i++) {
		data[i].key = array[i];
		data[i].next = NULL;
	}
	
	// 分配
	for (i = 0; i < length; i++) {
		index = get_ditital_at(data[i].key, count);
		if (bucket[index].next == NULL) {
			bucket[index].next = &data[i];
		}
		else {
			temp = &bucket[index];
			while (temp->next != NULL && temp->next->key < data[i].key) {
				temp = temp->next;
			}
			
			data[i].next = temp->next;
			temp->next = &data[i];
		}
	}
	
	// 收集
	index = 0;
	for (i = 0; i < 10; i++) {
		temp = bucket[i].next;
		while (temp != NULL) {
			array[index++] = temp->key;
			temp = temp->next;
		}
	}
	
	
	free(data);
}

// 基数排序
//
void radix_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	if (length <= 1) {
		return;
	}
	
	const int buffer_size = length * sizeof(int);
	
	int i, k, count, index;
	int bucket[10] = {0, };	// 根据数字个数 0 ~ 9 建立 10 个桶
	
	int* temp = (int*)malloc(buffer_size);
	if (!temp) {
		printf("Error: out of memory!\n");
		return;
	}
	
	count = get_max_digital_count(array, length);
	
	for (k = 1; k <= count; ++k) {
		memset(bucket, 0, 10 * sizeof(int));
		
		// 统计各桶中元素的个数
		for (i = 0; i < length; ++i) {
			index = get_ditital_at(array[i], k);
			++bucket[index];
		}
		
		// 为每个记录创建索引下标
		for (i = 1; i < 10; ++i) {
			bucket[i] += bucket[i - 1];
		}
		
		// 按索引下标顺序排列
		for (i = length - 1; i >= 0; --i) {
			index = get_ditital_at(array[i], k);
			assert(bucket[index] - 1 >= 0);
			temp[--bucket[index]] = array[i];
		}
		
		// 一趟桶排序完毕，拷贝结果
		memcpy(array, temp, buffer_size);
		
#ifdef DEBUG_SORT
		debug_print(" 第 %d 趟排序：", k);
		for (i = 0; i < length; ++i) {
			debug_print("%d ", array[i]);
		}
		
		debug_print("\n");
#endif
	}
	
	free(temp);
}
#define DEBUG_SEARCH

#ifdef DEBUG_SEARCH
#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

// 顺序查找:在任意序列中查找，成功时返回结点的位置，失败时返回 -1
//
int sequential_search(const int* array, int length, int key)
{
	assert(array && length >= 0);
	
	int i;
	
	for (i = 0; i < length; ++i) {
		if (array[i] == key) {
			return i;
		}
	}
	
	return -1;
}

// 二分查找:在有序序列中查找，成功时返回结点的位置，失败时返回 -1
//
int binary_search(const int* array, int length, int key)
{
	assert(array && length >= 0);
	
	int low = 0;
	int high = length;
	int mid;
	
	while (low <= high) {
		mid = (low + high) >> 1;
		
		if (array[mid] == key) {
			return mid;
		}
		
		if (array[mid] > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	
	return -1;
}

// 分块查找/索引顺序查找
//
int blocking_search(
					const int* array,
					int length,
					IndexNode* indexTable,
					int indexTableLength,
					int key)
{
	assert(array && length >= 0 && indexTable && indexTableLength >= 0);
	
#if 1
	// 二分查找索引表
	int i, mid;
	int low = 0;
	int high = indexTableLength - 1;
	
	while (low <= high) {
		mid = (low + high) >> 1;
		
		if (indexTable[mid].key == key) {
			return indexTable[mid].index;
		}
		else if (indexTable[mid].key > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	
	low = indexTable[low].index;
	high = indexTable[high].index;
	
#else
	
	// 顺序查找索引表
	int i;
	int low = 0;
	int high = length - 1;
	
	for (i = 0; i < indexTableLength; ++i) {
		if (indexTable[i].key > key) {
			high = indexTable[i].index - 1;
			break;
		}
		
		low = indexTable[i].index;
	}
#endif
	
	for (i = low; i <= high; ++i) {
		if (array[i] == key) {
			return i;
		}
	}
	
	return -1;
}

// 散列查找
// 

// 散列函数：取余法
// h(key) = key % tableLength
//
int hash_remiander(int key, int tableLength)
{
	return key % tableLength;
}

// 散列函数：相乘取整法
// h(key) = [tableLength * (key * A - [key * A])]
// A 约等于 (根号 5 - 1)/2 = 0.61803398
//
int hash_multi_round_off(int key, int tableLength)
{
	double d = key * 0.61803398;
	return (int)(tableLength * (d - (int)d));
}

// 探查时，使用的二重 hash 函数 h1。总的探查法为：
// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
// 
// 定义 h1(key) 的方法较多，但无论采用什么方法定义，都必须使 h1(key) 的值和
// tableLength 互素，才能使发生冲突的同义词地址均匀地分布在整个表中，
// 否则可能造成同义词地址的循环计算。
//
// 【例】若 tableLength 为素数，则 h1(key) 取 1 到 tableLength - 1 之间
//		的任何数均与 tableLength 互素，因此，我们可以简单地将它定义为：
//		h1(key) = key % (tableLength - 2) + 1
// 【例】若 tableLength 是 2 的方幂，
//      则 h1(key) 可取 1 到 tableLength - 1之间的任何奇数。
//
int hash_double(int key, int tableLength)
{
	return key % (tableLength - 2) + 1;
}

//=========================================================
//					开放地址法散列
//=========================================================
// 创建采用开放地址法的散列表
//
void create_open_address_hash_table(
									int* table,
									int tableLength,
									const int* data,
									int dataLength,
									Hash_Function hashFunc,
									Conflict_Resolution confictResolution,
									int zeroValue)
{
	assert(data && table && hashFunc
		   && dataLength > 0 && tableLength > 0);
	
	int i, j, index, index2, temp;
	
	// 初始化 hash table, 设置为序列中没有的值（零值）
	for (i = 0; i < tableLength; ++i) {
		table[i] = zeroValue;
	}
	
	for (i = 0; i < dataLength; ++i){
		index = (hashFunc)(data[i], tableLength);
		if (table[index] == zeroValue) {
			table[index] = data[i];
		}
		
		// 有冲突
		else {
			// 采用双重散列探查解决冲突
			// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
			if (Conflict_Resolution_Double_Hash == confictResolution) {
				index2 = hash_double(data[i], tableLength);
				
				j = 1;
				while (j < tableLength) {
					temp = index + j * index2;
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}
					
					++j;
				}
			}
			
			// 采用二次探查解决冲突
			// hi = (h(key) + i * i) % tableLength, 0 <= i <= tableLength - 1
			else if (Conflict_Resolution_Quadratic == confictResolution) {
				j = 1;
				while (j < tableLength) {
					temp = (index + j * j) % tableLength;
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}
					
					++j;
				}
				
				// hash 表可能已满，报错。
				// 在这里表有可能尚未填满，只是二次散列算法无法探查到那些空挡。
				if (temp == tableLength) {
					assert(0 && "Error: Hash table may be full!\n");
				}
			}
			
			// 采用线性探查解决冲突（Conflict_Resolution_Linear）
			// hi = (h(key) + i) % tableLength, 0 <= i <= tableLength - 1
			else {
				temp = (index + 1) % tableLength;	
				while (temp != index) {
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}
					
					temp = (++temp) % tableLength;
				}
				
				// hash 表已满，报错
				if (temp == index) {
					assert(0 && "Error: Hash table is full!\n");
				}
			}
		}
	}
	
#ifdef DEBUG_SEARCH
	debug_print("\n创建长度为 %d 的 hash table：\n  ", tableLength);
	for (i = 0; i < tableLength; ++i) {
		debug_print("%d ", table[i]);
	}
	debug_print("\n");
#endif
}

// 在采用开放地址法的散列表中查找
//
int open_address_hash_search(
							 int key,
							 const int* table,
							 int tableLength,
							 Hash_Function hashFunc,
							 Conflict_Resolution confictResolution,
							 int zeroValue)
{
	assert(table && hashFunc && tableLength > 0);
	assert(key != zeroValue);
	
	int j, index, index2, temp;
	
	index = (hashFunc)(key, tableLength);
	if (table[index] == key) {
		return index;
	}
	else if (table[index] == zeroValue) {
		return -1;
	}
	
	// 可能是有冲突
	else {
		// 采用双重散列探查继续查找
		// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
		if (Conflict_Resolution_Double_Hash == confictResolution) {
			index2 = hash_double(key, tableLength);
			j = 1;
			while (j < tableLength) {
				temp = index + j * index2;
				if (table[temp] == zeroValue) {
					return -1;
				}
				else if (table[temp] == key) {
					return temp;
				}
				
				++j;
			}
		}
		
		// 采用二次探查继续查找
		// hi = (h(key) + i * i) % tableLength, 0 <= i <= tableLength - 1
		else if (Conflict_Resolution_Quadratic == confictResolution) {
			j = 1;
			while (j < tableLength) {
				temp = (index + j * j) % tableLength;
				if (table[temp] == key) {
					return temp;
				}
				else if (table[index] == zeroValue) {
					return -1;
				}
				
				++j;
			}
		}
		
		// 采用线性探查继续查找（Conflict_Resolution_Linear）
		// hi = (h(key) + i) % tableLength, 0 <= i <= tableLength - 1
		else {
			temp = (index + 1) % tableLength;
			while (temp != index) {
				if (table[temp] == key) {
					return temp;
				}
				else if (table[temp] == zeroValue){
					return -1;
				}
				
				temp = (++temp) % tableLength;
			}
		}
	}
	
	return -1;
}

//=========================================================
//					拉链址法散列
//=========================================================

// 创建采用拉链法的散列表
//
void create_link_hash_table(
							Hash_Node** pTable,
							int tableLength,
							const int* data,
							int dataLength,
							Hash_Function hashFunc,
							int zeroValue)
{
	assert(pTable && data && hashFunc && tableLength > 0 && dataLength > 0);
	
	int i, index;
	Hash_Node* node, *newNode;
	Hash_Node* table = NULL;
	
	table = (Hash_Node*)malloc(tableLength * sizeof(Hash_Node));
	if (!table) {
		*pTable = NULL;
		printf("Error: out of memory!\n");
		return;
	}
	
	*pTable = table;
	
	// 初始化表
	for (i = 0; i < tableLength; ++i) {
		table[i].key = zeroValue;
		table[i].next = NULL;
	}
	
	for (i = 0; i < dataLength; ++i) {
		index = (hashFunc)(data[i], tableLength);
		if (table[index].key == zeroValue) {
			table[index].key = data[i];
		}
		else {
			node = &table[index];
			while (node->next) {
				node = node->next;
			}
			
			newNode = (Hash_Node*)malloc(sizeof(Hash_Node));
			newNode->key = data[i];
			newNode->next = NULL;
			
			node->next = newNode;
		}
	}
	
#ifdef DEBUG_SEARCH
	debug_print("\n创建长度为 %d 的 hash table：\n", tableLength);
	for (i = 0; i < tableLength; ++i) {
		node = &table[i];
		debug_print(" %d : ", i);
		while (node) {
			debug_print(" %d ->", node->key);
			node = node->next;
		}
		
		debug_print(" null\n");
	}
	debug_print("\n");
#endif
}

// 销毁采用拉链法的散列表
//
void destroy_link_hash_table(
							 Hash_Node* table,
							 int tableLength)
{
	int i;
	Hash_Node* node, *nextNode;
	
	for (i = 0; i < tableLength; ++i) {
		node = table[i].next;
		while (node) {
			nextNode = node->next;
			free(node);
			
			node = nextNode;
		}
	}
	
	free(table);
	table = NULL;
}

// 在采用拉链法的散列表中查找
//
int link_hash_search(
					 int key,
					 const Hash_Node* table,
					 int tableLength,
					 Hash_Function hashFunc,
					 int zeroValue)
{
	assert(table && hashFunc && tableLength > 0);
	assert(key != zeroValue);
	
	int index = (hashFunc)(key, tableLength);
	const Hash_Node* node = &table[index];
	
	while (node) {
		if (node->key == key) {
			return index;
		}
		
		node = node->next;
	}
	
	return -1;
}

// 打印数组
// 
void print_array(const int* a, int length, const char* prefix)
{
	assert(a && length >= 0);
	
	if (prefix) {
		printf("%s", prefix);
	}
	
	for (int i = 0; i < length; i++) {
		printf("%d ", a[i]);
	}
	
	printf("\n");
}

//==================================================================
//					测试各种排序算法
//==================================================================

typedef void (*Sort_Function)(int* array, int length);

struct SortFucntionInfo {
	char * name;
	Sort_Function func;
};

SortFucntionInfo sort_function_list[] = {
	{"直接插入排序",				insert_sort},
{"希尔排序",					shell_sort},
	{"冒泡排序",					bubble_sort},
{"冒泡排序优化版",			bubble_sort_opt},
	{"快速排序",					quick_sort},
{"直接选择排序",				selection_sort},
	{"堆排序",					heap_sort},
{"合并排序：自下向上二路归并",	merge_sort},
	{"合并排序：自上向下分治",		merge_sort_dc},
{"桶/箱排序",				bucket_sort},
	{"基数排序",					radix_sort},
{"", NULL}
};

// 测试某种排序算法
//
void test_sort_function(Sort_Function func)
{
	const int length = 11;
	const int count = 2;
	int array[count][length] = {
		{65, 32, 49, 10, 8, 72, 27, 42, 18, 58, 91},
	{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	};
	
	for (int i = 0; i < count; i++) {
		print_array(array[i], length, " original: ");
		
		func(array[i], length);
		
		print_array(array[i], length, "   sorted: ");
		
		printf("\n");
	}
}

// 测试各种排序算法
//
void test_sort()
{
	for (int i = 0; sort_function_list[i].func != NULL; ++i) {
		printf("\n=== %s ===\n", sort_function_list[i].name);
		test_sort_function(sort_function_list[i].func);
	}
	
	const int length = 11;
	printf("\n=== 计数排序 ===\n");
	int array2[11] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};
	
	print_array(array2, length, " data: ");
	
	counting_sort(array2, length, 100);
	
	print_array(array2, length, " data: ");
}

//==================================================================
//					测试各种查找算法
//==================================================================

void test_sequential_search();
void test_binary_search();
void test_blocking_search();
void test_open_address_hash_search();
void test_link_hash_search();
void test_binary_tree_search();

typedef void (*Test_Search_Function)();

struct TestSearchFucntionInfo {
	char * name;
	Test_Search_Function func;
};

TestSearchFucntionInfo test_search_function_list[] = {
	{"顺序查找",					test_sequential_search},
{"二分查找",					test_binary_search},
	{"分块查找",					test_blocking_search},
{"开放地址法哈希/散列查找",	test_open_address_hash_search},
	{"拉链法哈希/散列查找",		test_link_hash_search},
{"二叉查找树查找",			test_binary_tree_search},
	{"", NULL},
};

// 测试各种查找算法
//
void test_search()
{
	for (int i = 0; test_search_function_list[i].func != NULL; ++i) {
		printf("\n=== %s ===\n", test_search_function_list[i].name);
		(test_search_function_list[i].func)();
	}
}

// 测试顺序查找
//
void test_sequential_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};
	
	int key1 = 72;
	int key2 = 55;
	int pos;
	
	print_array(array, length, " data: ");
	
	pos = sequential_search(array, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	
	pos = sequential_search(array, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// 测试二分查找
//
void test_binary_search()
{
	// 二分查找要求序列有序
	const int length = 11;
	int array[length] = {8, 10, 18, 27, 32, 43, 49, 58, 65, 72, 96};
	
	int key1 = 72;
	int key2 = 55;
	int pos;
	
	print_array(array, length, " data: ");
	
	pos = binary_search(array, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	
	pos = binary_search(array, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// 测试分块查找
//
void test_blocking_search()
{
	// 分块查找要求序列分块有序: 块长为 3，共 4 块
	const int length = 11;
	int array[length] = {10, 8, 18, 43, 27, 32, 58, 49, 65, 72, 69};
	
	int key1 = 72;
	int key2 = 55;
	int pos;
	
	// 创建分块索引表：块长为 3，共 4 块。
	const int indexTableLength = 4;
	IndexNode indexNode[indexTableLength];
	indexNode[0].key = 18;
	indexNode[0].index = 2;
	indexNode[1].key = 43;
	indexNode[1].index = 3;
	indexNode[2].key = 65;
	indexNode[2].index = 8;
	indexNode[3].key = 72;
	indexNode[3].index = 9;
	
	print_array(array, length, " data: ");
	
	pos = blocking_search(array, length, indexNode, indexTableLength, key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	
	pos = blocking_search(array, length, indexNode, indexTableLength,  key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// 测试采用开放地址法的哈希查找
// 
void test_open_address_hash_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};
	
	int pos;
	int key1 = 72;
	int key2 = 55;
	
	print_array(array, length, " data: ");
	
	// 换成别的 hash 函数试试
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;	
	
	// 换成别的探查方式试试
	Conflict_Resolution conflictResolution = Conflict_Resolution_Linear;
	conflictResolution = Conflict_Resolution_Quadratic;
	//conflictResolution = Conflict_Resolution_Double_Hash;
	
	// 创建开放地址法散列表
	int tableLength = 17;	// 对于二重探查散列法，散列表长取素数或奇数为佳
	int* hashTable = (int*)malloc(tableLength * sizeof(int));
	if (!hashTable) {
		printf("Error: out of memory!\n");
		return;
	}
	
	create_open_address_hash_table(hashTable, tableLength, array, length, hashFunc, conflictResolution,-1);
	
	pos = open_address_hash_search(key1, hashTable, tableLength,hashFunc, conflictResolution,-1);
	printf(" try searching %d, index at hash is table %d\n", key1, pos);
	
	pos = open_address_hash_search(key2, hashTable, tableLength, hashFunc, conflictResolution,-1);
	printf(" try searching %d, index at hash is table %d\n", key2, pos);
	
	// 删除开放地址法散列表
	free(hashTable);
	hashTable = NULL;
}

// 测试采用拉链法的哈希查找
//
void test_link_hash_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};
	
	int key1 = 72;
	int key2 = 55;
	int pos;
	
	print_array(array, length, " data: ");
	
	// 换成别的 hash 函数试试
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;		
	
	// 创建拉链法散列表
	int tableLength = 7;
	Hash_Node* linkHashTable = NULL;
	
	create_link_hash_table(&linkHashTable, tableLength, array, length, hashFunc,-1);
	if (!linkHashTable){
		printf("Failed to create link hash table!\n");
		return;
	}
	
	pos = link_hash_search(key1, linkHashTable, tableLength, hashFunc,-1);
	printf(" try searching %d, index at hash table is %d\n", key1, pos);
	
	pos = link_hash_search(key2, linkHashTable, tableLength, hashFunc,-1);
	printf(" try searching %d, index at hash table is %d\n", key2, pos);
	
	// 销毁拉链法散列表
	destroy_link_hash_table(linkHashTable, tableLength);
}


void BST_insert(BSTree* tree, int key)
{
	assert(tree);
	
	BSTNode* parent;
	BSTNode* node = *tree;
	
	// find the parent that will add the new node.
	while (node) {
		// already exists
		if (node->key == key) {
			return;
		}
		
		parent = node;
		
		if (key < node->key) {
			node = node->leftChild;
		}
		else {
			node = node->rightChild;
		}
	}
	
	// malloc a new node.
	node = (BSTNode*)malloc(sizeof(BSTNode));
	if (!node) {
		printf("Error: out of memory!\n");
		return;
	}
	
	node->key = key;
	node->leftChild = NULL;
	node->rightChild = NULL;
	
	// tree is empty.
	if (NULL == *tree) {
		*tree = node;
	}
	
	else {
		// insert the node to the tree.
		if (key < parent->key) {
			parent->leftChild = node;
		}
		else {
			parent->rightChild = node;
		}
	}
}

void BST_remove(BSTree* tree, int key)
{
	assert(tree);
	
	BSTNode* parent = NULL, *temp = NULL;
	BSTNode* node = *tree;
	
	// find the node.
	while (node) {
		if (node->key == key) {
			break;
		}
		
		parent = node;
		
		if (key < node->key) {
			node = node->leftChild;
		}
		else {
			node = node->rightChild;
		}
	}
	
	// key is not in the tree.
	if (!node) {
		printf("Can not remove %d, it is not in the tree!\n", key);
		return;
	}
	
	// 如果节点是叶子节点，直接删除，把父节点相应孩子设置为 NULL
	if (NULL == node->leftChild && NULL == node->rightChild) {
		// tree root node equals the key
		if (node == *tree) {
			*tree = NULL;
		}
		else {
			assert(parent);
			
			if (parent->leftChild == node) {
				parent->leftChild = NULL;
			}
			else {
				parent->rightChild = NULL;
			}
		}
		
		free(node);
	}
	
	// 如果节点的左孩子不为空，右孩子为空
	else if (NULL != node->leftChild) {
		if (parent->leftChild == node) {
			parent->leftChild = node->leftChild;
		}
		else {
			parent->rightChild = node->leftChild;
		}
		
		free(node);
	}
	
	// 如果节点的右孩子不为空，左孩子为空
	else if (NULL != node->rightChild) {
		if (parent->leftChild == node) {
			parent->leftChild = node->rightChild;
		}
		else {
			parent->rightChild = node->rightChild;
		}
		
		free(node);
	}
	
	// 节点的左，右孩子均不为空
	else {
		// find the most left child of node in the right-child-tree
		// add set it as new parent.
		//
		//          node		<----- replace this node
		//		   /    \
		//       ...    ...
		//             /
		//           temp       <----- remove most left child
		//          /    \
		//        null  rightChild
		
		parent = node;
		temp = node->rightChild;
		while (temp->leftChild) {
			parent = temp;
			temp = temp->leftChild;
		}
		
		assert(temp);
		
		node->key = temp->key;
		parent->leftChild = temp->rightChild;
		
		free(node);
	}
}

BSTNode* BST_search(BSTree tree, int key)
{
#if 1
	// 递归实现
	if (tree == NULL || tree->key == key) {
		return tree;
	}
	else if (key < tree->key) {
		return BST_search(tree->leftChild, key);
	}
	else {
		return BST_search(tree->rightChild, key);
	}
#else
	// 循环实现
	BSTNode* node = tree;
	while (node) {
		if (key == node->key) {
			return node;
		}
		
		else {
			if (key < node->key) {
				node = node->leftChild;
			}
			else {
				node = node->rightChild;
			}
		}
	}
#endif
	return NULL;
}

// 平衡二叉树(Balanced Binary Tree)
//
void BBT_insert(BSTree* tree, int key)
{
	
}

void BBT_remove(BSTree* tree, int key)
{
	
}

// 根据数组内容创建二叉树
//
void BST_create(BSTree* tree, const int* data, int length)
{
	assert(tree && length >= 0);
	
	*tree = NULL;
	
	if (!data || length == 0) {
		return;
	}
	
	int i;
	for (i = 0; i < length; ++i) {
		BST_insert(tree, data[i]);
	}
}

// 销毁二叉树
//
void BST_destory(BSTree* tree)
{
	BSTNode* node = *tree;
	if (node) {
		BST_destory(&node->leftChild);
		BST_destory(&node->rightChild);
		
		free(node);
		node = NULL;
	}
	
	*tree = NULL;
}

// 前序遍历
void BST_prev_order_impl(BSTree tree, int* data, int& index)
{
	assert(data && tree && index >= 0);
	
	data[index] = tree->key;
	
	if (tree->leftChild) {
		BST_prev_order_impl(tree->leftChild, data, index);
	}
	
	if (tree->rightChild) {
		BST_prev_order_impl(tree->rightChild, data, ++index);
	}
}

void BST_prev_order(BSTree* tree, int* data)
{
	assert(data);
	
	if (!tree) {
		return;
	}
	
	int index = 0;
	
	BST_prev_order_impl(*tree, data, index);
}

// 中序遍历
void BST_in_order_impl(BSTree tree, int* data, int& index)
{
	assert(data && tree && index >= 0);
	
	if (tree->leftChild) {
		BST_in_order_impl(tree->leftChild, data, ++index);
	}
	
	data[index] = tree->key;
	
	if (tree->rightChild) {
		BST_in_order_impl(tree->rightChild, data, ++index);
	}
}

void BST_in_order(BSTree* tree, int* data)
{
	assert(data);
	
	if (!tree) {
		return;
	}
	
	int index = 0;
	
	BST_in_order_impl(*tree, data, index);
}

// 后序遍历
void BST_post_order_impl(BSTree tree, int* data, int& index)
{
	assert(data && tree && index >= 0);
	
	if (tree->leftChild) {
		BST_post_order_impl(tree->leftChild, data, ++index);
	}
	
	if (tree->rightChild) {
		BST_post_order_impl(tree->rightChild, data, ++index);
	}
	
	data[index] = tree->key;
}

void BST_post_order(BSTree* tree, int* data)
{
	assert(data);
	
	if (!tree) {
		return;
	}
	
	int index = 0;
	
	BST_post_order_impl(*tree, data, index);
}

#define max(a, b) (((a) > (b)) ? (a) : (b))

//#define DEBUG_TREE

//#ifdef DEBUG_TREE
//#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
//#else
//#define debug_print(fmt,...)
//#endif

// 模拟向磁盘写入节点
void disk_write(BTNode* node)
{
	printf("向磁盘写入节点\n");
}

// 模拟从磁盘读取节点
void disk_read(BTNode** node)
{
	printf("从磁盘读取节点\n");
}

// 按层次打印 B 树
void BTree_print(BTree tree, int her)
{
	int i;
	BTNode* node = tree;
	
	if (node) {
		printf("第 %d 层， %d node : ", her, node->keynum);
		
		for (i = 0; i < node->keynum; ++i) {
			printf("%c ", node->key[i]);
		}
		
		printf("\n");
		
		++her;
		for (i = 0 ; i <= node->keynum; i++) {
			if (node->child[i]) {
				BTree_print(node->child[i], her);
			}
		}
	}
	else {
		printf("树为空。\n");
	}
}

// 将非满的节点与其第 index 个满孩子节点合并
// parent 是一个非满的父节点
// node 是 tree 孩子表中下标为 index 的孩子节点，且是满的
void BTree_split_child(BTNode* parent, int index, BTNode* node)
{
	assert(parent && node);
	
	int i;
	
	// 创建新节点，存储 node 中后半部分的数据
	BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
	if (!newNode) {
		printf("Error! out of memory!\n");
		return;
	}
	
	newNode->isLeaf = node->isLeaf;
	newNode->keynum = BTree_T - 1;
	
	// 拷贝 node 后半部分关键字
	for (i = 0; i < newNode->keynum; ++i){
		newNode->key[i] = node->key[BTree_T + i];
		node->key[BTree_T + i] = 0;
	}
	
	// 如果 node 不是叶子节点，拷贝 node 后半部分的孩子节点
	if (!node->isLeaf) {
		for (i = 0; i < BTree_T; i++) {
			newNode->child[i] = node->child[BTree_T + i];
			node->child[BTree_T + i] = NULL;
		}
	}
	
	// 将 node 分裂出 newNode 之后，里面的数据减半
	node->keynum = BTree_T - 1;
	
	// 调整父节点
	for (i = parent->keynum; i > index; --i) {
		parent->child[i + 1] = parent->child[i];
	}
	
	parent->child[index + 1] = newNode;
	
	for (i = parent->keynum - 1; i >= index; --i) {
		parent->key[i + 1] = parent->key[i];
	}
	
	parent->key[index] = node->key[BTree_T - 1];
	++parent->keynum;
	
	// 清除 node 中的中后部数据
	// 可以不处理，因为是通过 keynum 控制访问的
	// 	for (i = BTree_T - 1; i < BTree_N; ++i) {
	// 		node->key[i] = 0;
	// 		node->child[i + 1] = NULL;
	// 	}
	
	// 写入磁盘
	disk_write(parent);
	disk_write(newNode);
	disk_write(node);
}

void BTree_insert_nonfull(BTNode* node, int key)
{
	assert(node);
	
	int i;
	
	// 节点是叶子节点，直接插入
	if (node->isLeaf) {
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			node->key[i + 1] = node->key[i];
			--i;
		}
		
		node->key[i + 1] = key;
		++node->keynum;
		
		// 写入磁盘
		disk_write(node);
	}
	
	// 节点是内部节点
	else {
		// 查找插入的位置
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			--i;
		}
		
		++i;
		
		// 从磁盘读取孩子节点
		disk_read(&node->child[i]);
		
		// 如果该孩子节点已满，分裂调整值
		if (node->child[i]->keynum == BTree_N) {
			BTree_split_child(node, i, node->child[i]);
			
			if (key > node->key[i]) {
				++i;
			}
		}
		
		BTree_insert_nonfull(node->child[i], key);
	}
}

void BTree_insert(BTree* tree, int key)
{
	BTNode* node;
	BTNode* root = *tree;
	
	// 树为空
	if (NULL == root) {
		root = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!root) {
			printf("Error! out of memory!\n");
			return;
		}
		root->isLeaf = true;
		root->keynum = 1;
		root->key[0] = key;
		
		*tree = root;
		
		// 写入磁盘
		disk_write(root);
		
		return;
	}
	
	// 节点已满，需要进行分裂调整
	if (root->keynum == BTree_N) {
		// 产生新节点当作根
		node = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!node) {
			printf("Error! out of memory!\n");
			return;
		}
		
		*tree = node;
		node->isLeaf = false;
		node->keynum = 0;
		node->child[0] = root;
		
		BTree_split_child(node, 0, root);
		
		BTree_insert_nonfull(node, key);
	}
	
	// 节点未满，在当前节点中插入 key
	else {
		BTree_insert_nonfull(root, key);
	}
}


// 对 tree 中的节点 node 进行合并孩子节点处理
// 注意：孩子节点的 keynum 必须均已达到下限，即均等于 BTree_T - 1
// 将 node 中索引为 index + 1 的孩子节点合并到索引为 index 的孩子节点中，
// 并将 tree 中索引为 index  的 key 下降到该节点中，调整相关的 key 和指针。
//
void BTree_merge_child(BTree* tree, BTNode* node, int index)
{
	assert(tree && node && index >= 0 && index < node->keynum);
	
	int i;
	
	int key = node->key[index];
	BTNode* prevChild = node->child[index];
	BTNode* nextChild = node->child[index + 1];
	
	assert(prevChild && prevChild->keynum == BTree_T - 1
		   && nextChild && nextChild->keynum == BTree_T - 1);
	
	prevChild->key[prevChild->keynum] = key;
	prevChild->child[prevChild->keynum + 1] = nextChild->child[0];
	++prevChild->keynum;
	
	// 合并
	for (i = 0; i < nextChild->keynum; ++i) {
		prevChild->key[prevChild->keynum] = nextChild->key[i];
		prevChild->child[prevChild->keynum + 1] = nextChild->child[i + 1];
		++prevChild->keynum;
	}
	
	// 在 node 中移除 key 以及指向后继孩子节点的指针
	for (i = index; i < node->keynum - 1; ++i) {
		node->key[i] = node->key[i + 1];
		node->child[i + 1] = node->child[i + 2];
	}
	
	node->key[node->keynum - 1] = 0;
	node->child[node->keynum] = NULL;
	--node->keynum;
	
	// 如果根节点没有 key 了，删之，并将根节点调整为前继孩子节点。
	if (node->keynum == 0) {
		if (*tree == node) {
			*tree = prevChild;
		}
		
		free(node);
		node = NULL;
	}
	
	free(nextChild);
}

void BTree_remove(BTree* tree, int key)
{
	// B-数的保持条件之一：
	// 非根节点的内部节点的关键字数目不能少于 BTree_T - 1
	
	int i, j, index;
	BTNode *root = *tree;
	BTNode *node = root;
	BTNode *prevChild, *nextChild, *child;
	int prevKey, nextKey;
	
	if (!root) {
		printf("Failed to remove %c, it is not in the tree!\n", key);
		return;
	}
	
	index = 0;
	while (index < node->keynum && key > node->key[index]) {
		++index;
	}
	
	//
	//  index of key:    i-1  i  i+1
	//	            +---+---+---+---+---+
	//             ...  +   + A +   +  ...
	//	            +---+---+---+---+---+
	//                 /    |    \
	//  index of C: i - 1   i    i + 1
	//               /      |      \
	//	    +---+---+     +---+	  +---+---+
	//     ...  +   +     +   +   +   +  ...
	//	    +---+---+     +---+	  +---+---+
	//      prevChild     child   nextChild
	
	// Find the key.
	if (index < node->keynum && node->key[index] == key) {
		// 1，所在节点是叶子节点，直接删除
		if (node->isLeaf) {
			for (i = index; i < node->keynum; ++i) {
				node->key[i] = node->key[i + 1];
				node->child[i + 1] = node->child[i + 2];
			}
			
			--node->keynum;
			
			if (node->keynum == 0) {
				assert(node == *tree);
				free(node);
				*tree = NULL;
			}
			
			return;
		}
		
		// 2a，如果位于 key 前的子节点的 key 数目 >= BTree_T，
		// 在其中找 key 的前驱，用前驱的 key 值赋予 key，
		// 然后在前驱所在孩子节点中递归删除前驱。
		else if (node->child[index]->keynum >= BTree_T) {
			prevChild = node->child[index];
			prevKey = prevChild->key[prevChild->keynum - 1];
			node->key[index] = prevKey;
			
			BTree_remove(&prevChild, prevKey);
		}
		
		// 2b，如果位于 key 后的子节点的 key 数目 >= BTree_T，
		// 在其中找 key 的后继，用后继的 key 值赋予 key，
		// 然后在后继所在孩子节点中递归删除后继。
		else if (node->child[index + 1]->keynum >= BTree_T) {
			nextChild = node->child[index + 1];
			nextKey = nextChild->key[0];
			node->key[index] = nextKey;
			
			BTree_remove(&nextChild, nextKey);
		}
		
		// 2c，前驱和后继都只包含 BTree_T - 1 个节点，
		// 将 key 下降前驱孩子节点，并将后继孩子节点合并到前驱孩子节点，
		// 删除后继孩子节点，在 node 中移除 key 和指向后继孩子节点的指针，
		// 然后在前驱所在孩子节点中递归删除 key。
		else if (node->child[index]->keynum == BTree_T - 1
				 && node->child[index + 1]->keynum == BTree_T - 1){
			prevChild = node->child[index];
			
			BTree_merge_child(tree, node, index);
			
			// 在前驱孩子节点中递归删除 key
			BTree_remove(&prevChild, key);
		}
	}
	
	// 3，key 不在内节点 node 中，则应当在某个包含 key 的子节点中。
	//  key < node->key[index], 所以 key 应当在孩子节点 node->child[index] 中
	else {
		child = node->child[index];
		if (!child) {
			printf("Failed to remove %c, it is not in the tree!\n", key);
			return;
		}
		
		if (child->keynum == BTree_T - 1) {
			prevChild = NULL;
			nextChild = NULL;
			
			if (index - 1 >= 0) {
				prevChild = node->child[index - 1];
			}
			
			if (index + 1 <= node->keynum) {
				nextChild = node->child[index + 1];
			}
			
			// 3a，如果所在孩子节点相邻的兄弟节点中有节点至少包含 BTree_t 个关键字
			// 将 node 的一个关键字下降到 child 中，将相邻兄弟节点中一个节点上升到
			// node 中，然后在 child 孩子节点中递归删除 key。
			if ((prevChild && prevChild->keynum >= BTree_T)
				|| (nextChild && nextChild->keynum >= BTree_T)) {
				
				if (nextChild && nextChild->keynum >= BTree_T) {
					child->key[child->keynum] = node->key[index];
					child->child[child->keynum + 1] = nextChild->child[0];
					++child->keynum;
					
					node->key[index] = nextChild->key[0];
					
					for (j = 0; j < nextChild->keynum - 1; ++j) {
						nextChild->key[j] = nextChild->key[j + 1];
						nextChild->child[j] = nextChild->child[j + 1];
					}
					--nextChild->keynum;
				}
				else {
					for (j = child->keynum; j > 0; --j) {
						child->key[j] = child->key[j - 1];
						child->child[j + 1] = child->child[j];
					}
					child->child[1] = child->child[0];
					child->child[0] = prevChild->child[prevChild->keynum];
					child->key[0] = node->key[index - 1];
					++child->keynum;
					
					node->key[index - 1] = prevChild->key[prevChild->keynum - 1];
					
					--prevChild->keynum;
				}
			}
				
				// 3b, 如果所在孩子节点相邻的兄弟节点都只包含 BTree_t - 1 个关键字，
				// 将 child 与其一相邻节点合并，并将 node 中的一个关键字下降到合并节点中，
				// 再在 node 中删除那个关键字和相关指针，若 node 的 key 为空，删之，并调整根。
				// 最后，在相关孩子节点中递归删除 key。
			else if ((!prevChild || (prevChild && prevChild->keynum == BTree_T - 1))
				&& ((!nextChild || nextChild && nextChild->keynum == BTree_T - 1))) {
				if (prevChild && prevChild->keynum == BTree_T - 1) {
					
					BTree_merge_child(tree, node, index - 1);
					
					child = prevChild;
				}
				
				else if (nextChild && nextChild->keynum == BTree_T - 1) {
					
					BTree_merge_child(tree, node, index);
				}
				}
		}
		
		BTree_remove(&child, key);
	}
}

BTNode* BTree_search(const BTree tree, int key, int* pos)
{
	if (!tree) {
		return NULL;
	}
	
	int i = 0;
	
	while (i < tree->keynum && key > tree->key[i]) {
		++i;
	}
	
	// Find the key.
	if (i < tree->keynum && tree->key[i] == key) {
		if (pos) {
			*pos = i;
		}
		
		return tree;
	}
	
	// tree 为叶子节点，找不到 key，查找失败返回
	if (tree->isLeaf) {
		return NULL;
	}
	
	// 节点内查找失败，但 tree->key[i - 1]< key < tree->key[i]，
	// 下一个查找的结点应为 child[i]
	
	// 从磁盘读取第 i 个孩子的数据
	disk_read(&tree->child[i]);
	
	// 递归地继续查找于树 tree->child[i]
	return BTree_search(tree->child[i], key, pos);
}

void BTree_create(BTree* tree, const int* data, int length)
{
	assert(tree);
	
	int i;
	
#ifdef DEBUG_TREE
	debug_print("\n 开始创建 B- 树，关键字为:\n");
	for (i = 0; i < length; i++) {
		printf(" %c ", data[i]);
	}
	debug_print("\n");
#endif
	
	
	for (i = 0; i < length; i++) {
#ifdef DEBUG_TREE
		debug_print("\n插入关键字 %c:\n", data[i]);
#endif
		BTree_insert(tree, data[i]);
		
#ifdef DEBUG_TREE
		BTree_print(*tree);
#endif
	}
	
	debug_print("\n");
}

void BTree_destory(BTree* tree)
{
	int i;
	BTNode* node = *tree;
	
	if (node) {
		for (i = 0; i <= node->keynum; i++) {
			BTree_destory(&node->child[i]);
		}
		
		free(node);
	}
	
	*tree = NULL;
}


static RBNode RBNode_Nil = {RB_Black, 0, 0, 0, 0};

RBNode* RBTree_nil()
{
	return &RBNode_Nil;
}

void RBTree_print(RBTree tree, int her)
{
	int i;
	RBNode* node = tree;
	
	assert(node);
	
	if (node != &RBNode_Nil) {
		for (i = 0; i < her; i++) {
			printf(" ");
		}
		printf("第 %d 层， %d(%c)\n",
			   her, node->key, node->color == RB_Black ? 'B' : 'R');
		
		if (node->leftChild != &RBNode_Nil) {
			RBTree_print(node->leftChild, her + 1);
		}
		
		if (node->rightChild != &RBNode_Nil) {
			RBTree_print(node->rightChild, her + 1);
		}
	}
}

// 最小关键字元素
RBNode* RBTree_minimum(RBNode* node)
{
	assert(node);
	
	RBNode* temp = node;
	while (temp->leftChild != &RBNode_Nil) {
		temp = temp->leftChild;
	}
	
	return temp;
}


// 最大关键字元素
RBNode* RBTree_maximum(RBNode* node)
{
	assert(node);
	
	RBNode* temp = node;
	while (temp->rightChild != &RBNode_Nil) {
		temp = temp->rightChild;
	}
	
	return temp;
}

// 中序遍历中的前驱
RBNode* RBTree_predecessor(RBNode* node)
{
	assert(node);
	
	RBNode* child = node->leftChild;
	
	// 没有左孩子，返回自身
	if (child == &RBNode_Nil) {
		return node;
	}
	
	// 只有左孩子，则左孩子是其直接前驱
	else if (child->rightChild == &RBNode_Nil) {
		return child->leftChild;
	}
	
	// 左右孩子均有，则右孩子树中最大的元素为其直接前驱
	else {
		return RBTree_maximum(child->rightChild);
	}
}

// 中序遍历中的后继
RBNode* RBTree_successor(RBNode* node)
{
	// 有右孩子，则右孩子树中最小的元素为其直接后继
	if (node->rightChild != &RBNode_Nil) {
		return RBTree_minimum(node->rightChild);
	}
	
	// 没有右孩子，向上找到的第一个左分支节点为其直接后继，
	// 即 node 为其直接后继的左孩子树中的最大元素。
	RBNode* temp = node;
	RBNode* parent = temp->parent;
	
	while (parent != &RBNode_Nil && temp == parent->rightChild) {
		temp = parent;
		parent = temp->parent;
	}
	
	return parent;
}

RBNode* RBTree_search(const RBTree tree, int key)
{
	RBNode* node = tree;
	
	while (node != &RBNode_Nil) {
		if (node->key == key) {
			return node;
		}
		
		else if (node->key < key) {
			node = node->rightChild;
		}
		else {
			node = node->leftChild;
		}
	}
	
	return &RBNode_Nil;
}

// 左旋
//            node                        right
//           /    \                      /     \
//          a    right     -->         node     c
//              /     \               /    \
//             b       c             a      b
//
void RBTree_left_rotate(RBTree* tree, RBNode* node)
{
	assert(node->rightChild && (*tree)->parent == &RBNode_Nil);
	
	RBNode* right = node->rightChild;
	
	// set b
	node->rightChild = right->leftChild;
	if (right->leftChild != &RBNode_Nil) {
		right->leftChild->parent = node;
	}
	
	right->parent = node->parent;
	if (node->parent == &RBNode_Nil) {
		*tree = right;
	}
	else if (node->parent->leftChild == node) {
		node->parent->leftChild = right;
	}
	else {
		node->parent->rightChild = right;
	}
	
	right->leftChild = node;
	node->parent = right;
}

// 右旋
//            node                  left
//           /    \                /    \
//         left    c     -->      a     node
//        /     \                      /    \
//       a       b                    b      c
//
void RBTree_right_rotate(RBTree* tree, RBNode* node)
{
	assert(node->leftChild && (*tree)->parent == &RBNode_Nil);
	
	RBNode* left = node->leftChild;
	
	// set b
	node->leftChild = left->rightChild;
	if (left->rightChild != &RBNode_Nil) {
		left->rightChild->parent = node;
	}
	
	left->parent = node->parent;
	if (node->parent == &RBNode_Nil) {
		*tree = left;
	}
	else if (node->parent->leftChild == node) {
		node->parent->leftChild = left;
	}
	else {
		node->parent->rightChild = left;
	}
	
	left->rightChild = node;
	node->parent = left;
}

// 插入调整
void RBTree_insert_fixup(RBTree* tree, RBNode* node)
{
	assert(tree && node);
	
	RBNode* parent = NULL;
	RBNode* uncle = NULL;
	RBNode* grand = NULL;
	RBNode* temp = NULL;
	
	parent = node->parent;
	while (parent->color == RB_Red) {
		// 根据红黑树性质，以及 node 的父亲的颜色为红色，
		// 可以肯定 node 的祖父节点一定存在
		grand = parent->parent;
		
		// 确定叔父节点
		if (parent == grand->leftChild) {
			uncle = grand->rightChild;
			
			// case 1: 叔父节点为红色
			//         grand(B)        new node  ->    grand(R)
			//         /     \                         /      \
			//   parent(R)    uncle(R)    -->     node(B)   uncle(B)
			//   /     \      /  \                /   \        /  \
			//  a    node(R) d    e          parent  node(R)  d    e
			//       /   \                          /   \
			//      b     c                        b     c
			//
			if (uncle->color == RB_Red) {
				parent->color = RB_Black;
				uncle->color = RB_Black;
				grand->color = RB_Red;
				node = grand;
				parent = node->parent;
			}
			
			// case 2, case 3：叔父节点为黑色
			//         case 2     --->    case 3         -->  done
			//                      parent is as new node
			//         grand(B)          grand(B)            node(B)
			//         /     \           /      \           /      \
			//   parent(R)    d       node(R)   d      parent(R)  grand(R)
			//   /     \               /     \           /  \      /   \
			//  a    node(R)      parent(R)   c         a    b    c     d
			//       /   \         /  \
			//      b     c       a    b
			//
			else {
				// 将 case 2 装换成 case 3
				// 注意：转换到 case 3之后， parent 为case 2中的 node，
				// node 为 case 2 中的 parent
				if (parent->rightChild == node) {
					RBTree_left_rotate(tree, parent);
					temp = parent;
					parent = node;
					node = temp;
				}
				
				// case 3
				parent->color = RB_Black;
				grand->color = RB_Red;
				
				RBTree_right_rotate(tree, grand);
			}
		}
		else {
			// 与上面的情况对称
			uncle = grand->leftChild;
			
			if (uncle->color == RB_Red) {
				parent->color = RB_Black;
				uncle->color = RB_Black;
				grand->color = RB_Red;
				node = grand;
				parent = node->parent;
			}
			
			else {
				// 将 case 2 装换成 case 3
				if (parent->leftChild == node) {
					RBTree_right_rotate(tree, parent);
					temp = parent;
					parent = node;
					node = temp;
				}
				
				// case 3
				parent->color = RB_Black;
				grand->color = RB_Red;
				
				RBTree_left_rotate(tree, grand);
			}
		}
	}
	
	(*tree)->color = RB_Black;
}

// 将节点 node 插入树 tree 内，然后将 node 着色为红色，此时，树可能不再
// 满足红黑树性质，因此调用 RBTree_insert_fixup 来对节点重新着色调整。
void RBTree_insert(RBTree* tree, RBNode* node)
{
	assert(tree && node);
	
	RBNode* parent = &RBNode_Nil;
	RBNode* temp = *tree;
	
	// 像二叉树一样，在树中查找适当的位置插入
	while (temp != &RBNode_Nil) {
		parent = temp;
		
		if (node->key < temp->key) {
			temp = temp->leftChild;
		}
		else {
			temp = temp->rightChild;
		}
	}
	
	node->parent = parent;
	
	// 树为空
	if (parent == &RBNode_Nil) {
		*tree = node;
	}
	else if (node->key < parent->key) {
		parent->leftChild = node;
	}
	else {
		parent->rightChild = node;
	}
	
	// 为节点着色
	node->leftChild = &RBNode_Nil;
	node->rightChild = &RBNode_Nil;
	node->color = RB_Red;
	
	// 调整树使之满足红黑树性质
	RBTree_insert_fixup(tree, node);
}

// 删除调整
void RBTree_delete_fixup(RBTree* tree, RBNode* node)
{
	RBNode* brother = NULL;
	RBNode* parent = NULL;
	
	while (node != *tree && node->color == RB_Black) {
		parent = node->parent;
		
		// 确定兄弟节点
		if (node == parent->leftChild) {
			brother = parent->rightChild;
			
			// case 1: 兄弟节点为红色
			if (brother->color == RB_Red) {
				brother->color = RB_Black;
				parent->color = RB_Red;
				
				RBTree_left_rotate(tree, parent);
				
				brother = node->parent->rightChild;
			}
			
			// case 2: 兄弟节点的两孩子均为黑色
			if (brother->leftChild->color == RB_Black
				&& brother->rightChild->color == RB_Black) {
				brother->color = RB_Red;
				node = parent;
			}
			
			else {
				// case 3: 兄弟节点的左孩子为红色，右孩子为黑色
				if (brother->rightChild->color == RB_Black) {
					brother->leftChild->color = RB_Black;
					brother->color = RB_Red;
					
					RBTree_right_rotate(tree, brother);
					
					brother = node->parent->rightChild;
				}
				
				// case 4:兄弟节点的右孩子为红色
				brother->color = parent->color;
				parent->color = RB_Black;
				brother->rightChild->color = RB_Black;
				
				RBTree_left_rotate(tree, parent);
				
				node = *tree;
			}
		}
		else {
			brother = parent->leftChild;
			
			// case 1: 兄弟节点为红色
			if (brother->color == RB_Red) {
				brother->color = RB_Black;
				parent->color = RB_Red;
				
				RBTree_right_rotate(tree, parent);
				
				brother = parent->leftChild;
			}
			
			// case 2: 兄弟节点的两孩子均为黑色
			if (brother->leftChild->color == RB_Black
				&& brother->rightChild->color == RB_Black) {
				brother->color = RB_Red;
				node = parent;
			}
			
			else {
				// case 3: 兄弟节点的左孩子为红色，右孩子为黑色
				if (brother->rightChild->color == RB_Black) {
					brother->leftChild->color = RB_Black;
					brother->color = RB_Red;
					
					RBTree_left_rotate(tree, brother);
					
					brother = parent->rightChild;
				}
				
				// case 4:兄弟节点的右孩子为红色
				brother->color = parent->color;
				parent->color = RB_Black;
				brother->leftChild->color = RB_Black;
				
				RBTree_right_rotate(tree, parent);
				
				node = *tree;
			}
		}
	}
	
	node->color = RB_Black;
}

// 删除
RBNode* RBTree_delete(RBTree* tree, RBNode* node)
{
	RBNode* successor = NULL;
	RBNode* temp = NULL;
	
	if (node->leftChild == &RBNode_Nil || node->rightChild == &RBNode_Nil) {
		successor = node;
	}
	else {
		successor = RBTree_successor(node);
	}
	
	if (successor->leftChild != &RBNode_Nil) {
		temp = successor->leftChild;
	}
	else {
		temp = successor->rightChild;
	}
	
	temp->parent = successor->parent;
	
	if (successor->parent == &RBNode_Nil) {
		*tree = temp;
	}
	else {
		if (successor == successor->parent->leftChild) {
			successor->parent->leftChild = temp;
		}
		else {
			successor->parent->rightChild = temp;
		}
	}
	
	if (successor != node) {
		node->key = successor->key;
	}
	
	if (successor->color == RB_Black) {
		RBTree_delete_fixup(tree, temp);
	}
	
	return successor;
}

//==================================================================
//					测试二叉查找树
//==================================================================

void test_binary_tree_search()
{
	// 二叉查找树要求记录的关键字唯一，所以不能有相同的记录
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 8, 72, 27, 42, 18, 58, 91};
	
	int key1 = 72;
	int key2 = 55;
	
	print_array(array, length, " data: ");
	
	BSTree tree = NULL;
	BSTNode* node = NULL;
	
	// 创建二叉树
	BST_create(&tree, array, length);
	if (!tree) {
		printf("Failed to create binary search tree!\n");
		return;
	}
	
	// 查找
	node = BST_search(tree, key1);
	printf("  %s %d in binary search tree.\n",
		   (NULL == node) ? "Could not find" : "Yeah! Found", key1);
	
	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		   (NULL == node) ? "Could not find" : "Found", key2);
	
	// 插入节点
	printf(" Insert %d to binary search tree.\n", key2);
	BST_insert(&tree, key2);
	
	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		   (NULL == node) ? "Could not find" : "Yeah! Found", key2);
	
	// 删除节点
	key2 = 27;
	printf(" Remove %d from binary search tree.\n", key2);
	BST_remove(&tree, key2);
	
	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		   (NULL == node) ? "Could not find" : "Yeah! Found", key2);
	
	// 销毁二叉树
	BST_destory(&tree);
	
	assert(NULL == tree);
}

//==================================================================
//					测试 B 树
//==================================================================
void test_BTree_search(BTree tree, int key)
{
	int pos = -1;
	BTNode*	node = BTree_search(tree, key, &pos);
	if (node) {
		printf("在%s节点（包含 %d 个关键字）中找到关键字 %c，其索引为 %d\n",
			   node->isLeaf ? "叶子" : "非叶子",
			   node->keynum, key, pos);
	}
	else {
		printf("在树中找不到关键字 %c\n", key);
	}
}

void test_BTree_remove(BTree* tree, int key)
{
	printf("\n移除关键字 %c \n", key);
	BTree_remove(tree, key);
	BTree_print(*tree,1);
	printf("\n");
}

void test_btree()
{
	const int length = 10;
	int array[length] = {
		'G', 'M', 'P', 'X', 'A', 'C', 'D', 'E', 'J', 'K',
			//'N', 'O', 'R', 'S', 'T', 'U', 'V', 'Y', 'Z', 'F'
	};
	
	BTree tree = NULL;
	BTNode* node = NULL;
	int pos = -1;
	int key1 = 'R';		// in the tree.
	int key2 = 'B';		// not in the tree.
	
	// 创建
	BTree_create(&tree, array, length);
	
	printf("\n=== 创建 B 树 ===\n");
	BTree_print(tree,1);
	printf("\n");
	
	// 查找
	test_BTree_search(tree, key1);
	printf("\n");
	test_BTree_search(tree, key2);
	
	// 插入关键字
	printf("\n插入关键字 %c \n", key2);
	BTree_insert(&tree, key2);
	BTree_print(tree,1);
	printf("\n");
	
	test_BTree_search(tree, key2);
	
	// 移除关键字
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'M';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'E';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'G';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'A';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'D';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'K';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'P';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'J';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'C';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	key2 = 'X';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	
	// 销毁
	BTree_destory(&tree);
}

//==================================================================
//					测试红黑树
//==================================================================
void test_redblacktree_delete(RBTree* tree, int key)
{
	RBNode* node = RBTree_search(*tree, key);
	assert(node != RBTree_nil());
	
	printf("\n删除节点 %d \n", node->key);
	
	node = RBTree_delete(tree, node);
	free(node);
	
	RBTree_print(*tree,1);
}

void test_redblacktree()
{
	const int length = 14;
	int array[length] = {
		2, 3, 4, 6, 7, 11, 9, 18, 12, 14, 19, 17, 22, 20
	};
	
	int i;
	RBTree tree = RBTree_nil();
	RBNode* node = NULL;
	
	// 插入节点生成树
	for (i = 0; i < length; i++) {
		node = (RBNode*)malloc(sizeof(RBNode));
		node->key = array[i];
		node->color = RB_Red;
		node->parent = RBTree_nil();
		node->leftChild = RBTree_nil();
		node->rightChild = RBTree_nil();
		
		RBTree_insert(&tree, node);	
	}
	
	RBTree_print(tree,1);
	
	// 插入测试
	node = (RBNode*)malloc(sizeof(RBNode));
	node->key = 21;
	
	printf("\n插入节点 %d\n", node->key);
	
	RBTree_insert(&tree, node);
	RBTree_print(tree,1);
	
	// 查找测试
	i = 6;
	node = RBTree_search(tree, i);
	
	if (node != RBTree_nil()) {
		printf("\n在红黑树中找到节点 %d\n", node->key);
	}
	else {
		printf("\n在红黑树中找不到节点 %d\n", i);
	}
	
	// 删除测试
	// 
	i = 4;// 取值 1, 2, 3, 4，分别对应 case 1, 2, 3, 4
	
	switch (i)
	{
	case 1:	// 兄弟为红色
		test_redblacktree_delete(&tree, 3);
		break;
		
	case 2:	// 兄弟为黑色，且兄弟的两孩子均为黑色
		test_redblacktree_delete(&tree, 12);
		break;
		
	case 3:	// 兄弟为黑色，且兄弟的左孩子为红色，右孩子均为黑色
		test_redblacktree_delete(&tree, 19);
		break;
		
	case 4:	// 兄弟为黑色，且兄弟的右孩子为红色
		test_redblacktree_delete(&tree, 9);
		break;
	}
	
	test_redblacktree_delete(&tree, 21);
	
	// 删除树
	for (i = 0; i < length; i++) {
		node = RBTree_search(tree, array[i]);
		
		if (node != RBTree_nil()) {
			printf("删除 %d\n", node->key);
			node = RBTree_delete(&tree, node);
			free(node);
		}
	}
	
	assert(tree == RBTree_nil());
}

typedef void (*Test_Function)();

Test_Function test_function[] = {
		test_sort,		// 测试排序算法
		test_search,		// 测试查找算法
		test_btree,			// 测试 B 树
		test_redblacktree,	// 测试红黑树
		nullptr
};

int main(int argc, const char* argv[])
{
	for (int i = 0; test_function[i] != nullptr; i++) {
		test_function[i](); system("pause");
	}
	
	printf("\n测试结束\n");
	system("pause");
	return 0;
}
