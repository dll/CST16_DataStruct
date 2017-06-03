#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX         100   // 矩阵最大容量
#define INF         65535  // 最大值65535
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

typedef char VType; //设顶点为字符类型
typedef int AdjType; //设邻接边权值为整数类型

// 图的邻接矩阵存储
typedef struct _graph
{
	VType vexs[MAX];       // 顶点集合
	int vexnum;           // 顶点数
	int edgnum;           // 边数
	AdjType matrix[MAX][MAX]; // 邻接矩阵
}Graph, *PGraph;

// 边的结构体
typedef struct _EdgeData
{
	VType start; // 边的起点
	VType end;   // 边的终点
	AdjType weight; // 边的权重
}EData;

// 图的邻接表存储（边集）
typedef struct node    
{    
	AdjType  adjvex;    
	AdjType  weight;    
	struct node *nextedge;    
}EdgeNode;   

//顶点集   
typedef struct  
{    
	VType    data;  
	int      id;    
	EdgeNode  *firstEdge;    
}VexNode;     

/*
* 返回ch在matrix矩阵中的位置
*/
static int get_position(Graph G, char ch)
{
	int i;
	for(i=0; i<G.vexnum; i++)
		if(G.vexs[i]==ch)
		return i;
	return -1;
}

/*
* 读取一个输入字符
*/
static char read_char()
{
	char ch;
	do {
		ch = getchar();
	} while(!isLetter(ch));
	
	return ch;
}

/*
* 创建图(手工输入，我不喜欢的)
*/
Graph* create_graph(char *filename)
{
	int c1, c2;
	int c3;
	int v, e;
	int i, j, weight, p1, p2;
	Graph* pG;
	
	// 输入"顶点数"和"边数"
	//printf("请输入顶点的数目:\n ");
	FILE *pf=fopen(filename, "r");
	fscanf(pf,"%d", &v);
	//printf("请输入边的数目: \n");
	fscanf(pf,"%d", &e);
	if ( v < 1 || e < 1 || (e > (v * (v-1))))
	{
		printf("输入有误！！!\n");
		return NULL;
	}
	
	if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
		return NULL;
	memset(pG, 0, sizeof(Graph));						//初始化
	
	// 初始化"顶点数"和"边数"
	pG->vexnum = v;
	pG->edgnum = e;
	// 初始化"顶点"
	for (i = 0; i < pG->vexnum; i++)
	{
		//printf("vertex(%d): ", i);
		//pG->vexs[i] = read_char();
		fscanf(pf,"%d",&c3);
		pG->vexs[i]= (char)c3;
	}
	
	// 1. 初始化"边"的权值
	for (i = 0; i < pG->vexnum; i++)
	{
		for (j = 0; j < pG->vexnum; j++)
		{
			if (i==j)
				pG->matrix[i][j] = 0;
			else
				pG->matrix[i][j] = INF;
		}
	}
	// 2. 初始化"边"的权值: 根据用户的输入进行初始化
	for (i = 0; i < pG->edgnum; i++)
	{
		// 读取边的起始顶点，结束顶点，权值
		//printf("edge(%d):", i);
		//c1 = read_char();
		//c2 = read_char();
		//scanf("%d", &weight);
		fscanf(pf,"%d%d%d",&c1, &c2, &weight);
		
		p1 = get_position(*pG, (char)c1);
		p2 = get_position(*pG, (char)c2);
		if (p1==-1 || p2==-1)
		{
			printf("输入有误!!!\n");
			free(pG);
			return NULL;
		}
		
		pG->matrix[p1][p2] = weight;
		//pG->matrix[p2][p1] = weight;
	}
	fclose(pf);
	return pG;
}

