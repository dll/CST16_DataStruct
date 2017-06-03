/*
*�ļ���TestDSA02.C
*����ļ���ʵ��˳���б���DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/
#include "DSA02.h"

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
char SeqListMenu(SeqList *SL);

void DSAInterface(void){

	char flag;
	SeqList SL;
	InitSeqList2(&SL);//��ʼ��
	flag='b';
	while(flag !='Q' && flag != 'q'){		
		system("CLS");//����
		flag = SeqListMenu(&SL);//˳�������	
		system("PAUSE");//��ͣ
	}

	ClearSeqList(&SL);//����
}

char SeqListMenu(SeqList *SL){

	int i, n, j, speed;
	ElemType x;
	char c, r;
	char fname[20];
	char tempFolder[100]=".\\Temp\\";

	printf("****************************** ˳������� ********************************\n\n");
	printf(" ��ʼ��������InitList��ʼ����[I/i]\n\n");
	printf(" ���ٲ�����Clear���ٱ�[C/c]��Quit�˳�[Q/q]\n\n");
	printf(" �����Ͳ�����Find����[F/f]��Save����[S/s]��Print��ӡ[P/p]\n\n");
	printf(" �ӹ��Ͳ�����Read��ȡ[R/r]��Add����[A/a]��Deleteɾ��[D/d]��Edit�༭[E/e]\n\n");
	printf("***************************************************************************\n\n");
	printf("���������ַ�ѡ��˳����Ĳ���:\t");flushall();
	c= getchar();
	switch(c){
		case 'I':
		case 'i':
			InitSeqList2(SL);
			printf("������һ������Ϊ%d�Ŀյ�˳���!\n",SL->listsize);
			break;
		case 'C':
		case 'c':
			ClearSeqList(SL);
			break;
		case 'R':
		case 'r':
			printf("���ļ���ȡ��˳�������,�磺DSA021.tmp\t");
			scanf("%s", fname);
			strcat(tempFolder, fname);
			ReadSeqList(SL,tempFolder);
			SeqListPrint2(SL);			
			break;
		case 'A':
		case 'a':
			if(SL->length==0)
				i=1;
			else
				i = (int)RandElem(1, SL->length);
			printf("����[r]robot�Զ���ɡ�����,�˹�����...\n");	flushall();
			if((r=getchar())=='r'){
				printf("����������Ԫ�غͶ����ٶ���100����?\t");
				scanf("%d %d", &n, &speed);
				for(j=0;j<n-1;j++){
					x=RandElem(j, n);
					SeqListInsert(SL, i, x, speed);
					i = (int)RandElem(1, SL->length);
				}
			}
			else{
				printf("�������λ�ú�Ԫ��(����Ϊ%d):\t",SL->length);
				scanf("%d %d", &i, &x);
			}
			printf("��˳���SL��%dλ���ϲ���Ԫ�� %d :\n",i, x);
			SeqListInsert(SL, i, x, speed);
			SeqListPrint2(SL);			
			break;
		case 'D':
		case 'd':
			SeqListPrint2(SL);	
			if(GetSeqListLength(SL)==0)
				return 'q';
			printf("ɾ���ĸ��ڵ�(����λ��) �Ͷ����ٶ���100����?\t");
			scanf("%d %d", &x, &speed);
			i=LocateSeqListElem(SL, x);
			if(SeqListDelete(SL, i, &x,speed))
				printf("��˳���SL��%dλ����ɾ��Ԫ�� %d \n",i, x);
			else
				printf("ɾ��ʧ��!\n");
			break;
		case 'E':
		case 'e':
			if(GetSeqListLength(SL)==0){
				printf("˳���Ϊ�ձ�������!\n");
				return 'q';
			}
			printf("�޸��ĸ�λ���ϵĽڵ�,������λ��:\t");
			scanf("%d", &i);
			if( GetSeqListElem(SL, i, &x) != 0){
				printf("˳���SL��%dλ����Ԫ�� %d ���޸�Ϊ:\t",i, x);
				scanf("%d", &x);
				SeqListEdit(SL, i, x);
				SeqListPrint2(SL);			
			}
			else
				printf("�޸�ʧ��!\n");
			break;
		case 'F':
		case 'f':			
			printf("�����ĸ��ڵ�(����λ��)? \t");
			scanf("%d", &x);
			if(	i=LocateSeqListElem(SL, x) != 0)
				printf("˳���SL��%dλ����Ϊ���ҵ�Ԫ�� %d \n",i, x);
			else
				printf("����ʧ��:˳�����û��%d Ԫ��!\n", x);
			break;
		case 'S':
		case 's':			
			printf("����˳������ݵ��ļ���,�磺DSA021.tmp\t");
			scanf("%s", fname);
			strcat(tempFolder, fname);
			SeqListSave(SL,tempFolder);
			SeqListSave(SL, fname);
			break;

		case 'P':
		case 'p':
			SeqListPrint2(SL);//��ӡ			
			break;
		case 'Q':
		case 'q':
			return c;//�˳����Ա�
		default:
			printf("������˳������������ַ�,Q/q�˳�!\n");
			break;
	}
	return NULL;
}