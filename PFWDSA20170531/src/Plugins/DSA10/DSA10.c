//PFWDSA plugin source file DSA10.c
#include "DSA10.h"

//ͼ�Ĳ���
//�����ڽӾ���洢��ͼ
void CreateAdjMatrixGraph(AdjMatrixGraph *G){
	int i,j,k;
	printf("������ͼ�Ķ�����������ͼ������:\t");flushall();
	scanf("%d%d%d", &G->vexnum, &G->arcnum, &G->kind);
	for(k=0;k<G->vexnum;k++)
		G->vex[k]='A'+k;//ͼ�Ķ��㣺�ַ�
	for(i=0; i<G->vexnum;i++)
		for(j=0;j<G->vexnum;j++)
			G->arc[i][j]=0;//��ʼ���ڽӾ���
	printf("ͼ�ı�Ϊ��%d \n", G->arcnum);
	for(k=0;k<G->arcnum;k++){
		printf("\n������߻�(��0 1):\t");flushall();
		scanf("%d%d", &i, &j);
		G->arc[i][j]=1;
		if(G->kind==0)//0����ͼ
			G->arc[j][i]=1;//�ڽӾ���Գ�
	}
}
void CreateAdjMatrixGraphFromFile(AdjMatrixGraph *G, const char *gname){
	int i,j,k;
	char graphKind[2];
	//printf("������ͼ�Ķ�����������ͼ������:\t");flushall();
	FILE *pf=fopen("Data\\DSA101.dat", "r");
	fscanf(pf,"%s", graphKind);
	if(strcmp(graphKind, gname)==0){
		fscanf(pf, "%d %d %d\n", &G->vexnum, &G->arcnum, &G->kind);
		for(k=0;k<G->vexnum;k++)
			G->vex[k]='A'+k;//ͼ�Ķ��㣺�ַ�
		for(i=0; i<G->vexnum;i++)
			for(j=0;j<G->vexnum;j++)
				G->arc[i][j]=0;//��ʼ���ڽӾ���
		printf("ͼ�ı�Ϊ��%d \n", G->arcnum);
		for(k=0;k<G->arcnum;k++){
			//printf("\n������߻�(��0 1):\t");flushall();
			fscanf(pf, "%d %d\n", &i, &j);
			G->arc[i][j]=1;
			if(G->kind==0)//0����ͼ
				G->arc[j][i]=1;//�ڽӾ���Գ�
		}
	}
	fclose(pf);
}
void PrintAdjMatrixGraph(AdjMatrixGraph*G){
	int i, j;
	for(i=0; i<G->vexnum; i++){
		printf("����%2c", G->vex[i]);
		for(j=0; j<G->vexnum; j++)
			printf("%4d", G->arc[i][j]);
		printf("\n");
	}
}
void FindAdjVex(AdjMatrixGraph * G){
	int i,j, k;
	char v;
	printf("�����ڽӵ㡣������ͼ��ĳ������:\t");flushall();
	scanf("%c", &v);
	for(i=0; i<G->vexnum; i++){
		if(v==G->vex[i])
			k=i;
	}
	if(k<0 || k >=G->vexnum){
		printf("ͼ��û��%c, ע�ⶥ����ĸ���ִ�Сд!", v);
		return;
	}
	if(G->kind==0){
		for(j=0; j<G->vexnum; j++)
			if(G->arc[k][j]==1)
				printf("%c--%c\n", v, G->vex[j]);	
	}else{
		for(j=0; j<G->vexnum; j++){
			if(G->arc[k][j]==1)
				printf("%c-->%c\n", v, G->vex[j]);		
			if(G->arc[j][k]==1)
				printf("%c-->%c\n", G->vex[j], v);
		}
	}
}
//�����ڽ�����洢��ͼ
//nΪͼ������
//mΪͼ������
void CreateAdjLinkListGraph(AdjLinkListGraph *G, int n, int m){
	int i,e=0;
	EdgeLinkNode *p, *q, *s; 
	char x, y;
	G->vex=n;
	G->tag=m;//m=0��ʾ����ͼ
	for(i=0; i<n; i++){//��ʼ���ڽӱ�
		G->VertexNode[i].vertex=i+'A';
		G->VertexNode[i].first=NULL;
	}
	printf("�������(��AB):");flushall();
	scanf("%c%c", &x, &y);//��д��ĸ��ʾͼ�Ķ���
	while(x!=' ' && y!=' '){//����ո����
		e++;//����
		s=(EdgeLinkNode*)malloc(sizeof(EdgeLinkNode));
		s->num=y-'A';//�����µĽ��
		if(G->VertexNode[x-'A'].first==NULL)
		{
			G->VertexNode[x-'A'].first=s;
			s->next=NULL;
		}
		else{
			p=G->VertexNode[x-'A'].first;
			q=p->next;
			while(q!=NULL && s->num > q->num){
				p=q; q=q->next;
			}
			p->next=s;
			s->next=q;
		}
		if(!G->tag){
			s=(EdgeLinkNode*)malloc(sizeof(EdgeLinkNode));
			s->num=x-'A';
			if(G->VertexNode[y-'A'].first==NULL){
				G->VertexNode[y-'A'].first=s; s->next=NULL;
			}
			else{
				p=G->VertexNode[y-'A'].first;
				q=p->next;
				while(q!=NULL && s->num > q->num){
					p=q;q=q->next;
				}
				p->next=s;s->next=q;
			}
		}
		printf("�������(��AB):");flushall();
		scanf("%c%c", &x, &y);
	}
	G->edge=e;
}
void CreateAdjLinkListGraphFromFile(AdjLinkListGraph *G, const char * gname, int n, int m){
	int i,e=0;
	EdgeLinkNode *p, *q, *s; 
	char x, y, b;
	char graphKind[2];
	FILE *pf=fopen("Data\\DSA101.dat", "r");
	while(!feof(pf)){
		fscanf(pf,"%s\n", graphKind);
		if(strcmp(graphKind,gname)==0){
			G->vex=n;
			G->tag=m;//m=1��ʾ����ͼ
			for(i=0; i<n; i++){//��ʼ���ڽӱ�
				G->VertexNode[i].vertex=i+'A';
				G->VertexNode[i].first=NULL;
			}
			fscanf(pf, "%c%c%c\n", &x, &b, &y);//��д��ĸ��ʾͼ�Ķ���
			while(x!='0' && y!='0'){//����ո����
				e++;//����
				s=(EdgeLinkNode*)malloc(sizeof(EdgeLinkNode));
				s->num=y-'A';//�����µĽ��
				if(G->VertexNode[x-'A'].first==NULL)
				{
					G->VertexNode[x-'A'].first=s;
					s->next=NULL;
				}
				else{
					p=G->VertexNode[x-'A'].first;
					q=p->next;
					while(q!=NULL && s->num > q->num){
						p=q; q=q->next;
					}
					p->next=s;
					s->next=q;
				}
				if(!G->tag){
					s=(EdgeLinkNode*)malloc(sizeof(EdgeLinkNode));
					s->num=x-'A';
					if(G->VertexNode[y-'A'].first==NULL){
						G->VertexNode[y-'A'].first=s; s->next=NULL;
					}
					else{
						p=G->VertexNode[y-'A'].first;
						q=p->next;
						while(q!=NULL && s->num > q->num){
							p=q;q=q->next;
						}
						p->next=s;s->next=q;
					}
				}
				fscanf(pf, "%c%c%c\n", &x, &b, &y);
			}
			G->edge=e;
		}
	}
	fclose(pf);
}
void PrintAdjLinkListGraph(AdjLinkListGraph *G){
	int i;
	EdgeLinkNode *p;
	printf("�ڽ������ʾ��ͼ:\n");
	for(i=0; i<G->vex; i++){
		printf("%d:%c->", i, G->VertexNode[i].vertex);
		p=G->VertexNode[i].first;
		while(p){
			printf("%3d->", p->num);
			p=p->next;
		}
		printf("\n");
	}
	printf("\n");
}
////������ȱ���,���������ȸ�����
void VisitedAdjLinkListGraphDFS(AdjLinkListGraph *G, int v, int visited[]){
	EdgeLinkNode *p;
	visited[v] = 1;
	printf("%c->", G->VertexNode[v].vertex);
	p=G->VertexNode[v].first;
	while(p){
		if(!visited[p->num])
			VisitedAdjLinkListGraphDFS(G, p->num, visited);//�ݹ�
		p=p->next;
	}
}
//������ȱ���
void DFSVisitGraph(AdjLinkListGraph * G){
	int i;
	int visited[MAXVERTEX]={0};
	printf("������ȱ���:");
	for(i=0; i<G->vex;i++)
		if(!visited[i])
			VisitedAdjLinkListGraphDFS(G, i, visited);
	printf("\n\n");
}
////������ȱ���,�������Ĳ���������ǵݹ飩
void VisitedAdjLinkListGraphBFS(AdjLinkListGraph *G, int v, int visited[]){
	int queue[MAXVERTEX], front, rear, i;
	EdgeLinkNode	*p;
	
	front=rear=0;
	queue[rear++]=v;
	while(front!=rear){
		v=queue[front++];
		printf("%c->", G->VertexNode[v].vertex);
		visited[v]=1;
		p=G->VertexNode[v].first;
		while(p){
			for(i=0; i<rear; i++)
				if(p->num == queue[i])break;
			if(i>=rear)
				queue[rear++]=p->num;
			p=p->next;
		}
	}
}
//������ȱ���
void BFSVisitGraph(AdjLinkListGraph * G){
	int i;
	int visited[MAXVERTEX]={0};
	printf("������ȱ���:");
	for(i=0; i<G->vex;i++)
		if(!visited[i])
			VisitedAdjLinkListGraphBFS(G, i, visited);
	printf("\n\n");
}

