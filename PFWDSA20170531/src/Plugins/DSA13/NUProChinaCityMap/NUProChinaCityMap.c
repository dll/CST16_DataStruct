#include"../DSA13.h"

//����ͶӰ���й����е�ͼ
void NUProChinaCityMap(void){
	
	char province[20],city[20];
	float lontitude=0.0F, latitude=0.0F;

	FILE * pFile=fopen(".\\Data\\DSA131.dat","r");
	printf("ֱ����ʾ�й�������Ĭ�Ͽ���̨���ڣ�25*80\n");
	system("PAUSE");
	while( !feof(pFile)){
		fscanf(pFile, "%s %s %f %f\n",  &province, &city, &latitude, &lontitude);
		gotoxy((int)lontitude,(int)latitude);
		printf("%c",001);
		gotoxy((int)lontitude,(int)latitude+1);
		printf("%s\n", city);
	}
	fclose(pFile);

	system("PAUSE");
	system("cls");
	printf("ֱ����ʾ�й�������140*70 ����̨����\n");
	system("PAUSE");

	pFile=fopen(".\\Data\\DSA131.dat","r");
	system("mode con:cols=140 lines=70"); 

	while( !feof(pFile)){
		fscanf(pFile, "%s %s %f %f\n",  &province, &city, &latitude, &lontitude);
		gotoxy((int)lontitude,(int)latitude);
		printf("%c",001);
		gotoxy((int)lontitude,(int)latitude+1);
		printf("%s\n", city);
	}
	fclose(pFile);
	gotoxy(0,0);
	//system("PAUSE");
}