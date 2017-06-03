/*
*�ļ���DSA07.C
*����ļ����������Ա���ջ�Ͷ��У�DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include"DSA07.h"

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

void TestMatch(void);
void TestPalindrome(void);
void TestPlusMinusQueue(void);

void DSAInterface(void){
	int i=0;
	while(i!=4){
		system("CLS");
		printf("\n��ջ�Ͷ����㷨��ʾ\
			\n����������ѡ��:\n1 TestMatch\n2 TestPalindrome\
			\n3 TestPlusMinusQueue\n4 �˳�\n");
		flushall();
		scanf("%d", &i);
		switch(i){
			case 1:
			TestMatch();break;
			case 2:
			TestPalindrome();break;
			case 3:
			TestPlusMinusQueue();break;
			case 4:return;
		}
		system("PAUSE");
	}
}

void  TestMatch(void){
	
	ElemType exps[100];
	FILE * pf;

	//1����ָ������
	ElemType *express="(){{}";
	printf("\n1����ָ������:\t");
	if(Match(express))
		printf("%s ����ƥ��!\n", express);
	else
		printf("%s ���Ų�ƥ��!\n", express);

	//2�����û�������������
	printf("\n2���û�����scanf���ʽ:\t");
	scanf("%s", exps);//�ַ����Ŀո���治����ȡ
	express = exps;
	if(Match(express))
		printf("%s ����ƥ��!\n", express);
	else
		printf("%s ���Ų�ƥ��!\n", express);

	flushall();

	//3ʹ���ַ����뺯��gets
	printf("\n3�����뺯��gets���ʽ:\t");
	gets(express);//���У������ո����ַ�
	if(Match(express))
		printf("%s ����ƥ��!\n", express);
	else
		printf("%s ���Ų�ƥ��!\n", express);

	flushall();
	//4fgets���ļ��ж�ȡ�ַ���
	printf("\n4�ļ��ж�ȡ�ַ�������fgets���ʽ:\n");
	if((pf=fopen("Data\\DSA071.dat", "r"))==NULL){
		printf("���ļ� DSA071.dat ʧ��!"); exit(0);
	}
	fgets(exps, 100, pf);
	if(Match(exps))
		printf("%s ����ƥ��!\n", exps);
	else
		printf("%s ���Ų�ƥ��!\n", exps);
	fclose(pf);

	flushall();
	//5fgets���ļ��ж�ȡ����ַ���
	printf("\n5�ļ��ж�ȡ����ַ�������fgets���ʽ:\n");
	if((pf=fopen("Data\\DSA072.dat", "r"))==NULL){
		printf("���ļ� DSA072.dat ʧ��!"); exit(0);
	}
	while(fgets(exps, 100, pf) !=NULL){
		if(Match(exps))
			printf("%s ����ƥ��!\n", exps);
		else
			printf("%s ���Ų�ƥ��!\n", exps);
	}
	fclose(pf);

}

void TestPalindrome(void){
	
	ElemType str[200];
	FILE * pf;
	//���ļ��ж�ȡ����ַ���
	printf("\n���ļ��ж�ȡ����ַ�������fgets���ʽ:\n");
	if((pf=fopen("Data\\DSA073.dat", "r"))==NULL){
		printf("���ļ� DSA073.dat ʧ��!"); exit(0);
	}
	while(fgets(str, 200, pf) !=NULL){
		if(Palindrome(str))
			printf("%s  �ǻ���!\n", str);
		else
			printf("%s  ���ǻ���!\n", str);
	}
	fclose(pf);

}
void TestPlusMinusQueue(void){
	
	PlusMinusQueue();//���ܲ�����
	system("PAUSE");
	myPlusMinusQueue();//�Լ�д�����ĳ��򣬰����Լ���⣡
	system("PAUSE");
	PlusMinusQueueFromFile();//�����õ��Լ���
}