int cmp( const void *a ,const void *b) 
{ 
	return (*(Edges *)a).weight > (*(Edges *)b).weight ? 1 : -1; 
} 

void PrimMST(int c[MAXVERTEXES][MAXVERTEXES], int n){
	int i, j, k, min, lowcost[MAXVERTEXES], closest[MAXVERTEXES];

	printf("Prim�㷨ͼ����С������\n");
	for(i=2; i<=n; i++){
		lowcost[i]=c[1][i];
		closest[i]=1;
	}
	closest[1]=0;
	for(i=2; i<=n; i++){
		min=MAXCOST;
		k=i;
		for(j=1; j<=n; j++)
			if(lowcost[j]<min && closest[j]!=0){
				min=lowcost[j];
				k=j;
			}
		printf("(%d, %d)", closest[k], k);
		closest[k]=0;
		for(j=2; j<=n; j++)
			if(closest[j]!=0 && c[k][j]<lowcost[j]){
				lowcost[j]=c[k][j];
				closest[j]=k;
			}
	}
	printf("\n");
}
int Seek(int set[], int v){
	int i=v;
	while(set[i]>0)
		i=set[i];
	return i;
}

void KruskalMST(EdgeSet ge, int n, int e){
	int set[MAXEDGES], v1, v2, i, j;

	printf("Kruskal�㷨ͼ����С������\n");
	for(i=1; i<=n; i++)
		set[i]=0;
	i=1;
	j=1;
	while(j<n && i<=e){
		v1=Seek(set, ge[i].bVertex);
		v2=Seek(set, ge[i].eVertex);
		if(v1!=v2){
			printf("(%d, %d)", ge[i].bVertex, ge[i].eVertex);
			set[v1]=v2;
			j++;
		}
		i++;
	}
	printf("\n");
}
void CreateAdjLinkListGraphTopSort(AdjLinkListGraphTopSort *G, int n, int m){
	int i,e=0;
	EdgeLinkNode *p, *q, *s; 
	char x, y;
	G->vex=n;
	G->tag=m;
	for(i=0; i<n; i++){
		G->VertexNode[i].vertex=i+'A';
		G->VertexNode[i].first=NULL;
		G->VertexNode[i].count=0;
	}
	printf("�������(��AB):");flushall();
	scanf("%c%c", &x, &y);
	while(x!=' ' && y!=' '){
		e++;
		s=(EdgeLinkNode*)malloc(sizeof(EdgeLinkNode));
		s->num=y-'A';
		if(G->VertexNode[x-'A'].first==NULL)
		{
			G->VertexNode[x-'A'].first=s;
			//G->VertexNode[x-'A'].count++;//����
			s->next=NULL;
		}
		else{
			p=G->VertexNode[x-'A'].first;
			//G->VertexNode[x-'A'].count++;//����
			q=p->next;
			while(q!=NULL && s->num > q->num){
				p=q; q=q->next;
			}
			p->next=s;
			s->next=q;
		}
		if(!G->tag){
			s=(EdgeLinkNode*)malloc(sizeof(EdgeLinkNode));
			s->num=x-'A';
			if(G->VertexNode[y-'A'].first==NULL){
				G->VertexNode[y-'A'].first=s; s->next=NULL;
				G->VertexNode[y-'A'].count++;//���
			}
			else{
				p=G->VertexNode[y-'A'].first;
				G->VertexNode[y-'A'].count++;//���
				q=p->next;
				while(q!=NULL && s->num > q->num){
					p=q;q=q->next;
				}
				p->next=s;
				s->next=q;
			}
		}
		printf("�������(��AB):");flushall();
		scanf("%c%c", &x, &y);
	}
	G->edge=e;
}

