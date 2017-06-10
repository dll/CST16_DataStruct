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
// ��ͻ����ʱ����������̽��ķ�ʽ
enum Conflict_Resolution
{
	Conflict_Resolution_Linear		= 0,	// ����̽��
	Conflict_Resolution_Quadratic	= 1,	// ����̽��
	Conflict_Resolution_Double_Hash	= 2,	// ˫��ɢ��̽��
};

// hash ����
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
// ���� B ������С����
// ÿ���ڵ��йؼ��ֵ������Ŀ BTree_N = 2 * BTree_T - 1
#define	BTree_T		2
#define BTree_N		(BTree_T * 2 - 1)

struct BTNode {
	int	keynum;						// ����йؼ��ֵĸ�����keynum <= BTree_N
	int key[BTree_N];				// �ؼ�������Ϊkey[0..keynum - 1]
	BTNode* child[BTree_T * 2];		// ����ָ������Ϊchild[0..keynum]
	bool isLeaf;					// �Ƿ���Ҷ�ӽڵ�ı�־
};

typedef BTNode* BTree;				// B��������

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

// ֱ�Ӳ�������
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

// ϣ������
//
void shell_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, j , temp;
	int increment = length;
	
	do {
		increment = increment / 3 + 1;
		
		// ϣ�������е�һ������increment Ϊ��ǰ����
		// �� [increment, length - 1] ֮��ļ�¼�ֱ������鵱ǰ��������
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

// ð������
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

// ð������Ľ���
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


// �� [low, high] �����֣������ػ�׼��¼��λ��
int quick_partition(int* array, int low, int high)
{
	assert(array && low >= 0 && low <= high);
	
	int pivot = array[low]; // ������ĵ� 1 ����¼��Ϊ��׼
	
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

// ��������
//
void quick_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	quick_sort_impl( array, 0, length - 1);
}


// ֱ��ѡ������
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


// ɸѡ�������ѣ��� [low] ֮�⣬[low] ���������Ӿ����Ǵ����
void adjust_heap(int* heap, int low, int high)
{
	assert(heap);
	
#if 1	// ѭ��ʵ��
	
	int i = low;
	int j = 2 * i;
	int temp = heap[i];
	
	while (j <= high) {
		// �����������ӣ�j Ϊ�����д���Ǹ����±�
		if (j < high && heap[j] < heap[j + 1]) {
			j = j + 1;
		}
		
		// ���Ƕ�
		if (temp >= heap[j]) {
			break;
		}
		
		// ����ɸѡ
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * i;
		}
	}
	
	heap[i] = temp;
	
#else	// �ݹ�ʵ��
	
	int i = low;
	int j = 2 * i;
	int temp = heap[i];
	
	if (j >= high) {
		return;
	}
	
	// �����������ӣ�j Ϊ�����д���Ǹ����±�
	if (j < high && heap[j + 1] > heap[j]) {
		j = j + 1;
	}
	
	// �Ѿ�Ϊ�ѣ��������
	if (heap[low] >= heap[j]) {
		return;
	}
	
	heap[i] = heap[j];
	heap[j] = temp;
	
	// ����֮��[j, high] ���ܲ�������ˣ����������
	adjust_heap(heap, j, high);
	
#endif
}

// ֻ��һ���������Ƕѣ�������ȫ�������У�������� i > n/2 �Ľ�㶼��Ҷ�ӣ�
// �������Щ���Ϊ�������������Ƕѡ�����������ֻ�����ν������Ϊ
// n/2, n/2 - 1, ��, 0 �Ľ����Ϊ��������������Ϊ�Ѽ��ɡ�
void build_heap(int* heap, int length)
{
	assert(heap && length >= 0);
	
	int i;
	
	for(i = length / 2; i >= 0; --i) {
		adjust_heap(heap, i, length - 1);
	}
}


