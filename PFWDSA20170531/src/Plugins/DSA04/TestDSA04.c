/*
*�ļ���TestDSA04.C
*����ļ��������ʹ�ã�����ʽ���㣬DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include"DSA04.h"

char gVersion[20];

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
	int i;
	FILE *pf;
	polynomial *c,  *polyArray[POLY];//polyArray��Ϊָ�����飡
	char tempFolder[100]=".\\Temp\\DSA041.tmp";

	pf=fopen(tempFolder, "w");

	//��DSA041.dat��ȡ����ʽ������
	CreatePolynFromFile(polyArray, ".\\Data\\DSA041.dat");
	
	//ÿ�ĸ�һ�飺����������һ���𰸼�AddPoly�㷨��������tempFolder.data�ļ���
	for(i=0; i<nPoly; i += 3)
	{
		printf("����ʽ%d��\t\t", i);
		PrintPolyn(polyArray[i]);
		fprintf(pf, "���԰��� %d\n", i);
		SavePolyn(pf, polyArray[i]);

		printf("����ʽ%d��\t\t", i+1);
		PrintPolyn(polyArray[i+1]);
		SavePolyn(pf, polyArray[i+1]);

		printf("����ʽ%d + %d �Ĵ𰸣�\t", i, i+1);
		PrintPolyn(polyArray[i+2]);
		SavePolyn(pf, polyArray[i+2]);

		AddPoly(&c, polyArray[i], polyArray[i+1]);
		printf("����ʽ%d + %d �Ľ����\t", i, i+1);
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
