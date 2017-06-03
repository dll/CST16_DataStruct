/*
*�ļ���TestDSA06.C
*����ļ����������Ա�����ģʽƥ�䣬DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include"DSA06.h"

char gVersion[20];
char gInterface[20];
//�����Ϣ
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			strcpy(gVersion,"1.0.0");
			strcpy(gInterface,"DSAInterface");
			break;
		case DLL_THREAD_ATTACH:	
		case DLL_THREAD_DETACH:		
		case DLL_PROCESS_DETACH:	
			break;
    }
    return TRUE;
}
char* GetPluginVersion(){
	return gVersion;
}
char* GetPluginInterface(){
	return gInterface;
}
//�����ܵĽӿ�

void TestFirstUpr(void);
void TestLinkStrBFSeek(void);
void TestBFKMPNext(void);
void TestMaxComSubStr(void);

void DSAInterface(void){
	int i=0;
	while(i!=5){
		system("CLS");
		printf("\n˳�򴮡�������BF��KMPģʽƥ���㷨��ʾ\
			\n����������ѡ��:\n1 TestFirstUpr\n2 TestLinkStrBFSeek\
			\n3 TestBFKMPNext\n4 TestMaxComSubStr\n5 �˳�\n");
		flushall();
		scanf("%d", &i);
		switch(i){
			case 1:
			TestFirstUpr();break;
			case 2:
			TestLinkStrBFSeek();break;
			case 3:
			TestBFKMPNext();break;
			case 4:
			TestMaxComSubStr();break;
			case 5:return;
		}
		system("PAUSE");
	}
}

void TestFirstUpr(void){
	
	char str[200];
	FILE * pf;
	LinkString *LS;
	
	LS = InitLinkString();
	if((pf=fopen("Data\\DSA061.dat", "r"))==NULL){
		printf("���ļ� DSA061.dat ʧ��!"); exit(0);
	}
	while(fgets(str, 200, pf) !=NULL){
		LinkStringAssign(LS, str);
		FirstUpr(LS);
		
		PrintLinkString(LS);
	}
	fclose(pf);

	DestroyLinkString(LS);
}

void TestLinkStrBFSeek(void){
	
	int o;
	char sstr[200], tstr[200];
	FILE * pf;
	SeqString SS, ST;
	LinkString *LS, *LT;
	
	LS = InitLinkString();
	LT = InitLinkString();
	InitSeqString(&SS);
	InitSeqString(&ST);

	if((pf=fopen("Data\\DSA062.dat", "r"))==NULL){
		printf("���ļ� DSA062.dat ʧ��!"); exit(0);
	}
	while(fgets(sstr, 200, pf) !=NULL && fgets(tstr, 200, pf) !=NULL){
		printf("˳�򴮵�BF:\n");
		SeqStringAssign(&SS, sstr);
		PrintSeqString(&SS);
		SeqStringAssign(&ST, tstr);
		PrintSeqString(&ST);
		if(StringBFIndex(&SS, &ST, 1, &o)==0)
			printf("StringBFIndex O(%d)ʧ��!\n", o);
		else
			printf("StringBFIndex O(%d),������%d λ��ƥ��ɹ�!\n", o, StringBFIndex(&SS,&ST,1,&o));

		printf("������BF:\n");
		LinkStringAssign(LS, sstr);
		PrintLinkString(LS);
		LinkStringAssign(LT, tstr);			
		PrintLinkString(LT);
		if(LinkStrBFSeek(LS, LT, 1, &o)==0)
			printf("LinkStrBFSeek O(%d)ʧ��!\n", o);
		else
			printf("LinkStrBFSeek O(%d),������%d λ��ƥ��ɹ�!\n", o, LinkStrBFSeek(LS,LT,1,&o));
		printf("\n\n");

	}
	fclose(pf);

}
void TestBFKMPNext(void){
	
	int o; int next[200];
	char sstr[200], tstr[200];
	FILE * pf;
	SeqString SS, ST;
	
	InitSeqString(&SS);
	InitSeqString(&ST);

	if((pf=fopen("Data\\DSA063.dat", "r"))==NULL){
		printf("���ļ� DSA063.dat ʧ��!"); exit(0);
	}
	while(fgets(sstr, 200, pf) !=NULL && fgets(tstr, 200, pf) !=NULL){
		printf("˳�򴮵�BF:\n");
		SeqStringAssign(&SS, sstr);
		PrintSeqString(&SS);
		SeqStringAssign(&ST, tstr);
		PrintSeqString(&ST);
		if(StringBFIndex(&SS, &ST, 1, &o)==0)
			printf("StringBFIndex O(%d)ʧ��!\n", o);
		else
			printf("StringBFIndex O(%d),������%d λ��ƥ��ɹ�!\n", o, StringBFIndex(&SS,&ST,1,&o));

		printf("˳�򴮵�KMP:\n");
		if(StringKMPIndex(&SS, &ST, 1, &o)==0)
			printf("StringKMPIndex O(%d)ʧ��!\n", o);
		else
			printf("StringKMPIndex O(%d),������%d λ��ƥ��ɹ�!\n", o, StringKMPIndex(&SS,&ST,1,&o));

		printf("˳�򴮵ĸĽ�KMP:\n");
		if(StringKMPIndex2(&SS, &ST, 1, &o)==0)
			printf("StringKMPIndex O(%d)ʧ��!\n", o);
		else
			printf("StringKMPIndex O(%d),������%d λ��ƥ��ɹ�!\n", o, StringKMPIndex2(&SS,&ST,1,&o));
		printf("\n\n");

	}
	printf("��next��nextvalֵ:\n");
	for(o=0;sstr[o]!='\n';o++)
		printf("%d ", o);//j
	printf("\n");
	SeqStringAssign(&SS, sstr);
	PrintSeqString(&SS);//pattern string
	GetNext(&SS, next);
	for(o=0;o<SS.length; o++)
		printf("%d ", next[o]);//next
	printf("\n");

	GetNextValue(&SS, next);
	for(o=0;o<SS.length; o++)
		printf("%d ", next[o]);//nextval
	printf("\n");

	fclose(pf);

}

void TestMaxComSubStr(void){
	
	char sstr[200], tstr[200];
	FILE * pf;
	SeqString SS, ST;
	
	InitSeqString(&SS);
	InitSeqString(&ST);

	if((pf=fopen("Data\\DSA064.dat", "r"))==NULL){
		printf("���ļ� DSA064.dat ʧ��!"); exit(0);
	}
	while(fgets(sstr, 200, pf) !=NULL && fgets(tstr, 200, pf) !=NULL){
		SeqStringAssign(&SS, sstr);
		PrintSeqString(&SS);
		SeqStringAssign(&ST, tstr);
		PrintSeqString(&ST);
		printf("������Ӵ�:\t");
		MaxComSubStr(&SS, &ST);
		printf("\n\n");

	}
	fclose(pf);
}