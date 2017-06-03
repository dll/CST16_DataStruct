#include"DSA08.h"


void 	PrintSymmetricMatrix(int a[]){
	int i,j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++)
			if(i>=j)printf("%4d", a[i*(i+1)/2 +j]);
			else printf("%4d", a[j*(j+1)/2 + i]);
			printf("\n");
	}
}


void CreateTSL(TupleSeqList * m, iElemType A[M][N]){
	int i,j;
	m->rownum=M;
	m->colnum=N;
	m->nznum=0;
	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
			if(A[i][j]!=0){
				m->data[m->nznum].i=i;
				m->data[m->nznum].j=j;
				m->data[m->nznum].e=A[i][j];
				m->nznum++;			
			}
}

void PrintSparseMatrix(TupleSeqList * m){
	int i, j, k, e;
	for(i=0; i<m->rownum; i++){
		for(j=0; j<m->colnum; j++){
			e=0;
			for(k=0; k<m->nznum; k++)
				if(i==m->data[k].i && j==m->data[k].j){
					e=m->data[k].e; break;
				}
			printf("%4d",e);
		}
		printf("\n");
	}
	printf("\n");
}
void PrintTupleSeqList(TupleSeqList * m){
	int k;
	for(k=0; k<m->nznum; k++)
		printf("%4d %4d %4d\n",m->data[k].i, m->data[k].j, m->data[k].e);
	printf("\n");
}


void Translate(TupleSeqList *T, TupleSeqList *m){
	int col,b, q=0;
	T->rownum=m->colnum;
	T->colnum=m->rownum;
	T->nznum=m->nznum;
	if(T->nznum!=0){
		for(col=0; col<m->colnum; col++)
			for(b=0; b<m->nznum; b++)
				if(m->data[b].j==col)
				{
					T->data[q].i=m->data[b].j;
					T->data[q].j=m->data[b].i;
					T->data[q].e=m->data[b].e;
					q++;
				}
	}
}


void SubString(char* sub, char* S, int i, int j){
	char *p1=S+i-1, *p2=sub;
	int k=1;
	while(k<=j){
		*p2++ = *p1++;
		k++;
	}
	*p2='\0';
}

void SplitStrServe(char *str, char * hstr){
	char ch=*str;
	int n, i, k;
	n=strlen(str);
	i=0;
	for(k=0; i<n && ch!=',' || k!=0; i++){
		ch = *(str+i);
		if(ch=='(')
			++k;
		else if(ch==')')
				--k;
	}

	if(i<n){
		SubString(hstr, str, 1, i-1);
		SubString(str, str, i+1, n-i+1);
	}
	else{
		strcpy(hstr, str);
		*str='\0';
	}
}

GLHTNode * CreateGL(char *S){
	GLHTNode *h, *p, *q;
	char emp[]="()";
	char sub[81],hsub[81];
	if(strcmp(S,emp)==0) h=NULL;
	else{
		h=(GLHTNode*)malloc(sizeof(GLHTNode));
		if(strlen(S)==1){
			h->tag=0;
			h->val.data=*S;
		}
		else{
			h->tag=1;
			p=h;
			SubString(sub, S, 2, strlen(S)-2);
			do{
				SplitStrServe(sub, hsub);
				p->val.ptr.hp=CreateGL(hsub);
				q=p;
				if(strlen(sub)!=0){
					p=(GLHTNode*)malloc(sizeof(GLHTNode));
					p->tag=1;
					q->val.ptr.tp=p;
				}
			}while(strlen(sub)!=0);
			q->val.ptr.tp=NULL;
		}
	}
	return h;
}

int GetGLDepth(GLHTNode *h){
	int max, dep;
	GLHTNode * p;
	if(h==NULL)return 1;
	if(h->tag==0)return 0;
	for(max=0, p=h; p; p=p->val.ptr.tp){
		dep=GetGLDepth(p->val.ptr.hp);
		if(dep>max)max=dep;
	}
	return max+1;
}
void PrintGL(GLHTNode *h){
	GLHTNode *p;
	if(h!=NULL){
		if(h->tag==1){
			p=h->val.ptr.hp;
			if(p->tag==1)
				printf("%c", '(');
			PrintGL(h->val.ptr.hp);
		}
		else
			printf("%c", h->val.data);
		if(h->tag==1 && h->val.ptr.tp!=h)
		{
			if(h->val.ptr.tp!=NULL){
				printf("%c", ',');
				PrintGL(h->val.ptr.tp);
			}
			else
				printf("%c", ')');
		}
	}
	else
		printf("()");
}

