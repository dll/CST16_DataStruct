/*
*文件：DSA06.C
*插件文件，特殊线性表：串及模式匹配
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA06.h"

LinkString * InitLinkString(void){
	LinkString *LS;
	LS=(LinkString*)malloc(sizeof(LinkString));
	LS->next=NULL;
	return LS;
}
void DestroyLinkString(LinkString * LS){
	LinkString * p=LS->next;
	while(p){
		LS->next = p->next;
		free(p);
		p=LS->next;
	}
	free(LS);
}
void LinkStringAssign(LinkString * LS, char *s){
	int i;
	LinkString *p, *q, *r;
	r=LS;
	q=LS->next;
	for(i=0; s[i]!='\n'; i++)
		if(q!=NULL){q->ch=s[i]; r=q; q=q->next;}
		else{
			p=(LinkString*)malloc(sizeof(LinkString));
			p->ch=s[i];
			r->next=p;
			r=p;
		}
	r->next=NULL;
	while(q!=NULL){
		p=q->next;free(q);q=p;
	}
}
void PrintLinkString(LinkString * LS){
	LinkString * p=LS->next;
	while(p){
		printf("%c ", p->ch);
		p = p->next;
	}
	printf("\n");
}

void FirstUpr(LinkString * LS){
	int word=0;
	LinkString *p;
	p=LS->next;
	while(p){
		if(p->ch==' ')word=0;
		else if(word==0)
		{
			if(p->ch>='a' && p->ch<='z')
				p->ch -= 32;
			word=1;
		}
		p=p->next;
	}

}

void InitSeqString(SeqString * SS ){
	SS->ch = (char*)malloc(INITSTRLEN * sizeof(char));
	SS->length=0;
	SS->strsize=INITSTRLEN;
}
void SeqStringAssign(SeqString * SS, char *s){
	int i=0;
	while(s[i]!='\n')i++;
	if(i>SS->strsize){
		SS->ch=(char*)realloc(SS->ch, i*sizeof(char));
		SS->strsize = i;
	}
	SS->length=i;
	for(i=0;i<SS->length; i++)
		SS->ch[i]=s[i];
}
void PrintSeqString(SeqString * SS){
	int i;
	for(i=0; i<SS->length; i++)
		printf("%c ", SS->ch[i]);
	printf("\n");	
}

int StringBFIndex(SeqString *s, SeqString *t, int pos, int *o){
	int i, j, c;
	if(pos<1 || pos>s->length || pos>s->length - t->length+1) return 0;
	i=pos-1;j=0;c=1;
	while(i<s->length && j<t->length){
		 c++;
		if(s->ch[i]==t->ch[j])
		{i++; j++;}
		else
		{i=i-j+1; j=0;}
	}
	*o=c;
	if(j>=t->length)
		return i-t->length+1;
	else
		return 0;
}
int LinkStrBFSeek(LinkString * LS, LinkString * LT, int pos, int *o){
	int i,c; LinkString *p,*q,*r;
	if(pos<1)return 0;
	for(i=0,r=LS; r&&i<pos; i++,r=r->next);
	if(!r)return 0;
	c=1;
	while(r){
		p=r;q=LT->next;
		while(p && q && q->ch == p->ch){
			p=p->next;q=q->next;c++;
		}
		*o=c;
		if(!q)
			return i;
		i++;
		r=r->next;
	}
	*o=c;
	return 0;
}

void  GetNext(SeqString *SS, int next[]){
	int j, k;
	j=0;k=-1;next[0]=-1;
	while(j<SS->length)
		if(k==-1 || SS->ch[j]==SS->ch[k])
		{j++; k++; next[j]=k;}
		else
			k=next[k];
}

void  GetNextValue(SeqString *SS, int nextval[]){
	int j, k;
	j=0;k=-1;nextval[0]=-1;
	while(j<SS->length)
		if(k==-1 || SS->ch[j]==SS->ch[k]){
			j++; k++; 
			if(SS->ch[j]!=SS->ch[k])
				nextval[j]=k;
			else
				nextval[j]=nextval[k];
		}
		else
			k=nextval[k];
}
int StringKMPIndex(SeqString *s, SeqString *t, int pos, int *o){
	int next[INITSTRLEN], i, j, c;
	GetNext(s, next);
	i=pos-1;j=0;c=1;
	while(i<s->length && j<t->length){
		c++;
		if(j==-1 || s->ch[i]==t->ch[j])
		{i++;j++;}
		else j=next[j];
	}
	*o=c;
	if(j>=t->length)
		return i-t->length+1;
	else
		return 0;
}
int StringKMPIndex2(SeqString *s, SeqString *t, int pos, int *o){
	int next[INITSTRLEN], i, j, c;
	GetNextValue(s, next);
	i=pos-1;j=0;c=1;
	while(i<s->length && j<t->length){
		c++;
		if(j==-1 || s->ch[i]==t->ch[j])
		{i++;j++;}
		else j=next[j];
	}
	*o=c;
	if(j>=t->length)
		return i-t->length+1;
	else
		return 0;
}

void MaxComSubStr(SeqString *s, SeqString *t){
	int pos=0, len=0, i, j, k, len1;
	i=0;
	while(i<s->length){
		j=0;
		while(j<t->length){
			if(s->ch[i]==t->ch[j]){
				len1=1;
				for(k=1;k+i<s->length && k+j<t->length && s->ch[k+i]==t->ch[k+j];k++)
					len1++;
				if(len1>len){ pos=i; len=len1;}
			}
			j++;
		}
		i++;
	}
	for(i=0; i<len; i++)
		printf("%c ", s->ch[i+pos]);
}