// ������
//
void heap_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, temp;
	
	// �� [0, length - 1] ���ɳ�ʼ��
	build_heap(array, length);
	
	// �Ե�ǰ������ [0, i - 1] ���ж����򣬹��� length - 1 �ˡ�
	for(i = length - 1; i > 0; --i) {
		// ���Ѷ��Ͷ������һ����¼����
		temp = array[0];
		array[0] = array[i];
		array[i]= temp;
		
		// �� [0, i - 1] ���µ���Ϊ�ѣ����� [0] ����Υ��������
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

// �� [0, length - 1] ��һ�˹鲢����Ϊ n  �Ĺ鲢����
void merge_pass(int* array, int length, int n)
{
	assert(array && length >= 1 && n >= 1);
	
	int i;
	int sortLength = 2 * n;
	
	// �鲢����Ϊ n ����������������
	for(i = 0; i + sortLength - 1 < length; i = i + sortLength) {
		merge(array, i, i + n - 1, i + sortLength - 1);
	}
	
	// �� i + n - 1 < length - 1����ʣ��һ�����ļ��ֿգ�����鲢��
	// �������������У����к�һ������С�� n, �鲢������������С�
	if (length - 1 > i + n - 1) {
		merge(array, i, i + n - 1, length - 1);
	}
}

// �÷��η��������Ͻ��ж�·�鲢����
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

// �÷��η��������½�������
void merge_sort_dc(int* array, int length)
{
	assert(array && length >= 0);
	
	merge_sort_dc_impl(array, 0, length - 1);
}

// array �м�¼��ֵ������ڷ�Χ [0, k] ֮�䡣
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
	
	// ����
	for (i = 0; i < length; ++i) {
		++counts[temp[i]];
	}
	
	// ȷ��˳��
	for (i = 1; i <= k; ++i) {
		counts[i] += counts[i - 1];
	}
	
	// ����
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

// ��/Ͱ����ͻ��������Կռ任ʱ��
//
struct bucket_node {
	int key;
	bucket_node* next;
};

// ȡ���������������λ��
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

// ȡ���� num �дӵ͵��ߵ� n λ�ϵ�����
int get_ditital_at(int num, int n)
{
	while (--n > 0) {
		num /= 10;
	}
	
	return (num % 10);
}

// ��/Ͱ����
//
void bucket_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	if (length <= 1) {
		return;
	}
	
	int i, index;
	bucket_node* temp = NULL;
	bucket_node bucket[10] = {0, };	// �������ָ��� 0 ~ 9 ���� 10 ��Ͱ
	
	int count = get_max_digital_count(array, length);
	
	// �������ݽڵ�
	bucket_node* data = (bucket_node*)malloc(length * sizeof(bucket_node));
	if (!data) {
		printf("Error: out of memory!\n");
		return;
	}
	
	for (i = 0; i < length; i++) {
		data[i].key = array[i];
		data[i].next = NULL;
	}
	
	// ����
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
	
	// �ռ�
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

// ��������
//
void radix_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	if (length <= 1) {
		return;
	}
	
	const int buffer_size = length * sizeof(int);
	
	int i, k, count, index;
	int bucket[10] = {0, };	// �������ָ��� 0 ~ 9 ���� 10 ��Ͱ
	
	int* temp = (int*)malloc(buffer_size);
	if (!temp) {
		printf("Error: out of memory!\n");
		return;
	}
	
	count = get_max_digital_count(array, length);
	
	for (k = 1; k <= count; ++k) {
		memset(bucket, 0, 10 * sizeof(int));
		
		// ͳ�Ƹ�Ͱ��Ԫ�صĸ���
		for (i = 0; i < length; ++i) {
			index = get_ditital_at(array[i], k);
			++bucket[index];
		}
		
		// Ϊÿ����¼���������±�
		for (i = 1; i < 10; ++i) {
			bucket[i] += bucket[i - 1];
		}
		
		// �������±�˳������
		for (i = length - 1; i >= 0; --i) {
			index = get_ditital_at(array[i], k);
			assert(bucket[index] - 1 >= 0);
			temp[--bucket[index]] = array[i];
		}
		
		// һ��Ͱ������ϣ��������
		memcpy(array, temp, buffer_size);
		
#ifdef DEBUG_SORT
		debug_print(" �� %d ������", k);
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

// ˳�����:�����������в��ң��ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
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

// ���ֲ���:�����������в��ң��ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
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

// �ֿ����/����˳�����
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
	// ���ֲ���������
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
	
	// ˳�����������
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

// ɢ�в���
// 

// ɢ�к�����ȡ�෨
// h(key) = key % tableLength
//
int hash_remiander(int key, int tableLength)
{
	return key % tableLength;
}

// ɢ�к��������ȡ����
// h(key) = [tableLength * (key * A - [key * A])]
// A Լ���� (���� 5 - 1)/2 = 0.61803398
//
int hash_multi_round_off(int key, int tableLength)
{
	double d = key * 0.61803398;
	return (int)(tableLength * (d - (int)d));
}

// ̽��ʱ��ʹ�õĶ��� hash ���� h1���ܵ�̽�鷨Ϊ��
// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
// 
// ���� h1(key) �ķ����϶࣬�����۲���ʲô�������壬������ʹ h1(key) ��ֵ��
// tableLength ���أ�����ʹ������ͻ��ͬ��ʵ�ַ���ȵطֲ����������У�
// ����������ͬ��ʵ�ַ��ѭ�����㡣
//
// �������� tableLength Ϊ�������� h1(key) ȡ 1 �� tableLength - 1 ֮��
//		���κ������� tableLength ���أ���ˣ����ǿ��Լ򵥵ؽ�������Ϊ��
//		h1(key) = key % (tableLength - 2) + 1
// �������� tableLength �� 2 �ķ��ݣ�
//      �� h1(key) ��ȡ 1 �� tableLength - 1֮����κ�������
//
int hash_double(int key, int tableLength)
{
	return key % (tableLength - 2) + 1;
}

//=========================================================
//					���ŵ�ַ��ɢ��
//=========================================================
// �������ÿ��ŵ�ַ����ɢ�б�
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
	
	// ��ʼ�� hash table, ����Ϊ������û�е�ֵ����ֵ��
	for (i = 0; i < tableLength; ++i) {
		table[i] = zeroValue;
	}
	
	for (i = 0; i < dataLength; ++i){
		index = (hashFunc)(data[i], tableLength);
		if (table[index] == zeroValue) {
			table[index] = data[i];
		}
		
		// �г�ͻ
		else {
			// ����˫��ɢ��̽������ͻ
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
			
			// ���ö���̽������ͻ
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
				
				// hash ���������������
				// ��������п�����δ������ֻ�Ƕ���ɢ���㷨�޷�̽�鵽��Щ�յ���
				if (temp == tableLength) {
					assert(0 && "Error: Hash table may be full!\n");
				}
			}
			
			// ��������̽������ͻ��Conflict_Resolution_Linear��
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
				
				// hash ������������
				if (temp == index) {
					assert(0 && "Error: Hash table is full!\n");
				}
			}
		}
	}
	
