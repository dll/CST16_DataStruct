/*
*�ļ���DSA00.C
*����ļ���ʵ�ָ���ģʽ������Ϸ��DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include "DSA00.h"

//�ṹ������
void inmain(void);
//ģ�黯����
void Init(void);
void BeginGuess(void);
void Goodbye(void);
int MakeNumber(void);
void GuessNumber(int magic);
void modulemain(void);

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
void DSAInterface(void){
	int i, g;
	char guessMenu[8][20]={{"\n[0]Ĭ�ϲ���"},{"\n[1]��ʾ����"},{"\n[2]��������"},\
	{"\n[3]�Ʒֲ���"},{"\n[4]�޴β���"},{"\n[5]�ṹ��"},{"\n[6]ģ�黯"},{"\n[7]�˳�"}};
	while(1){
		for(i=0; i<8;i++)
			printf("%s", guessMenu[i]);
		printf("\n��ѡ�����ģʽ:0,1,2,3,4,5,6,7:");
		scanf("%d", &i);
		switch(i){
			case 0:
				dGuessNumber(MakeNumber());
				break;
			case 1:
				pGuessNumber(MakeNumber());
				break;
			case 2:
				rGuessNumber(MakeNumber());
				break;
			case 3:
				sGuessNumber(MakeNumber());
				break;
			case 4:
				tGuessNumber(MakeNumber());
				break;
			case 5:
				inmain();//�ṹ��
				break;
			case 6:
				modulemain();//ģ�黯
				break;
			case 7:
				return;
			default:
				printf("������[0-7]֮�������!\n");
				break;
		}
	}
}
////////////////////////////
void inmain(void)
{
	char cont;
	int magic;
	int i;
	int answer;
	int times=0;

	srand(time(NULL));
	do
	{
		magic=rand()%100+1;
		for (i=0; i<10; i++)
		{
			printf("������һ������\n");
			scanf("%d", &answer);
			times++;
			
			if (answer == magic)
			{
				break;
			}
			else if (answer > magic)
			{
				printf("̫����.\n");
			}
			else
			{
				printf("̫����.\n");
			}
		}
		
		printf("�´�=%d\n", times);

		while (getchar() != '\n')
			;
		printf("������?(Y/N)");
		cont = getchar();
	} while(cont != 'n' && cont != 'N');
}

////////////////////////////
void modulemain(void)
{
	Init();
	BeginGuess();
	Goodbye();
}

/* ��ʼ�� */
void Init(void)
{
	srand(time(NULL));
}

/* ������ */
void BeginGuess(void)
{
	char cont;
	int magic;

	do
	{
		magic=MakeNumber();
		GuessNumber(magic);

		while (getchar() != '\n')
			;
		printf("������?(Y/N)");
		cont = getchar();
	} while(cont != 'n' && cont != 'N');
}

void Goodbye(void)
{

}

/* ���ش�1��100������� */
int MakeNumber(void)
{
	//return rand()%100+1;
	//��DSATestServices.libģ���ڣ���PFWDSA����ṩ�ĺ���RandInt
	return RandInt(1,100);
}

/* ��10�λ���²�magic */
void GuessNumber(int magic)
{
	int i;
	int answer;
	int times=0;

	for (i=0; i<10; i++)
	{
		printf("����һ������.\n");
		scanf("%d", &answer);
		times++;
		
		if (answer == magic)
		{
			break;
		}
		else if (answer > magic)
		{
			printf("̫����.\n");
		}
		else
		{
			printf("̫����.\n");
		}
	}
	
	printf("�´�=%d\n", times);
}