GLHTNode * CopyGL(GLHTNode *h){
	GLHTNode *p;
	if(h==NULL)p=NULL;
	else{
		p=(GLHTNode*)malloc(sizeof(GLHTNode));
		p->tag=h->tag;
		if(h->tag==0)p->val.data=h->val.data;
		else{
			p->val.ptr.hp = CopyGL(h->val.ptr.hp);
			p->val.ptr.tp = CopyGL(h->val.ptr.tp);
		}
	}
	return p;
}

GLHTNode * GetGLHead(GLHTNode *h){
	GLHTNode *p;
	if(h==NULL)p=NULL;
	else p=CopyGL(h->val.ptr.hp);
	return p;
}

GLHTNode * GetGLTail(GLHTNode *h){
	GLHTNode *p;
	if(h==NULL)p=NULL;
	else p=CopyGL(h->val.ptr.tp);
	return p;
}


AcrossLinker* CreateAcrossLinker(AcrossLinker *h[], int A[M][N]){
	int i, j;
	MatrixNode *p, *q;
	p=(AcrossLinker*)malloc(sizeof(MatrixNode));
	h[0] = p;
	p->row = M;
	p->col = N;
	for(i=1; i<=Max; i++){
		p=(MatrixNode*)malloc(sizeof(MatrixNode));	
		p->row = p->col=-1;
		h[i]=p;
		h[i-1]->tag.link=p;
		p->down=p->right=p;
	}
	h[Max]->tag.link=h[0];
	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
			if(A[i][j]!=0){
				p=(MatrixNode*)malloc(sizeof(MatrixNode));
				p->row=i;p->col=j;p->tag.value=A[i][j];
				q=h[i+1];
				while(q->right!=h[i+1] && q->right->col<j)
					q=q->right;
				p->right = q->right;
				q->right = p;
				q=h[j+1];
				while(q->down!=h[j+1] && q->down->row<i)
					q=q->down;
				p->down=q->down;
				q->down=p;
			}
	return h[0];
}

void PrintAcrossLinker(AcrossLinker *h){
	MatrixNode *p, *q;
	int i, j, e;
	p=h->tag.link;
	for(i=0; i<M; i++){
		q=p->right;
		for(j=0; j<N; j++){
			e=0;
			if(i==q->row && j==q->col){
				e=q->tag.value;
				q=q->right;
			}
			printf("%4d",e);
		}
		p=p->tag.link;
		printf("\n");
	}
	printf("\n");
}

AcrossLinker* PreNode(AcrossLinker *h[], int i, int j){
	AcrossLinker *p=h[j+1];
	while(p->down->col !=-1 && p->down->row<i-1)
		p=p->down;
	return p;
}

void MatrixAdd(AcrossLinker *ha, AcrossLinker *hb, AcrossLinker *h[]){
	MatrixNode *p, *q, *ca, *cb, *pa, *pb, *qa;
	if(ha->row!=hb->row || ha->col != hb->col){
		printf("a和b矩阵行列不等, 不能相加!\n");exit(0);
	}
	ca=ha->tag.link;
	cb=hb->tag.link;
	do{
		pa=ca->right;
		pb=cb->right;
		qa=ca;
		while(pb->col!=-1)
			if(pa->col!=-1 && pa->col <pb->col){
				qa=pa;pa=pa->right;			
			}
			else if(pa->col==-1 || pa->col>pb->col){
				p=(MatrixNode*)malloc(sizeof(MatrixNode));
				p->row=pb->row;
				p->col=pb->col;
				p->tag.value=pb->tag.value;
				p->right=pa;
				qa->right=p;qa=p;
				q=PreNode(h, p->row, p->col);
				p->down=q->down;
				q->down=p;
				pb=pb->right;				
			}
			else{
				pa->tag.value += pb->tag.value;
				if(pa->tag.value==0){
					qa->right=pa->right;
					q=PreNode(h, pa->row, pa->col);
					q->down=pa->down;
					free(pa);
				}
				else
					qa=pa;
				pa=pa->right;pb=pb->right;
			}
			ca=ca->tag.link;
			cb=cb->tag.link;
	}while(ca->row==-1);
}

void DestroyAcrossLinker(AcrossLinker *h){
	MatrixNode *p, *q, *t;
	int i, j, e;
	p=h->tag.link;
	for(i=0; i<M; i++){
		q=p->right;
		t=p->right;
		for(j=0; j<N; j++){
			e=0;
			if(i==q->row && j==q->col){
				t=q->right->right;
				free(q);
				q=t;
			}
		}
		p=p->tag.link;
	}
}