#ifdef DEBUG_SEARCH
	debug_print("\n��������Ϊ %d �� hash table��\n  ", tableLength);
	for (i = 0; i < tableLength; ++i) {
		debug_print("%d ", table[i]);
	}
	debug_print("\n");
#endif
}

// �ڲ��ÿ��ŵ�ַ����ɢ�б��в���
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
	
	// �������г�ͻ
	else {
		// ����˫��ɢ��̽���������
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
		
		// ���ö���̽���������
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
		
		// ��������̽��������ң�Conflict_Resolution_Linear��
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
//					����ַ��ɢ��
//=========================================================

// ����������������ɢ�б�
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
	
	// ��ʼ����
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
	debug_print("\n��������Ϊ %d �� hash table��\n", tableLength);
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

// ���ٲ�����������ɢ�б�
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

// �ڲ�����������ɢ�б��в���
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

// ��ӡ����
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
//					���Ը��������㷨
//==================================================================

typedef void (*Sort_Function)(int* array, int length);

struct SortFucntionInfo {
	char * name;
	Sort_Function func;
};

SortFucntionInfo sort_function_list[] = {
	{"ֱ�Ӳ�������",				insert_sort},
{"ϣ������",					shell_sort},
	{"ð������",					bubble_sort},
{"ð�������Ż���",			bubble_sort_opt},
	{"��������",					quick_sort},
{"ֱ��ѡ������",				selection_sort},
	{"������",					heap_sort},
{"�ϲ������������϶�·�鲢",	merge_sort},
	{"�ϲ������������·���",		merge_sort_dc},
{"Ͱ/������",				bucket_sort},
	{"��������",					radix_sort},
{"", NULL}
};

// ����ĳ�������㷨
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

// ���Ը��������㷨
//
void test_sort()
{
	for (int i = 0; sort_function_list[i].func != NULL; ++i) {
		printf("\n=== %s ===\n", sort_function_list[i].name);
		test_sort_function(sort_function_list[i].func);
	}
	
	const int length = 11;
	printf("\n=== �������� ===\n");
	int array2[11] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};
	
	print_array(array2, length, " data: ");
	
	counting_sort(array2, length, 100);
	
	print_array(array2, length, " data: ");
}

//==================================================================
//					���Ը��ֲ����㷨
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
	{"˳�����",					test_sequential_search},
{"���ֲ���",					test_binary_search},
	{"�ֿ����",					test_blocking_search},
{"���ŵ�ַ����ϣ/ɢ�в���",	test_open_address_hash_search},
	{"��������ϣ/ɢ�в���",		test_link_hash_search},
{"�������������",			test_binary_tree_search},
	{"", NULL},
};

// ���Ը��ֲ����㷨
//
void test_search()
{
	for (int i = 0; test_search_function_list[i].func != NULL; ++i) {
		printf("\n=== %s ===\n", test_search_function_list[i].name);
		(test_search_function_list[i].func)();
	}
}

// ����˳�����
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

