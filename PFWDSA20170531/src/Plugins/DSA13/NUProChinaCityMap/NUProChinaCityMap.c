#include"../DSA13.h"

//不带投影的中国城市地图
void NUProChinaCityMap(void){
	
	char province[20],city[20];
	float lontitude=0.0F, latitude=0.0F;

	FILE * pFile=fopen(".\\Data\\DSA131.dat","r");
	printf("直接显示中国城市在默认控制台窗口：25*80\n");
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
	printf("直接显示中国城市在140*70 控制台窗口\n");
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