/*
* 创建图(用已提供的矩阵，你会使用文件吗？)
*/
Graph* create_example_graph()
{
	char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	int matrix[][7] = {
				/*A*//*B*//*C*//*D*//*E*//*F*//*G*/
		/*A*/ {   0,  12, INF, INF, INF,  16,  14},
		/*B*/ {  12,   0,  10, INF, INF,   7, INF},
		/*C*/ { INF,  10,   0,   3,   5,   6, INF},
		/*D*/ { INF, INF,   3,   0,   4, INF, INF},
		/*E*/ { INF, INF,   5,   4,   0,   2,   8},
		/*F*/ {  16,   7,   6, INF,   2,   0,   9},
		/*G*/ {  14, INF, INF, INF,   8,   9,   0}};
	int vlen = LENGTH(vexs);
	int i, j;
	Graph* pG;
	
	// 输入"顶点数"和"边数"
	if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
		return NULL;
	memset(pG, 0, sizeof(Graph));//内存拷贝，还初始化0，快！
	
	// 初始化"顶点数"
	pG->vexnum = vlen;
	// 初始化"顶点"
	for (i = 0; i < pG->vexnum; i++)
		pG->vexs[i] = vexs[i];
	
	// 初始化"边"
	for (i = 0; i < pG->vexnum; i++)
		for (j = 0; j < pG->vexnum; j++)
			pG->matrix[i][j] = matrix[i][j];
			
			// 统计边的数目
			for (i = 0; i < pG->vexnum; i++)
				for (j = 0; j < pG->vexnum; j++)
					if (i!=j && pG->matrix[i][j]!=INF)
						pG->edgnum++;
			pG->edgnum /= 2;
			
			return pG;
}

/*
* 返回顶点v的第一个邻接顶点的索引，失败则返回-1
*/
static int first_vertex(Graph G, int v)
{
	int i;
	
	if (v<0 || v>(G.vexnum-1))
		return -1;
	
	for (i = 0; i < G.vexnum; i++)
		if (G.matrix[v][i]!=0 && G.matrix[v][i]!=INF)
			return i;
	
	return -1;
}

/*
* 返回顶点v相对于w的下一个邻接顶点的索引，失败则返回-1
*/
static int next_vertix(Graph G, int v, int w)
{
	int i;
	
	if (v<0 || v>(G.vexnum-1) || w<0 || w>(G.vexnum-1))
		return -1;
	
	for (i = w + 1; i < G.vexnum; i++)
		if (G.matrix[v][i]!=0 && G.matrix[v][i]!=INF)
			return i;
	
	return -1;
}

/*
* 深度优先搜索遍历图的递归实现
*/
static void DFS(Graph G, int i, int *visited)
{                                   
	int w; 
	
	visited[i] = 1;
	printf("%c ", G.vexs[i]);
	// 遍历该顶点的所有邻接顶点。若是没有访问过，那么继续往下走
	for (w = first_vertex(G, i); w >= 0; w = next_vertix(G, i, w))
	{
		if (!visited[w])
			DFS(G, w, visited);
	}
	
}

/*
* 深度优先搜索遍历图
*/
void DFSTraverse(Graph G)
{
	int i;
	int visited[MAX];       // 顶点访问标记
	
	// 初始化所有顶点都没有被访问
	for (i = 0; i < G.vexnum; i++)
		visited[i] = 0;
	
	printf("DFS: ");
	for (i = 0; i < G.vexnum; i++)
	{
		//printf("\n== LOOP(%d)\n", i);
		if (!visited[i])
			DFS(G, i, visited);
	}
	printf("\n");
}

/*
* 广度优先搜索（类似于树的层次遍历）
*/
void BFS(Graph G)
{
	int head = 0;
	int rear = 0;
	int queue[MAX];     // 辅组队列
	int visited[MAX];   // 顶点访问标记
	int i, j, k;
	
	for (i = 0; i < G.vexnum; i++)
		visited[i] = 0;
	
	printf("BFS: ");
	for (i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			printf("%c ", G.vexs[i]);
			queue[rear++] = i;  // 入队列
		}
		while (head != rear) 
		{
			j = queue[head++];  // 出队列
			for (k = first_vertex(G, j); k >= 0; k = next_vertix(G, j, k)) //k是为访问的邻接顶点
			{
				if (!visited[k])
				{
					visited[k] = 1;
					printf("%c ", G.vexs[k]);
					queue[rear++] = k;
				}
			}
		}
	}
	printf("\n");
}