// ���Զ��ֲ���
//
void test_binary_search()
{
	// ���ֲ���Ҫ����������
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

// ���Էֿ����
//
void test_blocking_search()
{
	// �ֿ����Ҫ�����зֿ�����: �鳤Ϊ 3���� 4 ��
	const int length = 11;
	int array[length] = {10, 8, 18, 43, 27, 32, 58, 49, 65, 72, 69};
	
	int key1 = 72;
	int key2 = 55;
	int pos;
	
	// �����ֿ��������鳤Ϊ 3���� 4 �顣
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

// ���Բ��ÿ��ŵ�ַ���Ĺ�ϣ����
// 
void test_open_address_hash_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};
	
	int pos;
	int key1 = 72;
	int key2 = 55;
	
	print_array(array, length, " data: ");
	
	// ���ɱ�� hash ��������
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;	
	
	// ���ɱ��̽�鷽ʽ����
	Conflict_Resolution conflictResolution = Conflict_Resolution_Linear;
	conflictResolution = Conflict_Resolution_Quadratic;
	//conflictResolution = Conflict_Resolution_Double_Hash;
	
	// �������ŵ�ַ��ɢ�б�
	int tableLength = 17;	// ���ڶ���̽��ɢ�з���ɢ�б�ȡ����������Ϊ��
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
	
	// ɾ�����ŵ�ַ��ɢ�б�
	free(hashTable);
	hashTable = NULL;
}

// ���Բ����������Ĺ�ϣ����
//
void test_link_hash_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};
	
	int key1 = 72;
	int key2 = 55;
	int pos;
	
	print_array(array, length, " data: ");
	
	// ���ɱ�� hash ��������
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;		
	
	// ����������ɢ�б�
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
	
	// ����������ɢ�б�
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
	
	// ����ڵ���Ҷ�ӽڵ㣬ֱ��ɾ�����Ѹ��ڵ���Ӧ��������Ϊ NULL
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
	
	// ����ڵ�����Ӳ�Ϊ�գ��Һ���Ϊ��
	else if (NULL != node->leftChild) {
		if (parent->leftChild == node) {
			parent->leftChild = node->leftChild;
		}
		else {
			parent->rightChild = node->leftChild;
		}
		
		free(node);
	}
	
	// ����ڵ���Һ��Ӳ�Ϊ�գ�����Ϊ��
	else if (NULL != node->rightChild) {
		if (parent->leftChild == node) {
			parent->leftChild = node->rightChild;
		}
		else {
			parent->rightChild = node->rightChild;
		}
		
		free(node);
	}
	
	// �ڵ�����Һ��Ӿ���Ϊ��
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
	// �ݹ�ʵ��
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
	// ѭ��ʵ��
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

// ƽ�������(Balanced Binary Tree)
//
void BBT_insert(BSTree* tree, int key)
{
	
}

void BBT_remove(BSTree* tree, int key)
{
	
}

// �����������ݴ���������
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

// ���ٶ�����
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

// ǰ�����
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

// �������
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

// �������
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

// ģ�������д��ڵ�
void disk_write(BTNode* node)
{
	printf("�����д��ڵ�\n");
}

// ģ��Ӵ��̶�ȡ�ڵ�
void disk_read(BTNode** node)
{
	printf("�Ӵ��̶�ȡ�ڵ�\n");
}

// ����δ�ӡ B ��
void BTree_print(BTree tree, int her)
{
	int i;
	BTNode* node = tree;
	
	if (node) {
		printf("�� %d �㣬 %d node : ", her, node->keynum);
		
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
		printf("��Ϊ�ա�\n");
	}
}

// �������Ľڵ������ index �������ӽڵ�ϲ�
// parent ��һ�������ĸ��ڵ�
// node �� tree ���ӱ����±�Ϊ index �ĺ��ӽڵ㣬��������
void BTree_split_child(BTNode* parent, int index, BTNode* node)
{
	assert(parent && node);
	
	int i;
	
	// �����½ڵ㣬�洢 node �к�벿�ֵ�����
	BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
	if (!newNode) {
		printf("Error! out of memory!\n");
		return;
	}
	
	newNode->isLeaf = node->isLeaf;
	newNode->keynum = BTree_T - 1;
	
	// ���� node ��벿�ֹؼ���
	for (i = 0; i < newNode->keynum; ++i){
		newNode->key[i] = node->key[BTree_T + i];
		node->key[BTree_T + i] = 0;
	}
	
	// ��� node ����Ҷ�ӽڵ㣬���� node ��벿�ֵĺ��ӽڵ�
	if (!node->isLeaf) {
		for (i = 0; i < BTree_T; i++) {
			newNode->child[i] = node->child[BTree_T + i];
			node->child[BTree_T + i] = NULL;
		}
	}
	
	// �� node ���ѳ� newNode ֮����������ݼ���
	node->keynum = BTree_T - 1;
	
	// �������ڵ�
	for (i = parent->keynum; i > index; --i) {
		parent->child[i + 1] = parent->child[i];
	}
	
	parent->child[index + 1] = newNode;
	
	for (i = parent->keynum - 1; i >= index; --i) {
		parent->key[i + 1] = parent->key[i];
	}
	
	parent->key[index] = node->key[BTree_T - 1];
	++parent->keynum;
	
	// ��� node �е��к�����
	// ���Բ�������Ϊ��ͨ�� keynum ���Ʒ��ʵ�
	// 	for (i = BTree_T - 1; i < BTree_N; ++i) {
	// 		node->key[i] = 0;
	// 		node->child[i + 1] = NULL;
	// 	}
	
	// д�����
	disk_write(parent);
	disk_write(newNode);
	disk_write(node);
}