void TopSort(AdjLinkListGraphTopSort *G){
	int i, j, top=0, n=0;
	char stack[MAXVERTEX], ch;
	EdgeLinkNode * p;
	for(i=0; i<G->vex; i++)
		if(G->VertexNode[i].count==0)
			stack[top++]=G->VertexNode[i].vertex;
	while(top>0){
		ch=stack[--top];
		printf("%c->",ch);
		n++;
		p=G->VertexNode[ch-'A'].first;
		while(p){
			j=p->num;
			G->VertexNode[j].count--;
			if(G->VertexNode[j].count==0)
				stack[top++]=G->VertexNode[j].vertex;
			p=p->next;
		}
	}
	if(n<G->vex)
		printf("ͼ�л�!\n");
	printf("\n");
}
void PrintAdjLinkListGraphTopSort(AdjLinkListGraphTopSort *G){
	int i;
	EdgeLinkNode *p;
	printf("�ڽ������ʾ��ͼ:\n");
	for(i=0; i<G->vex; i++){
		printf("%d:%c->", i, G->VertexNode[i].vertex);
		p=G->VertexNode[i].first;
		while(p){
			printf("%c->", 'A'+p->num);
			p=p->next;
		}
		printf("\n");
	}
	printf("\n");
}

//ͼ�Ĳ���
void CreateAdjMatrixGraphDijkstra(AdjMatrixGraph *G){
	int i,j,k,w;
	printf("������ͼ�Ķ���������:\t");flushall();
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for(k=0;k<G->vexnum;k++)
		G->vex[k]='A'+k;
	for(i=0; i<G->vexnum;i++)
		for(j=0;j<G->vexnum;j++)
			G->arc[i][j]=INFINITY;
	for(k=0;k<G->arcnum;k++){
		printf("\n������߻򻡼�Ȩ��(��0 1 6):\t");flushall();
		scanf("%d%d%d", &i, &j, &w);
		G->arc[i][j]=w;
	}
}
void PrintAdjMatrixGraphDijkstra(AdjMatrixGraph*G){
	int i, j;
	for(i=0; i<G->vexnum; i++){
		printf("����%2c", G->vex[i]);
		for(j=0; j<G->vexnum; j++)
			if(G->arc[i][j]==INFINITY)
				printf("%4c", ' ');
			else
				printf("%4d", G->arc[i][j]);
		printf("\n");
	}
}