/*
* 打印矩阵队列图
*/
void print_graph(Graph G)
{
	int i,j;
	
	printf("Martix Graph:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
			printf("%10d ", G.matrix[i][j]);
		printf("\n");
	}
}

/*
* prim最小生成树
*
* 参数说明：
*       G -- 邻接矩阵图
*   start -- 从图中的第start个元素开始，生成最小树
*/
void prim(Graph G, int start)
{
	int min,i,j,k,m,n,sum;
	int index=0;         // prim最小树的索引，即prims数组的索引
	char prims[MAX];     // prim最小树的结果数组
	int weights[MAX];    // 顶点间边的权值
	
	// prim最小生成树中第一个数是"图中第start个顶点"，因为是从start开始的。
	prims[index++] = G.vexs[start];
	
	// 初始化"顶点的权值数组"，
	// 将每个顶点的权值初始化为"第start个顶点"到"该顶点"的权值。
	for (i = 0; i < G.vexnum; i++ )
		weights[i] = G.matrix[start][i];
		// 将第start个顶点的权值初始化为0。
		// 可以理解为"第start个顶点到它自身的距离为0"。
		weights[start] = 0;
		
		for (i = 0; i < G.vexnum; i++)
		{
			// 由于从start开始的，因此不需要再对第start个顶点进行处理。
			if(start == i)
				continue;
			
			j = 0;
			k = 0;
			min = INF;
			// 在未被加入到最小生成树的顶点中，找出权值最小的顶点。
			while (j < G.vexnum)
			{
				// 若weights[j]=0，意味着"第j个节点已经被排序过"(或者说已经加入了最小生成树中)。
				if (weights[j] != 0 && weights[j] < min)
				{
					min = weights[j];
					k = j;
				}
				j++;
			}
			
			// 经过上面的处理后，在未被加入到最小生成树的顶点中，权值最小的顶点是第k个顶点。
			// 将第k个顶点加入到最小生成树的结果数组中
			prims[index++] = G.vexs[k];
			// 将"第k个顶点的权值"标记为0，意味着第k个顶点已经排序过了(或者说已经加入了最小树结果中)。
			weights[k] = 0;
			// 当第k个顶点被加入到最小生成树的结果数组中之后，更新其它顶点的权值。
			for (j = 0 ; j < G.vexnum; j++)
			{
				// 当第j个节点没有被处理，并且需要更新时才被更新。
				if (weights[j] != 0 && G.matrix[k][j] < weights[j])
					weights[j] = G.matrix[k][j];
			}
		}
		
		// 计算最小生成树的权值
		sum = 0;
		for (i = 1; i < index; i++)
		{
			min = INF;
			// 获取prims[i]在G中的位置
			n = get_position(G, prims[i]);
			// 在vexs[0...i]中，找出到j的权值最小的顶点。
			for (j = 0; j < i; j++)
			{
				m = get_position(G, prims[j]);
				if (G.matrix[m][n]<min)
					min = G.matrix[m][n];
			}
			sum += min;
		}
		// 打印最小生成树
		printf("PrimMST(%c)=%d: ", G.vexs[start], sum);
		for (i = 0; i < index; i++)
			printf("%c ", prims[i]);
		printf("\n");
}

/* 
* 获取图中的边
*/
EData* get_edges(Graph G)
{
	int i,j;
	int index=0;
	EData *edges;
	
	edges = (EData*)malloc(G.edgnum*sizeof(EData));
	for (i=0;i < G.vexnum;i++)
	{
		for (j=i+1;j < G.vexnum;j++)
		{
			if (G.matrix[i][j]!=INF)
			{
				edges[index].start  = G.vexs[i];
				edges[index].end    = G.vexs[j];
				edges[index].weight = G.matrix[i][j];
				index++;
			}
		}
	}
	return edges;
}

/* 
* 对边按照权值大小进行排序(由小到大)
*/
void sorted_edges(EData* edges, int elen)
{
	int i,j;
	for (i=0; i<elen; i++)
	{
		for (j=i+1; j<elen; j++)
		{
			if (edges[i].weight > edges[j].weight)
			{
				// 交换"第i条边"和"第j条边"
				EData tmp = edges[i];
				edges[i] = edges[j];
				edges[j] = tmp;
			}
		}
	}
}