void BTree_insert_nonfull(BTNode* node, int key)
{
	assert(node);
	
	int i;
	
	// �ڵ���Ҷ�ӽڵ㣬ֱ�Ӳ���
	if (node->isLeaf) {
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			node->key[i + 1] = node->key[i];
			--i;
		}
		
		node->key[i + 1] = key;
		++node->keynum;
		
		// д�����
		disk_write(node);
	}
	
	// �ڵ����ڲ��ڵ�
	else {
		// ���Ҳ����λ��
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			--i;
		}
		
		++i;
		
		// �Ӵ��̶�ȡ���ӽڵ�
		disk_read(&node->child[i]);
		
		// ����ú��ӽڵ����������ѵ���ֵ
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
	
	// ��Ϊ��
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
		
		// д�����
		disk_write(root);
		
		return;
	}
	
	// �ڵ���������Ҫ���з��ѵ���
	if (root->keynum == BTree_N) {
		// �����½ڵ㵱����
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
	
	// �ڵ�δ�����ڵ�ǰ�ڵ��в��� key
	else {
		BTree_insert_nonfull(root, key);
	}
}


// �� tree �еĽڵ� node ���кϲ����ӽڵ㴦��
// ע�⣺���ӽڵ�� keynum ������Ѵﵽ���ޣ��������� BTree_T - 1
// �� node ������Ϊ index + 1 �ĺ��ӽڵ�ϲ�������Ϊ index �ĺ��ӽڵ��У�
// ���� tree ������Ϊ index  �� key �½����ýڵ��У�������ص� key ��ָ�롣
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
	
	// �ϲ�
	for (i = 0; i < nextChild->keynum; ++i) {
		prevChild->key[prevChild->keynum] = nextChild->key[i];
		prevChild->child[prevChild->keynum + 1] = nextChild->child[i + 1];
		++prevChild->keynum;
	}
	
	// �� node ���Ƴ� key �Լ�ָ���̺��ӽڵ��ָ��
	for (i = index; i < node->keynum - 1; ++i) {
		node->key[i] = node->key[i + 1];
		node->child[i + 1] = node->child[i + 2];
	}
	
	node->key[node->keynum - 1] = 0;
	node->child[node->keynum] = NULL;
	--node->keynum;
	
	// ������ڵ�û�� key �ˣ�ɾ֮���������ڵ����Ϊǰ�̺��ӽڵ㡣
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
	// B-���ı�������֮һ��
	// �Ǹ��ڵ���ڲ��ڵ�Ĺؼ�����Ŀ�������� BTree_T - 1
	
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
		// 1�����ڽڵ���Ҷ�ӽڵ㣬ֱ��ɾ��
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
		
		// 2a�����λ�� key ǰ���ӽڵ�� key ��Ŀ >= BTree_T��
		// �������� key ��ǰ������ǰ���� key ֵ���� key��
		// Ȼ����ǰ�����ں��ӽڵ��еݹ�ɾ��ǰ����
		else if (node->child[index]->keynum >= BTree_T) {
			prevChild = node->child[index];
			prevKey = prevChild->key[prevChild->keynum - 1];
			node->key[index] = prevKey;
			
			BTree_remove(&prevChild, prevKey);
		}
		
		// 2b�����λ�� key ����ӽڵ�� key ��Ŀ >= BTree_T��
		// �������� key �ĺ�̣��ú�̵� key ֵ���� key��
		// Ȼ���ں�����ں��ӽڵ��еݹ�ɾ����̡�
		else if (node->child[index + 1]->keynum >= BTree_T) {
			nextChild = node->child[index + 1];
			nextKey = nextChild->key[0];
			node->key[index] = nextKey;
			
			BTree_remove(&nextChild, nextKey);
		}
		
		// 2c��ǰ���ͺ�̶�ֻ���� BTree_T - 1 ���ڵ㣬
		// �� key �½�ǰ�����ӽڵ㣬������̺��ӽڵ�ϲ���ǰ�����ӽڵ㣬
		// ɾ����̺��ӽڵ㣬�� node ���Ƴ� key ��ָ���̺��ӽڵ��ָ�룬
		// Ȼ����ǰ�����ں��ӽڵ��еݹ�ɾ�� key��
		else if (node->child[index]->keynum == BTree_T - 1
				 && node->child[index + 1]->keynum == BTree_T - 1){
			prevChild = node->child[index];
			
			BTree_merge_child(tree, node, index);
			
			// ��ǰ�����ӽڵ��еݹ�ɾ�� key
			BTree_remove(&prevChild, key);
		}
	}
	
	// 3��key �����ڽڵ� node �У���Ӧ����ĳ������ key ���ӽڵ��С�
	//  key < node->key[index], ���� key Ӧ���ں��ӽڵ� node->child[index] ��
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
			
			// 3a��������ں��ӽڵ����ڵ��ֵܽڵ����нڵ����ٰ��� BTree_t ���ؼ���
			// �� node ��һ���ؼ����½��� child �У��������ֵܽڵ���һ���ڵ�������
			// node �У�Ȼ���� child ���ӽڵ��еݹ�ɾ�� key��
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
				
				// 3b, ������ں��ӽڵ����ڵ��ֵܽڵ㶼ֻ���� BTree_t - 1 ���ؼ��֣�
				// �� child ����һ���ڽڵ�ϲ������� node �е�һ���ؼ����½����ϲ��ڵ��У�
				// ���� node ��ɾ���Ǹ��ؼ��ֺ����ָ�룬�� node �� key Ϊ�գ�ɾ֮������������
				// �������غ��ӽڵ��еݹ�ɾ�� key��
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
	
	// tree ΪҶ�ӽڵ㣬�Ҳ��� key������ʧ�ܷ���
	if (tree->isLeaf) {
		return NULL;
	}
	
	// �ڵ��ڲ���ʧ�ܣ��� tree->key[i - 1]< key < tree->key[i]��
	// ��һ�����ҵĽ��ӦΪ child[i]
	
	// �Ӵ��̶�ȡ�� i �����ӵ�����
	disk_read(&tree->child[i]);
	
	// �ݹ�ؼ����������� tree->child[i]
	return BTree_search(tree->child[i], key, pos);
}

