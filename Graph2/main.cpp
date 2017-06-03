#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX         100   // �����������
#define INF         65535  // ���ֵ65535
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

typedef char VType; //�趥��Ϊ�ַ�����
typedef int AdjType; //���ڽӱ�ȨֵΪ��������

// ͼ���ڽӾ���洢
typedef struct _graph
{
	VType vexs[MAX];       // ���㼯��
	int vexnum;           // ������
	int edgnum;           // ����
	AdjType matrix[MAX][MAX]; // �ڽӾ���
}Graph, *PGraph;

// �ߵĽṹ��
typedef struct _EdgeData
{
	VType start; // �ߵ����
	VType end;   // �ߵ��յ�
	AdjType weight; // �ߵ�Ȩ��
}EData;

// ͼ���ڽӱ�洢���߼���
typedef struct node    
{    
	AdjType  adjvex;    
	AdjType  weight;    
	struct node *nextedge;    
}EdgeNode;   

//���㼯   
typedef struct  
{    
	VType    data;  
	int      id;    
	EdgeNode  *firstEdge;    
}VexNode;     

/*
* ����ch��matrix�����е�λ��
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
* ��ȡһ�������ַ�
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
* ����ͼ(�ֹ����룬�Ҳ�ϲ����)
*/
Graph* create_graph(char *filename)
{
	int c1, c2;
	int c3;
	int v, e;
	int i, j, weight, p1, p2;
	Graph* pG;
	
	// ����"������"��"����"
	//printf("�����붥�����Ŀ:\n ");
	FILE *pf=fopen(filename, "r");
	fscanf(pf,"%d", &v);
	//printf("������ߵ���Ŀ: \n");
	fscanf(pf,"%d", &e);
	if ( v < 1 || e < 1 || (e > (v * (v-1))))
	{
		printf("�������󣡣�!\n");
		return NULL;
	}
	
	if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
		return NULL;
	memset(pG, 0, sizeof(Graph));						//��ʼ��
	
	// ��ʼ��"������"��"����"
	pG->vexnum = v;
	pG->edgnum = e;
	// ��ʼ��"����"
	for (i = 0; i < pG->vexnum; i++)
	{
		//printf("vertex(%d): ", i);
		//pG->vexs[i] = read_char();
		fscanf(pf,"%d",&c3);
		pG->vexs[i]= (char)c3;
	}
	
	// 1. ��ʼ��"��"��Ȩֵ
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
	// 2. ��ʼ��"��"��Ȩֵ: �����û���������г�ʼ��
	for (i = 0; i < pG->edgnum; i++)
	{
		// ��ȡ�ߵ���ʼ���㣬�������㣬Ȩֵ
		//printf("edge(%d):", i);
		//c1 = read_char();
		//c2 = read_char();
		//scanf("%d", &weight);
		fscanf(pf,"%d%d%d",&c1, &c2, &weight);
		
		p1 = get_position(*pG, (char)c1);
		p2 = get_position(*pG, (char)c2);
		if (p1==-1 || p2==-1)
		{
			printf("��������!!!\n");
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
* ����ͼ(�����ṩ�ľ������ʹ���ļ���)
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
	
	// ����"������"��"����"
	if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
		return NULL;
	memset(pG, 0, sizeof(Graph));//�ڴ濽��������ʼ��0���죡
	
	// ��ʼ��"������"
	pG->vexnum = vlen;
	// ��ʼ��"����"
	for (i = 0; i < pG->vexnum; i++)
		pG->vexs[i] = vexs[i];
	
	// ��ʼ��"��"
	for (i = 0; i < pG->vexnum; i++)
		for (j = 0; j < pG->vexnum; j++)
			pG->matrix[i][j] = matrix[i][j];
			
			// ͳ�Ʊߵ���Ŀ
			for (i = 0; i < pG->vexnum; i++)
				for (j = 0; j < pG->vexnum; j++)
					if (i!=j && pG->matrix[i][j]!=INF)
						pG->edgnum++;
			pG->edgnum /= 2;
			
			return pG;
}

/*
* ���ض���v�ĵ�һ���ڽӶ����������ʧ���򷵻�-1
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
* ���ض���v�����w����һ���ڽӶ����������ʧ���򷵻�-1
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
* ���������������ͼ�ĵݹ�ʵ��
*/
static void DFS(Graph G, int i, int *visited)
{                                   
	int w; 
	
	visited[i] = 1;
	printf("%c ", G.vexs[i]);
	// �����ö���������ڽӶ��㡣����û�з��ʹ�����ô����������
	for (w = first_vertex(G, i); w >= 0; w = next_vertix(G, i, w))
	{
		if (!visited[w])
			DFS(G, w, visited);
	}
	
}

/*
* ���������������ͼ
*/
void DFSTraverse(Graph G)
{
	int i;
	int visited[MAX];       // ������ʱ��
	
	// ��ʼ�����ж��㶼û�б�����
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
* ����������������������Ĳ�α�����
*/
void BFS(Graph G)
{
	int head = 0;
	int rear = 0;
	int queue[MAX];     // �������
	int visited[MAX];   // ������ʱ��
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
			queue[rear++] = i;  // �����
		}
		while (head != rear) 
		{
			j = queue[head++];  // ������
			for (k = first_vertex(G, j); k >= 0; k = next_vertix(G, j, k)) //k��Ϊ���ʵ��ڽӶ���
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
* ��ӡ�������ͼ
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
* prim��С������
*
* ����˵����
*       G -- �ڽӾ���ͼ
*   start -- ��ͼ�еĵ�start��Ԫ�ؿ�ʼ��������С��
*/
void prim(Graph G, int start)
{
	int min,i,j,k,m,n,sum;
	int index=0;         // prim��С������������prims���������
	char prims[MAX];     // prim��С���Ľ������
	int weights[MAX];    // �����ߵ�Ȩֵ
	
	// prim��С�������е�һ������"ͼ�е�start������"����Ϊ�Ǵ�start��ʼ�ġ�
	prims[index++] = G.vexs[start];
	
	// ��ʼ��"�����Ȩֵ����"��
	// ��ÿ�������Ȩֵ��ʼ��Ϊ"��start������"��"�ö���"��Ȩֵ��
	for (i = 0; i < G.vexnum; i++ )
		weights[i] = G.matrix[start][i];
		// ����start�������Ȩֵ��ʼ��Ϊ0��
		// �������Ϊ"��start�����㵽������ľ���Ϊ0"��
		weights[start] = 0;
		
		for (i = 0; i < G.vexnum; i++)
		{
			// ���ڴ�start��ʼ�ģ���˲���Ҫ�ٶԵ�start��������д���
			if(start == i)
				continue;
			
			j = 0;
			k = 0;
			min = INF;
			// ��δ�����뵽��С�������Ķ����У��ҳ�Ȩֵ��С�Ķ��㡣
			while (j < G.vexnum)
			{
				// ��weights[j]=0����ζ��"��j���ڵ��Ѿ��������"(����˵�Ѿ���������С��������)��
				if (weights[j] != 0 && weights[j] < min)
				{
					min = weights[j];
					k = j;
				}
				j++;
			}
			
			// ��������Ĵ������δ�����뵽��С�������Ķ����У�Ȩֵ��С�Ķ����ǵ�k�����㡣
			// ����k��������뵽��С�������Ľ��������
			prims[index++] = G.vexs[k];
			// ��"��k�������Ȩֵ"���Ϊ0����ζ�ŵ�k�������Ѿ��������(����˵�Ѿ���������С�������)��
			weights[k] = 0;
			// ����k�����㱻���뵽��С�������Ľ��������֮�󣬸������������Ȩֵ��
			for (j = 0 ; j < G.vexnum; j++)
			{
				// ����j���ڵ�û�б�����������Ҫ����ʱ�ű����¡�
				if (weights[j] != 0 && G.matrix[k][j] < weights[j])
					weights[j] = G.matrix[k][j];
			}
		}
		
		// ������С��������Ȩֵ
		sum = 0;
		for (i = 1; i < index; i++)
		{
			min = INF;
			// ��ȡprims[i]��G�е�λ��
			n = get_position(G, prims[i]);
			// ��vexs[0...i]�У��ҳ���j��Ȩֵ��С�Ķ��㡣
			for (j = 0; j < i; j++)
			{
				m = get_position(G, prims[j]);
				if (G.matrix[m][n]<min)
					min = G.matrix[m][n];
			}
			sum += min;
		}
		// ��ӡ��С������
		printf("PrimMST(%c)=%d: ", G.vexs[start], sum);
		for (i = 0; i < index; i++)
			printf("%c ", prims[i]);
		printf("\n");
}

/* 
* ��ȡͼ�еı�
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
* �Ա߰���Ȩֵ��С��������(��С����)
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
				// ����"��i����"��"��j����"
				EData tmp = edges[i];
				edges[i] = edges[j];
				edges[j] = tmp;
			}
		}
	}
}

/*
* ��ȡi���յ�
*/
int get_end(int vends[], int i)
{
	while (vends[i] != 0)
		i = vends[i];
	return i;
}

/*
* ��³˹������Kruskal)��С������
*/
void kruskal(Graph G)
{
	int i,m,n,p1,p2;
	int length;
	int index = 0;          // rets���������
	int vends[MAX]={0};     // ���ڱ���"������С������"��ÿ�������ڸ���С���е��յ㡣
	EData rets[MAX];        // ������飬����kruskal��С�������ı�
	EData *edges;           // ͼ��Ӧ�����б�
	
	// ��ȡ"ͼ�����еı�"
	edges = get_edges(G);
	// ���߰���"Ȩ"�Ĵ�С��������(��С����)
	sorted_edges(edges, G.edgnum);
	
	for (i=0; i<G.edgnum; i++)
	{
		p1 = get_position(G, edges[i].start);   // ��ȡ��i���ߵ�"���"�����
		p2 = get_position(G, edges[i].end);     // ��ȡ��i���ߵ�"�յ�"�����
		
		m = get_end(vends, p1);                 // ��ȡp1��"���е���С������"�е��յ�
		n = get_end(vends, p2);                 // ��ȡp2��"���е���С������"�е��յ�
		// ���m!=n����ζ��"��i"��"�Ѿ���ӵ���С�������еĶ���"û���γɻ�·
		if (m != n)
		{
			vends[m] = n;                       // ����m��"���е���С������"�е��յ�Ϊn
			rets[index++] = edges[i];           // ������
		}
	}
	free(edges);
	
	// ͳ�Ʋ���ӡ"kruskal��С������"����Ϣ
	length = 0;
	for (i = 0; i < index; i++)
		length += rets[i].weight;
	printf("KruskalMST=%d: ", length);
	for (i = 0; i < index; i++)
		printf("(%c,%c) ", rets[i].start, rets[i].end);
	printf("\n");
}

/*
* Dijkstra���·����
* ����ͳ��ͼ(G)��"����vs"������������������·����
*
* ����˵����
*        G -- ͼ
*       vs -- ��ʼ����(start vertex)��������"����vs"��������������·����
*     prev -- ǰ���������顣����prev[i]��ֵ��"����vs"��"����i"�����·����������ȫ�������У�λ��"����i"֮ǰ���Ǹ����㡣
*     dist -- �������顣����dist[i]��"����vs"��"����i"�����·���ĳ��ȡ�
*/
void dijkstra(Graph G, int vs, int prev[], int dist[])
{
	int i,j,k;
	int min;
	int tmp;
	int flag[MAX];      // flag[i]=1��ʾ"����vs"��"����i"�����·���ѳɹ���ȡ��
	
	// ��ʼ��
	for (i = 0; i < G.vexnum; i++)
	{
		flag[i] = 0;              // ����i�����·����û��ȡ����
		prev[i] = 0;              // ����i��ǰ������Ϊ0��
		dist[i] = G.matrix[vs][i];// ����i�����·��Ϊ"����vs"��"����i"��Ȩ��
	}
	
	// ��"����vs"������г�ʼ��
	flag[vs] = 1;
	dist[vs] = 0;
	
	// ����G.vexnum-1�Σ�ÿ���ҳ�һ����������·����
	for (i = 1; i < G.vexnum; i++)
	{
		// Ѱ�ҵ�ǰ��С��·����
		// ������δ��ȡ���·���Ķ����У��ҵ���vs����Ķ���(k)��
		min = INF;
		for (j = 0; j < G.vexnum; j++)
		{
			if (flag[j]==0 && dist[j]<min)
			{
				min = dist[j];
				k = j;
			}
		}
		// ���"����k"Ϊ�Ѿ���ȡ�����·��
		flag[k] = 1;
		
		// ������ǰ���·����ǰ������
		// �������Ѿ�"����k�����·��"֮�󣬸���"δ��ȡ���·���Ķ�������·����ǰ������"��
		for (j = 0; j < G.vexnum; j++)
		{
			tmp = (G.matrix[k][j]==INF ? INF : (min + G.matrix[k][j])); // ��ֹ���
			if (flag[j] == 0 && (tmp  < dist[j]) )
			{
				dist[j] = tmp;
				prev[j] = k;
			}
		}
	}
	
	// ��ӡdijkstra���·���Ľ��
	printf("dijkstraSP(%c): \n", G.vexs[vs]);
	for (i = 0; i < G.vexnum; i++)
		printf("  shortest(%c, %c)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);
}

void TestDijkstra()
{
	int prev[MAX] = {0};
	int dist[MAX] = {0};
	Graph* pG;
	
	// �Զ���"ͼ"(����������)
	//pG = create_graph();
	// �������е�"ͼ"
	pG = create_example_graph();
//	pG = create_graph("P196_ͼ6.22_G6.txt");
	print_graph(*pG);       // ��ӡͼ
	DFSTraverse(*pG);       // ������ȱ���
	BFS(*pG);               // ������ȱ���
	prim(*pG, 0);           // prim�㷨������С������
	kruskal(*pG);           // kruskal�㷨������С������
	// dijkstra�㷨��ȡ"��7������"�����������������̾���
	dijkstra(*pG, 6, prev, dist);
}

//���������㷨Floyd����
//����G�����ڽӾ����ʾ����������������·�� 
//D[][]�����·�����Ⱦ���path[][]���·����־���� 
void Floyd(Graph * G,int path[][MAX],int D[][MAX],int n)
{ 
	int i,j,k;
	//��ʼ��
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
	
	//����n������
	for(k=0;k<n;k++)
	{ 
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(D[i][j] > D[i][k] + D[k][j])
				{
					D[i][j]=D[i][k]+D[k][j];			//ȡС�� 
					path[i][j]=path[i][k];				//��Vi�ĺ�� 
				}
			}
		}
	}
}


void TestFloyd()
{
	int i,j,k,v=0,n=0;								//vΪ��㣬nΪ������� 

	Graph *pG= create_example_graph();
//	Graph *pG= create_graph("P201_ͼ6.24_G7.txt");
	n=pG->vexnum;
	AdjType path[MAX][MAX];//v������������·������
	AdjType D[MAX][MAX];//v�����������·����������
	
	Floyd(pG,path,D,n);
	//���ÿ�Զ�������·�����ȼ����·��
	for(i=0;i<n;i++)
	{					
		for(j=0;j<n;j++)
		{
			printf("V%d-V%d����̳���: ",i,j); 
			printf("%d\t",D[i][j]);						//���Vi��Vj�����·������
			k=path[i][j];								//ȡ·����Vi�ĺ���Vk
			if(k==-1)
			{
				printf("V%d-V%d֮��û��·��\n",i,j);//·�������� 
			}
			else
			{
				printf("���·��Ϊ:"); 
				printf("(��%d",i);					//���Vi�����i
				//k������·���յ�jʱ
				while(k!=j)
				{						 
					printf(",V%d",k);				//���k
					k=path[k][j];					//��·������һ������� 
				}
				printf("����%d)",j);			//���·���յ���� 
			}
			printf("\n");
		} 
		if(i==n/2){//�����δ�ӡ������������ڲ鿴��
			system("pause");
			system("cls");
		}
	}
}
/*
���ڽӾ���ͼת���ڽ�����洢
Graph-->VexNode
*/
void CreateGraph(Graph *pG,VexNode* Graph,int vexnumber,int arcnumber)  
{  
	int i = 0, j = 0, k = 0;
	int begin,end,weight; 
	EdgeNode *p; 
	//��ʼ��
	for(i=0;i<vexnumber;i++) 
	{    
		Graph[i].id =0;  
		Graph[i].firstEdge =NULL;  
	}  
	// ͼ�еĸ��������ֵ  
	for(i=0;i<vexnumber;i++)
		Graph[i].data=pG->vexs[i];
 
	//ͼ�л�����ʼ�㼰Ȩֵ:���ʽΪ<���,�յ�,Ȩֵ>
	EData *edges=get_edges(*pG);
	for(k=0;k<arcnumber;k++)
	{  
		begin=edges[k].start-'A'+1;//�ַ�ת�����Σ��Ҵ�1��ʼ
		end=edges[k].end-'A'+1;
		weight=edges[k].weight;
		//�γ�����
		p=(EdgeNode*)malloc(sizeof(EdgeNode));  
		p->adjvex =end-1;  
		p->weight =weight;  
		Graph[end-1].id ++;
		p->nextedge =Graph[begin-1].firstEdge ;  
		Graph[begin-1].firstEdge =p;  
	}  
}
/*
Ѱ�ҹؼ�·��AOE��CMP
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
		printf("\n��������������ͼ�л�·���ɼ�����ؼ�·��\n");
		printf("���˳�������\n");
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
	printf("| ��� | �յ� | ���翪ʼʱ�� | ��ٿ�ʼʱ�� | ��ֵ | �Ƿ�Ϊ�ؼ�·�� \n");  
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
				printf(" �˻�Ϊ�ؼ�� "); 
				sv[t]=Graph[j].data;t++;
			}
			printf("\n"); 
			p=p->nextedge;  
		}
	}  
	printf("�ؼ�·���ڵ�Ϊ��");
	sv[t]=Graph[vexnumber-1].data;
	for(i=0;i<=t;i++)
	{
		printf("%c",sv[i]);
		if(sv[i]!=Graph[vexnumber-1].data)
			printf("--->");
	}
	printf("\n");
	printf("�ؼ�·������Ϊ��%d����λʱ��\n",totaltime); 
	return 1;  
}  
void TestAOE( )  
{  
	Graph*pG= create_example_graph();
//	Graph*pG= create_graph("P206_ͼ6.28_G8.txt");
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