/*
* 获取i的终点
*/
int get_end(int vends[], int i)
{
	while (vends[i] != 0)
		i = vends[i];
	return i;
}

/*
* 克鲁斯卡尔（Kruskal)最小生成树
*/
void kruskal(Graph G)
{
	int i,m,n,p1,p2;
	int length;
	int index = 0;          // rets数组的索引
	int vends[MAX]={0};     // 用于保存"已有最小生成树"中每个顶点在该最小树中的终点。
	EData rets[MAX];        // 结果数组，保存kruskal最小生成树的边
	EData *edges;           // 图对应的所有边
	
	// 获取"图中所有的边"
	edges = get_edges(G);
	// 将边按照"权"的大小进行排序(从小到大)
	sorted_edges(edges, G.edgnum);
	
	for (i=0; i<G.edgnum; i++)
	{
		p1 = get_position(G, edges[i].start);   // 获取第i条边的"起点"的序号
		p2 = get_position(G, edges[i].end);     // 获取第i条边的"终点"的序号
		
		m = get_end(vends, p1);                 // 获取p1在"已有的最小生成树"中的终点
		n = get_end(vends, p2);                 // 获取p2在"已有的最小生成树"中的终点
		// 如果m!=n，意味着"边i"与"已经添加到最小生成树中的顶点"没有形成环路
		if (m != n)
		{
			vends[m] = n;                       // 设置m在"已有的最小生成树"中的终点为n
			rets[index++] = edges[i];           // 保存结果
		}
	}
	free(edges);
	
	// 统计并打印"kruskal最小生成树"的信息
	length = 0;
	for (i = 0; i < index; i++)
		length += rets[i].weight;
	printf("KruskalMST=%d: ", length);
	for (i = 0; i < index; i++)
		printf("(%c,%c) ", rets[i].start, rets[i].end);
	printf("\n");
}

/*
* Dijkstra最短路径。
* 即，统计图(G)中"顶点vs"到其它各个顶点的最短路径。
*
* 参数说明：
*        G -- 图
*       vs -- 起始顶点(start vertex)。即计算"顶点vs"到其它顶点的最短路径。
*     prev -- 前驱顶点数组。即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
*     dist -- 长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
*/
void dijkstra(Graph G, int vs, int prev[], int dist[])
{
	int i,j,k;
	int min;
	int tmp;
	int flag[MAX];      // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。
	
	// 初始化
	for (i = 0; i < G.vexnum; i++)
	{
		flag[i] = 0;              // 顶点i的最短路径还没获取到。
		prev[i] = 0;              // 顶点i的前驱顶点为0。
		dist[i] = G.matrix[vs][i];// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
	}
	
	// 对"顶点vs"自身进行初始化
	flag[vs] = 1;
	dist[vs] = 0;
	
	// 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
	for (i = 1; i < G.vexnum; i++)
	{
		// 寻找当前最小的路径；
		// 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
		min = INF;
		for (j = 0; j < G.vexnum; j++)
		{
			if (flag[j]==0 && dist[j]<min)
			{
				min = dist[j];
				k = j;
			}
		}
		// 标记"顶点k"为已经获取到最短路径
		flag[k] = 1;
		
		// 修正当前最短路径和前驱顶点
		// 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
		for (j = 0; j < G.vexnum; j++)
		{
			tmp = (G.matrix[k][j]==INF ? INF : (min + G.matrix[k][j])); // 防止溢出
			if (flag[j] == 0 && (tmp  < dist[j]) )
			{
				dist[j] = tmp;
				prev[j] = k;
			}
		}
	}
	
	// 打印dijkstra最短路径的结果
	printf("dijkstraSP(%c): \n", G.vexs[vs]);
	for (i = 0; i < G.vexnum; i++)
		printf("  shortest(%c, %c)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);
}

void TestDijkstra()
{
	int prev[MAX] = {0};
	int dist[MAX] = {0};
	Graph* pG;
	
	// 自定义"图"(输入矩阵队列)
	//pG = create_graph();
	// 采用已有的"图"
	pG = create_example_graph();
//	pG = create_graph("P196_图6.22_G6.txt");
	print_graph(*pG);       // 打印图
	DFSTraverse(*pG);       // 深度优先遍历
	BFS(*pG);               // 广度优先遍历
	prim(*pG, 0);           // prim算法生成最小生成树
	kruskal(*pG);           // kruskal算法生成最小生成树
	// dijkstra算法获取"第7个顶点"到其它各个顶点的最短距离
	dijkstra(*pG, 6, prev, dist);
}

//弗洛伊德算法Floyd代码
//求网G（用邻接矩阵表示）中任意两点间最短路径 
//D[][]是最短路径长度矩阵，path[][]最短路径标志矩阵 
void Floyd(Graph * G,int path[][MAX],int D[][MAX],int n)
{ 
	int i,j,k;
	//初始化
	for(i=0;i<n;i++)
	{ 
		for(j=0;j<n;j++)
		{
			if(G->matrix[i][j]<INF)
			{
				path[i][j]=j;
			}
			else
			{
				path[i][j]=-1;
			}
			D[i][j]=G->matrix[i][j];
		}
	} 
	
	//进行n次搜索
	for(k=0;k<n;k++)
	{ 
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(D[i][j] > D[i][k] + D[k][j])
				{
					D[i][j]=D[i][k]+D[k][j];			//取小者 
					path[i][j]=path[i][k];				//改Vi的后继 
				}
			}
		}
	}
}