void BTree_create(BTree* tree, const int* data, int length)
{
	assert(tree);
	
	int i;
	
#ifdef DEBUG_TREE
	debug_print("\n ��ʼ���� B- �����ؼ���Ϊ:\n");
	for (i = 0; i < length; i++) {
		printf(" %c ", data[i]);
	}
	debug_print("\n");
#endif
	
	
	for (i = 0; i < length; i++) {
#ifdef DEBUG_TREE
		debug_print("\n����ؼ��� %c:\n", data[i]);
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
		printf("�� %d �㣬 %d(%c)\n",
			   her, node->key, node->color == RB_Black ? 'B' : 'R');
		
		if (node->leftChild != &RBNode_Nil) {
			RBTree_print(node->leftChild, her + 1);
		}
		
		if (node->rightChild != &RBNode_Nil) {
			RBTree_print(node->rightChild, her + 1);
		}
	}
}

// ��С�ؼ���Ԫ��
RBNode* RBTree_minimum(RBNode* node)
{
	assert(node);
	
	RBNode* temp = node;
	while (temp->leftChild != &RBNode_Nil) {
		temp = temp->leftChild;
	}
	
	return temp;
}


// ���ؼ���Ԫ��
RBNode* RBTree_maximum(RBNode* node)
{
	assert(node);
	
	RBNode* temp = node;
	while (temp->rightChild != &RBNode_Nil) {
		temp = temp->rightChild;
	}
	
	return temp;
}

// ��������е�ǰ��
RBNode* RBTree_predecessor(RBNode* node)
{
	assert(node);
	
	RBNode* child = node->leftChild;
	
	// û�����ӣ���������
	if (child == &RBNode_Nil) {
		return node;
	}
	
	// ֻ�����ӣ�����������ֱ��ǰ��
	else if (child->rightChild == &RBNode_Nil) {
		return child->leftChild;
	}
	
	// ���Һ��Ӿ��У����Һ�����������Ԫ��Ϊ��ֱ��ǰ��
	else {
		return RBTree_maximum(child->rightChild);
	}
}

