/*
*文件：DSA07.C
*插件文件，特殊线性表：堆栈和队列，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA07.h"

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

void TestMatch(void);
void TestPalindrome(void);
void TestPlusMinusQueue(void);

void DSAInterface(void){
	int i=0;
	while(i!=4){
		system("CLS");
		printf("\n堆栈和队列算法演示\
			\n请输入数字选择:\n1 TestMatch\n2 TestPalindrome\
			\n3 TestPlusMinusQueue\n4 退出\n");
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

	//1测试指定数据
	ElemType *express="(){{}";
	printf("\n1测试指定数据:\t");
	if(Match(express))
		printf("%s 括号匹配!\n", express);
	else
		printf("%s 括号不匹配!\n", express);

	//2测试用户输入的随机数据
	printf("\n2请用户输入scanf表达式:\t");
	scanf("%s", exps);//字符串的空格后面不被读取
	express = exps;
	if(Match(express))
		printf("%s 括号匹配!\n", express);
	else
		printf("%s 括号不匹配!\n", express);

	flushall();

	//3使用字符输入函数gets
	printf("\n3请输入函数gets表达式:\t");
	gets(express);//正行，包括空格后的字符
	if(Match(express))
		printf("%s 括号匹配!\n", express);
	else
		printf("%s 括号不匹配!\n", express);

	flushall();
	//4fgets从文件中读取字符串
	printf("\n4文件中读取字符串函数fgets表达式:\n");
	if((pf=fopen("Data\\DSA071.dat", "r"))==NULL){
		printf("打开文件 DSA071.dat 失败!"); exit(0);
	}
	fgets(exps, 100, pf);
	if(Match(exps))
		printf("%s 括号匹配!\n", exps);
	else
		printf("%s 括号不匹配!\n", exps);
	fclose(pf);

	flushall();
	//5fgets从文件中读取多个字符串
	printf("\n5文件中读取多个字符串函数fgets表达式:\n");
	if((pf=fopen("Data\\DSA072.dat", "r"))==NULL){
		printf("打开文件 DSA072.dat 失败!"); exit(0);
	}
	while(fgets(exps, 100, pf) !=NULL){
		if(Match(exps))
			printf("%s 括号匹配!\n", exps);
		else
			printf("%s 括号不匹配!\n", exps);
	}
	fclose(pf);

}

void TestPalindrome(void){
	
	ElemType str[200];
	FILE * pf;
	//从文件中读取多个字符串
	printf("\n从文件中读取多个字符串函数fgets表达式:\n");
	if((pf=fopen("Data\\DSA073.dat", "r"))==NULL){
		printf("打开文件 DSA073.dat 失败!"); exit(0);
	}
	while(fgets(str, 200, pf) !=NULL){
		if(Palindrome(str))
			printf("%s  是回文!\n", str);
		else
			printf("%s  不是回文!\n", str);
	}
	fclose(pf);

}
void TestPlusMinusQueue(void){
	
	PlusMinusQueue();//可能不懂？
	system("PAUSE");
	myPlusMinusQueue();//自己写这样的程序，帮助自己理解！
	system("PAUSE");
	PlusMinusQueueFromFile();//做更好的自己！
}