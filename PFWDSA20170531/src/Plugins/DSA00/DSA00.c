/*
*文件：DSA00.C
*插件文件，实现各种模式猜数游戏，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include "DSA00.h"

//结构化猜数
void inmain(void);
//模块化猜数
void Init(void);
void BeginGuess(void);
void Goodbye(void);
int MakeNumber(void);
void GuessNumber(int magic);
void modulemain(void);

char gVersion[20];
char gInterface[20];
//插件信息
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
//插件框架的接口
void DSAInterface(void){
	int i, g;
	char guessMenu[8][20]={{"\n[0]默认猜数"},{"\n[1]提示猜数"},{"\n[2]机器猜数"},\
	{"\n[3]计分猜数"},{"\n[4]限次猜数"},{"\n[5]结构化"},{"\n[6]模块化"},{"\n[7]退出"}};
	while(1){
		for(i=0; i<8;i++)
			printf("%s", guessMenu[i]);
		printf("\n请选择猜数模式:0,1,2,3,4,5,6,7:");
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
				inmain();//结构化
				break;
			case 6:
				modulemain();//模块化
				break;
			case 7:
				return;
			default:
				printf("请输入[0-7]之间的数字!\n");
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
			printf("请输入一个整数\n");
			scanf("%d", &answer);
			times++;
			
			if (answer == magic)
			{
				break;
			}
			else if (answer > magic)
			{
				printf("太高啦.\n");
			}
			else
			{
				printf("太低啦.\n");
			}
		}
		
		printf("猜次=%d\n", times);

		while (getchar() != '\n')
			;
		printf("继续吗?(Y/N)");
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

/* 初始化 */
void Init(void)
{
	srand(time(NULL));
}

/* 主流程 */
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
		printf("继续吗?(Y/N)");
		cont = getchar();
	} while(cont != 'n' && cont != 'N');
}

void Goodbye(void)
{

}

/* 返回从1到100的随机数 */
int MakeNumber(void)
{
	//return rand()%100+1;
	//在DSATestServices.lib模块内，由PFWDSA框架提供的函数RandInt
	return RandInt(1,100);
}

/* 给10次机会猜测magic */
void GuessNumber(int magic)
{
	int i;
	int answer;
	int times=0;

	for (i=0; i<10; i++)
	{
		printf("输入一个整数.\n");
		scanf("%d", &answer);
		times++;
		
		if (answer == magic)
		{
			break;
		}
		else if (answer > magic)
		{
			printf("太高了.\n");
		}
		else
		{
			printf("太低了.\n");
		}
	}
	
	printf("猜次=%d\n", times);
}