void TestFloyd()
{
	int i,j,k,v=0,n=0;								//v为起点，n为顶点个数 

	Graph *pG= create_example_graph();
//	Graph *pG= create_graph("P201_图6.24_G7.txt");
	n=pG->vexnum;
	AdjType path[MAX][MAX];//v到各顶点的最短路径向量
	AdjType D[MAX][MAX];//v到各顶点最短路径长度向量
	
	Floyd(pG,path,D,n);
	//输出每对顶点间最短路径长度及最短路径
	for(i=0;i<n;i++)
	{					
		for(j=0;j<n;j++)
		{
			printf("V%d-V%d的最短长度: ",i,j); 
			printf("%d\t",D[i][j]);						//输出Vi到Vj的最短路径长度
			k=path[i][j];								//取路径上Vi的后续Vk
			if(k==-1)
			{
				printf("V%d-V%d之间没有路径\n",i,j);//路径不存在 
			}
			else
			{
				printf("最短路径为:"); 
				printf("(边%d",i);					//输出Vi的序号i
				//k不等于路径终点j时
				while(k!=j)
				{						 
					printf(",V%d",k);				//输出k
					k=path[k][j];					//求路径上下一顶点序号 
				}
				printf("，边%d)",j);			//输出路径终点序号 
			}
			printf("\n");
		} 
		if(i==n/2){//分两次打印输出，清屏便于查看！
			system("pause");
			system("cls");
		}
	}
}
/*
将邻接矩阵图转成邻接链表存储
Graph-->VexNode
*/
void CreateGraph(Graph *pG,VexNode* Graph,int vexnumber,int arcnumber)  
{  
	int i = 0, j = 0, k = 0;
	int begin,end,weight; 
	EdgeNode *p; 
	//初始化
	for(i=0;i<vexnumber;i++) 
	{    
		Graph[i].id =0;  
		Graph[i].firstEdge =NULL;  
	}  
	// 图中的各个顶点的值  
	for(i=0;i<vexnumber;i++)
		Graph[i].data=pG->vexs[i];
 
	//图中弧的起始点及权值:其格式为<起点,终点,权值>
	EData *edges=get_edges(*pG);
	for(k=0;k<arcnumber;k++)
	{  
		begin=edges[k].start-'A'+1;//字符转成整形，且从1开始
		end=edges[k].end-'A'+1;
		weight=edges[k].weight;
		//形成链表
		p=(EdgeNode*)malloc(sizeof(EdgeNode));  
		p->adjvex =end-1;  
		p->weight =weight;  
		Graph[end-1].id ++;
		p->nextedge =Graph[begin-1].firstEdge ;  
		Graph[begin-1].firstEdge =p;  
	}  
}
/*
寻找关键路径AOE的CMP
*/
int SearchMapPath(VexNode* Graph,int vexnumber,int arcnumber)  
{  
	int totaltime=0;
	int m=0;
	int i,j,k,t; 
	char sv[100];
	int front,rear; 
	int *topology_queue,*vl,*ve,*el,*ee;
	front=rear=-1; 
	t=0;
	topology_queue=(int*)malloc(vexnumber*sizeof(int));    
	vl=(int*)malloc(vexnumber*sizeof(int));               
	ve=(int*)malloc(vexnumber*sizeof(int));               
	el=(int*)malloc(arcnumber*sizeof(int));           
	ee=(int*)malloc(arcnumber*sizeof(int));    
	EdgeNode *p;   
	for(i=0;i<vexnumber;i++) 
		ve[i]=0;  
	for(i=0;i<vexnumber;i++)
	{  
		if(Graph[i].id==0)  
			topology_queue[++rear]=i; 
		m++;
	}
	while(front!=rear)
	{  
		front++;  
		j=topology_queue[front]; 
		m++;
		p=Graph[j].firstEdge ;  
		while(p)
		{  
			k=p->adjvex ;  
			Graph[k].id --;  
			if(ve[j]+p->weight >ve[k])  
				ve[k]=ve[j]+p->weight ;  
			if(Graph[k].id ==0) 
				topology_queue[++rear]=k;  
			p=p->nextedge ;  
		}  
	}  
	if(m<vexnumber)
	{
		printf("\n本程序所建立的图有回路不可计算出关键路径\n");
		printf("将退出本程序\n");
		return 0;
	}
	totaltime=ve[vexnumber-1];  
	for(i=0;i<vexnumber;i++)  
		vl[i]=totaltime;
	for(i=vexnumber-2;i>=0;i--)
	{  
		j=topology_queue[i];
		p=Graph[j].firstEdge;  
		while(p)
		{  
			k=p->adjvex ;  
			if((vl[k]-p->weight )<vl[j])  
				vl[j]=vl[k]-p->weight;  
			p=p->nextedge;  
		}  
	}   
	printf("| 起点 | 终点 | 最早开始时间 | 最迟开始时间 | 差值 | 是否为关键路径 \n");  
	i=0; 
	for(j=0;j<vexnumber;j++)     
	{  
		p=Graph[j].firstEdge;  
		while(p)
		{  
			k=p->adjvex;  
			ee[++i]=ve[j];  
			el[i]=vl[k]-p->weight;  
			printf("| %4c | %4c | %12d | %12d | %4d |",Graph[j].data ,Graph[k].data ,ee[i],el[i],el[i]-ee[i]);  
			if(el[i]==ee[i]) 
			{ 
				printf(" 此弧为关键活动 "); 
				sv[t]=Graph[j].data;t++;
			}
			printf("\n"); 
			p=p->nextedge;  
		}
	}  
	printf("关键路径节点为：");
	sv[t]=Graph[vexnumber-1].data;
	for(i=0;i<=t;i++)
	{
		printf("%c",sv[i]);
		if(sv[i]!=Graph[vexnumber-1].data)
			printf("--->");
	}
	printf("\n");
	printf("关键路径长度为：%d个单位时间\n",totaltime); 
	return 1;  
}  
void TestAOE( )  
{  
	Graph*pG= create_example_graph();
//	Graph*pG= create_graph("P206_图6.28_G8.txt");
	VexNode* Graph=(VexNode*)malloc(pG->vexnum*sizeof(VexNode)); 
	CreateGraph(pG,Graph,pG->vexnum,pG->edgnum);  
	SearchMapPath(Graph,pG->vexnum,pG->edgnum);
}
int main(void){
	TestDijkstra();
	system("pause");
	system("cls");
	TestFloyd();
	system("pause");
	system("cls");
	TestAOE();
	return 0;
}
