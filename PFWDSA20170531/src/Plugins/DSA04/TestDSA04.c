/*
*文件：TestDSA04.C
*插件文件，链表的使用：多项式运算，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA04.h"

char gVersion[20];

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
	int i;
	FILE *pf;
	polynomial *c,  *polyArray[POLY];//polyArray称为指数数组！
	char tempFolder[100]=".\\Temp\\DSA041.tmp";

	pf=fopen(tempFolder, "w");

	//从DSA041.dat读取多项式的数据
	CreatePolynFromFile(polyArray, ".\\Data\\DSA041.dat");
	
	//每四个一组：两个加数和一个答案及AddPoly算法都保存在tempFolder.data文件中
	for(i=0; i<nPoly; i += 3)
	{
		printf("多项式%d：\t\t", i);
		PrintPolyn(polyArray[i]);
		fprintf(pf, "测试案例 %d\n", i);
		SavePolyn(pf, polyArray[i]);

		printf("多项式%d：\t\t", i+1);
		PrintPolyn(polyArray[i+1]);
		SavePolyn(pf, polyArray[i+1]);

		printf("多项式%d + %d 的答案：\t", i, i+1);
		PrintPolyn(polyArray[i+2]);
		SavePolyn(pf, polyArray[i+2]);

		AddPoly(&c, polyArray[i], polyArray[i+1]);
		printf("多项式%d + %d 的结果：\t", i, i+1);
		PrintPolyn(c);
		SavePolyn(pf, c);
		if(IsEqualPoly(polyArray[i+2], c)){
			printf("OK!\n");
			fprintf(pf, "AddPoly OK!\n\n");
		}
		else{
			printf("FALSE!\n");
			fprintf(pf, "AddPoly FALSE!\n\n");
		}
		
		DestroyPoly(c);

		printf("\n");
	}
	fclose(pf);
	system(tempFolder);

	for(i=0; i< nPoly; i++)
		DestroyPoly(polyArray[i]);

}