void Dijkstra(AdjMatrixGraph *G, int n, int v0, int d[]){
	int s[MAXVERTEX];
	int i, j, u, mindis;
	for(i=0; i<n; i++){
		d[i]=G->arc[v0][i]; s[i]=0;
	}
	s[v0]=1;
	for(i=1; i<n; i++){
		mindis=INFINITY;
		for(j=0; j<n; j++)
			if(s[j]==0 && d[j]<mindis)
			{
				u=j;mindis=d[j];
			}
		s[u]=1;
		for(j=1; j<=n; j++)
			if(s[j]==0 && d[j]>d[u]+G->arc[u][j])
				d[j]=d[u]+G->arc[u][j];
	}
}



//ͼ�Ĳ���
void CreateAdjMatrixGraphFloyd(AdjMatrixGraph *G){
	int i,j,k,w;
	printf("������ͼ�Ķ���������:\t");flushall();
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for(k=0;k<G->vexnum;k++)
		G->vex[k]='A'+k;
	for(i=0; i<G->vexnum;i++)
		for(j=0;j<G->vexnum;j++)
			G->arc[i][j]=INFINITY;
	for(k=0;k<G->arcnum;k++){
		printf("\n������߻򻡼�Ȩ��(��0 1 6):\t");flushall();
		scanf("%d%d%d", &i, &j, &w);
		G->arc[i][j]=w;
	}
}
void PrintAdjMatrixGraphFloyd(AdjMatrixGraph*G){
	int i, j;
	for(i=0; i<G->vexnum; i++){
		printf("����%2c", G->vex[i]);
		for(j=0; j<G->vexnum; j++)
			if(G->arc[i][j]==INFINITY)
				printf("%4c", ' ');
			else
				printf("%4d", G->arc[i][j]);
		printf("\n");
	}
}

void Floyd(int cost[][MAXVERTEX], int n, int weight[][MAXVERTEX], int path[][MAXVERTEX]){
	int i, j, k;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++){
			weight[i][j]=cost[i][j];
			path[i][j]=-1;
	}
	for(k=0; k<n; k++){
		for(i=0; i<n; i++)
			for(j=0; j<n; j++)
				if(weight[i][j]>weight[i][k] + weight[k][j]){
					weight[i][j]=weight[i][k] + weight[k][j];
					path[i][j]=path[i][k] + path[k][j];
				}
	}
}