// ��������еĺ��
RBNode* RBTree_successor(RBNode* node)
{
	// ���Һ��ӣ����Һ���������С��Ԫ��Ϊ��ֱ�Ӻ��
	if (node->rightChild != &RBNode_Nil) {
		return RBTree_minimum(node->rightChild);
	}
	
	// û���Һ��ӣ������ҵ��ĵ�һ�����֧�ڵ�Ϊ��ֱ�Ӻ�̣�
	// �� node Ϊ��ֱ�Ӻ�̵��������е����Ԫ�ء�
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

// ����
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

// ����
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

// �������
void RBTree_insert_fixup(RBTree* tree, RBNode* node)
{
	assert(tree && node);
	
	RBNode* parent = NULL;
	RBNode* uncle = NULL;
	RBNode* grand = NULL;
	RBNode* temp = NULL;
	
	parent = node->parent;
	while (parent->color == RB_Red) {
		// ���ݺ�������ʣ��Լ� node �ĸ��׵���ɫΪ��ɫ��
		// ���Կ϶� node ���游�ڵ�һ������
		grand = parent->parent;
		
		// ȷ���常�ڵ�
		if (parent == grand->leftChild) {
			uncle = grand->rightChild;
			
			// case 1: �常�ڵ�Ϊ��ɫ
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
			
			// case 2, case 3���常�ڵ�Ϊ��ɫ
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
				// �� case 2 װ���� case 3
				// ע�⣺ת���� case 3֮�� parent Ϊcase 2�е� node��
				// node Ϊ case 2 �е� parent
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
			// �����������Գ�
			uncle = grand->leftChild;
			
			if (uncle->color == RB_Red) {
				parent->color = RB_Black;
				uncle->color = RB_Black;
				grand->color = RB_Red;
				node = grand;
				parent = node->parent;
			}
			
			else {
				// �� case 2 װ���� case 3
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

// ���ڵ� node ������ tree �ڣ�Ȼ�� node ��ɫΪ��ɫ����ʱ�������ܲ���
// �����������ʣ���˵��� RBTree_insert_fixup ���Խڵ�������ɫ������
void RBTree_insert(RBTree* tree, RBNode* node)
{
	assert(tree && node);
	
	RBNode* parent = &RBNode_Nil;
	RBNode* temp = *tree;
	
	// �������һ���������в����ʵ���λ�ò���
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
	
	// ��Ϊ��
	if (parent == &RBNode_Nil) {
		*tree = node;
	}
	else if (node->key < parent->key) {
		parent->leftChild = node;
	}
	else {
		parent->rightChild = node;
	}
	
	// Ϊ�ڵ���ɫ
	node->leftChild = &RBNode_Nil;
	node->rightChild = &RBNode_Nil;
	node->color = RB_Red;
	
	// ������ʹ֮������������
	RBTree_insert_fixup(tree, node);
}

// ɾ������
void RBTree_delete_fixup(RBTree* tree, RBNode* node)
{
	RBNode* brother = NULL;
	RBNode* parent = NULL;
	
	while (node != *tree && node->color == RB_Black) {
		parent = node->parent;
		
		// ȷ���ֵܽڵ�
		if (node == parent->leftChild) {
			brother = parent->rightChild;
			
			// case 1: �ֵܽڵ�Ϊ��ɫ
			if (brother->color == RB_Red) {
				brother->color = RB_Black;
				parent->color = RB_Red;
				
				RBTree_left_rotate(tree, parent);
				
				brother = node->parent->rightChild;
			}
			
			// case 2: �ֵܽڵ�������Ӿ�Ϊ��ɫ
			if (brother->leftChild->color == RB_Black
				&& brother->rightChild->color == RB_Black) {
				brother->color = RB_Red;
				node = parent;
			}
			
			else {
				// case 3: �ֵܽڵ������Ϊ��ɫ���Һ���Ϊ��ɫ
				if (brother->rightChild->color == RB_Black) {
					brother->leftChild->color = RB_Black;
					brother->color = RB_Red;
					
					RBTree_right_rotate(tree, brother);
					
					brother = node->parent->rightChild;
				}
				
				// case 4:�ֵܽڵ���Һ���Ϊ��ɫ
				brother->color = parent->color;
				parent->color = RB_Black;
				brother->rightChild->color = RB_Black;
				
				RBTree_left_rotate(tree, parent);
				
				node = *tree;
			}
		}
		else {
			brother = parent->leftChild;
			
			// case 1: �ֵܽڵ�Ϊ��ɫ
			if (brother->color == RB_Red) {
				brother->color = RB_Black;
				parent->color = RB_Red;
				
				RBTree_right_rotate(tree, parent);
				
				brother = parent->leftChild;
			}
			
			// case 2: �ֵܽڵ�������Ӿ�Ϊ��ɫ
			if (brother->leftChild->color == RB_Black
				&& brother->rightChild->color == RB_Black) {
				brother->color = RB_Red;
				node = parent;
			}
			
			else {
				// case 3: �ֵܽڵ������Ϊ��ɫ���Һ���Ϊ��ɫ
				if (brother->rightChild->color == RB_Black) {
					brother->leftChild->color = RB_Black;
					brother->color = RB_Red;
					
					RBTree_left_rotate(tree, brother);
					
					brother = parent->rightChild;
				}
				
				// case 4:�ֵܽڵ���Һ���Ϊ��ɫ
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

// ɾ��
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
//					���Զ��������
//==================================================================

void test_binary_tree_search()
{
	// ���������Ҫ���¼�Ĺؼ���Ψһ�����Բ�������ͬ�ļ�¼
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 8, 72, 27, 42, 18, 58, 91};
	
	int key1 = 72;
	int key2 = 55;
	
	print_array(array, length, " data: ");
	
	BSTree tree = NULL;
	BSTNode* node = NULL;
	
	// ����������
	BST_create(&tree, array, length);
	if (!tree) {
		printf("Failed to create binary search tree!\n");
		return;
	}
	
	// ����
	node = BST_search(tree, key1);
	printf("  %s %d in binary search tree.\n",
		   (NULL == node) ? "Could not find" : "Yeah! Found", key1);
	
	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		   (NULL == node) ? "Could not find" : "Found", key2);
	
	// ����ڵ�
	printf(" Insert %d to binary search tree.\n", key2);
	BST_insert(&tree, key2);
	
	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		   (NULL == node) ? "Could not find" : "Yeah! Found", key2);
	
	// ɾ���ڵ�
	key2 = 27;
	printf(" Remove %d from binary search tree.\n", key2);
	BST_remove(&tree, key2);
	
	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		   (NULL == node) ? "Could not find" : "Yeah! Found", key2);
	
	// ���ٶ�����
	BST_destory(&tree);
	
	assert(NULL == tree);
}

//==================================================================
//					���� B ��
//==================================================================
void test_BTree_search(BTree tree, int key)
{
	int pos = -1;
	BTNode*	node = BTree_search(tree, key, &pos);
	if (node) {
		printf("��%s�ڵ㣨���� %d ���ؼ��֣����ҵ��ؼ��� %c��������Ϊ %d\n",
			   node->isLeaf ? "Ҷ��" : "��Ҷ��",
			   node->keynum, key, pos);
	}
	else {
		printf("�������Ҳ����ؼ��� %c\n", key);
	}
}

void test_BTree_remove(BTree* tree, int key)
{
	printf("\n�Ƴ��ؼ��� %c \n", key);
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
	
	// ����
	BTree_create(&tree, array, length);
	
	printf("\n=== ���� B �� ===\n");
	BTree_print(tree,1);
	printf("\n");
	
	// ����
	test_BTree_search(tree, key1);
	printf("\n");
	test_BTree_search(tree, key2);
	
	// ����ؼ���
	printf("\n����ؼ��� %c \n", key2);
	BTree_insert(&tree, key2);
	BTree_print(tree,1);
	printf("\n");
	
	test_BTree_search(tree, key2);
	
	// �Ƴ��ؼ���
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
	
	// ����
	BTree_destory(&tree);
}

//==================================================================
//					���Ժ����
//==================================================================
void test_redblacktree_delete(RBTree* tree, int key)
{
	RBNode* node = RBTree_search(*tree, key);
	assert(node != RBTree_nil());
	
	printf("\nɾ���ڵ� %d \n", node->key);
	
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
	
	// ����ڵ�������
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
	
	// �������
	node = (RBNode*)malloc(sizeof(RBNode));
	node->key = 21;
	
	printf("\n����ڵ� %d\n", node->key);
	
	RBTree_insert(&tree, node);
	RBTree_print(tree,1);
	
	// ���Ҳ���
	i = 6;
	node = RBTree_search(tree, i);
	
	if (node != RBTree_nil()) {
		printf("\n�ں�������ҵ��ڵ� %d\n", node->key);
	}
	else {
		printf("\n�ں�������Ҳ����ڵ� %d\n", i);
	}
	
	// ɾ������
	// 
	i = 4;// ȡֵ 1, 2, 3, 4���ֱ��Ӧ case 1, 2, 3, 4
	
	switch (i)
	{
	case 1:	// �ֵ�Ϊ��ɫ
		test_redblacktree_delete(&tree, 3);
		break;
		
	case 2:	// �ֵ�Ϊ��ɫ�����ֵܵ������Ӿ�Ϊ��ɫ
		test_redblacktree_delete(&tree, 12);
		break;
		
	case 3:	// �ֵ�Ϊ��ɫ�����ֵܵ�����Ϊ��ɫ���Һ��Ӿ�Ϊ��ɫ
		test_redblacktree_delete(&tree, 19);
		break;
		
	case 4:	// �ֵ�Ϊ��ɫ�����ֵܵ��Һ���Ϊ��ɫ
		test_redblacktree_delete(&tree, 9);
		break;
	}
	
	test_redblacktree_delete(&tree, 21);
	
	// ɾ����
	for (i = 0; i < length; i++) {
		node = RBTree_search(tree, array[i]);
		
		if (node != RBTree_nil()) {
			printf("ɾ�� %d\n", node->key);
			node = RBTree_delete(&tree, node);
			free(node);
		}
	}
	
	assert(tree == RBTree_nil());
}

typedef void (*Test_Function)();

Test_Function test_function[] = {
		test_sort,		// ���������㷨
		test_search,		// ���Բ����㷨
		test_btree,			// ���� B ��
		test_redblacktree,	// ���Ժ����
		nullptr
};

int main(int argc, const char* argv[])
{
	for (int i = 0; test_function[i] != nullptr; i++) {
		test_function[i](); system("pause");
	}
	
	printf("\n���Խ���\n");
	system("pause");
	return 0;
}
