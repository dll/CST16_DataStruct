/*
程序的任务是从文件读取多项式数据及答案；编写程序验证加法与答案结果是否一致，可谓单元测试！
避免大量输入和计算结果的检查。重点是多项式运算，只给了加法，还有减法和乘法可以写！
2012-10-24 刘东良
*/

#include"DSA04.h"


//函数定义
//////////////////////////////////////////////////
//判断e是否在多项式p中(主要是指数)
int IsExistElem (polynomial *p, ElemType e){
	polynomial *h=p->next;
	while(h){
		if(h->data.expn == e.expn){
			/*printf("%d指数已经存在!\n", e.expn); */ return 1;
		}
		h=h->next;
	}
	return 0;//e.expn项不存在
}
//在链尾插入，结点接在链表后面
int InsAfter( polynomial * p, ElemType e ) {
	polynomial * h, *s;
	if ( ! p )
		return 0;
	h=p;
	s = (polynomial*)malloc(sizeof(polynomial));
	s->data = e;
	while(h->next)
		h=h->next;
	h->next = s;
	s->next=NULL;	
	return 1;
}
//选择排序确保多项式加法运算（在创建和生成多项式时，按指数升序排列
//符合数学习惯，但算法与教材不同，应注意AddPoly函数）
void SelectSortPoly(polynomial *p){
	ElemType e;
	polynomial * tmp1, *tmp2, *least;
	
	if (p)
        for (tmp1 = p; tmp1->next; tmp1 = tmp1->next) {
            for (tmp2 = tmp1->next, least = tmp1; tmp2; tmp2 = tmp2->next)
                if (tmp2->data.expn < least->data.expn)
                    least = tmp2;
				if (tmp1 != least){
					e = tmp1->data;
					tmp1 ->data = least->data;
					least->data = e;
				}
        }	
}
//因为大量输入，改为从文件中的读数生成多项式
//文件读写该掌握啦！
int CreatePolynFromFile ( polynomial **p, char * filename) {
   // 输入m项的系数和指数，建立表示一元多项式的有序链表p
	int i, m, j;
	ElemType e;
	polynomial *h, *q;
	FILE *pf;
	pf=fopen(filename, "r");//打开文件
	if(!pf){
		printf("读多项式数据文件%s失败!\n", filename);
		exit(0);//stdlib.h
	}
	nPoly=0;
	for(j=0; !feof(pf); j++){
		nPoly++;
		p[j] = (polynomial*)malloc(sizeof(polynomial));
		p[j]->data.coef=0.0;
		p[j]->data.expn=-1;
		p[j]->next=NULL;

		h=p[j];

		fscanf(pf, "%d\n", &m);//与scanf比较比较
		for ( i=1; i<=m; ++i ) {  // 依次输入 m 个非零项
			//printf("请输入多项式%d 项的系数和指数(按指数升序):\t", i);
			fscanf (pf, "%f %d", &e.coef, &e.expn);
			if (!IsExistElem ( p[j], e) && e.coef!=0){   
				q = (polynomial*)malloc(sizeof(polynomial));
				q->data = e;
				q->next = NULL;
				h->next=q;
				h=q;				
			}
			else 
				printf("\n多项式%d 的指数%d已经存在或系数为0!\n", j, e.expn);
		}
		fscanf (pf, "\n");
		SelectSortPoly(p[j]);//指数升序排序
	}
	fclose(pf);//关闭文件
	return 1;//成功
} // CreatPolyn

//销毁函数，许多时候都被忽略了！
void DestroyPoly(polynomial *p){
	polynomial *q = p;
	while(p->next){
		q = p->next;
		p->next=q->next;
		free(q);
	}
	free(p);
}
int cmp(ElemType e1, ElemType e2){
	if(e1.expn<e2.expn)
		return -1;
	else if(e1.expn>e2.expn)
		return 1;
	return 0;
}
// 利用两个多项式的结点构成“和多项式” Pc = Pa＋Pb，按指数升序！
int AddPoly ( polynomial **Pc, polynomial *Pa, polynomial *Pb) {
   
   ElemType e1, e2;
   polynomial *a, *b, *h;
   (*Pc) = (polynomial*)malloc(sizeof(polynomial));
   (*Pc)->data.coef=0.0;
   (*Pc)->data.expn=-1;
   (*Pc)->next=NULL;
   h = *Pc;

   a=Pa->next;b=Pb->next;
   while (a && b) {
	   e1=a->data;e2=b->data;
	   switch (cmp(e1, e2)) { 
			case 1: {  // 多项式Pb当前结点的指数值小
				InsAfter (h, e2);			
				b=b->next;
				break;
			}
			case 0: {   // 两者的指数值相等
				e1.coef= e1.coef + e2.coef ;
				if ( e1.coef != 0.0 ) 
					InsAfter(h, e1); 	
				a=a->next;b=b->next;
				break;
			}
			case -1: {  //多项式Pa中当前结点的指数值小
				InsAfter (h, e1);			
				a=a->next;
				break;
			}
		}
    }
   while(a){
	   InsAfter(h, a->data); 
	   a = a->next;
   }
   while(b){
	   InsAfter(h, b->data); 
	   b = b->next;
   }
   SelectSortPoly(h);//指数升序排序
   return 1;
} // AddPoly

//屏幕输入
void PrintPolyn(polynomial *p){
	polynomial * t = p->next;
	if(!t){
		printf("0\n");return;
	}
	while(t){
		printf("%5.1fX^%d ", t->data.coef, t->data.expn);
		t=t->next;
		if(t)
			if(t->data.coef>0)
				printf("+");
			else if(t->data.coef< 0)
				printf(" ");
	}
	printf("\n");
}

//输出到文件
void SavePolyn(FILE *pf, polynomial *p){
	polynomial * t = p->next;
	if(!t){
		fprintf(pf, "0\n");return;
	}
	while(t){
		fprintf(pf, "%5.1fX^%d ", t->data.coef, t->data.expn);
		t=t->next;
		if(t)
			if(t->data.coef>0)
				fprintf(pf, "+");
			else if(t->data.coef< 0)
				fprintf(pf, " ");
	}
	fprintf(pf, "\n\n");
}

//多项式判断，验证AddPoly函数测试使用
int IsEqualPoly(polynomial *a, polynomial *b)
{
	polynomial * h1=a->next, * h2=b->next;
	while(h1 && h2){
		if(h1->data.coef == h2->data.coef && h1->data.expn == h2->data.expn){
			h1=h1->next;
			h2=h2->next;
		}
		else
			return 0;//不等
	}
	if(!h1 && !h2)
		return 1;//相等
	else
		return 0;//不等
}