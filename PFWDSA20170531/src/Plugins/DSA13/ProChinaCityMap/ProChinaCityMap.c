
#include "../DSA13.h"
#include "stdbool.h"
#include "ProChinaCityMap.h"

//��ͶӰ���й����е�ͼ
void ProChinaCityMap(void){
	
	init();	//��ʼ��

	loadData();//��������

	mapZoom(.8F,0,0);//��ʼ��ʾ

	drawCity();//���Ƴ��е�ͼ

	drawProCity();/*���Ʒ�ʡ���е�ͼ*/

	mapMenu();//��ͼ����

	quit();//�˳�
}

//��ȡ��������
void loadData(void){
	int i=0;
	FILE* pFile=fopen(".\\Data\\DSA131.dat","r");
	if(pFile==NULL){
		gotoxy(MAXX/2,MAXY/2);
		printf("%s","���ء��ַ��й����е�ͼ����ͼ����ʧ�ܣ�");	
		gotoxy(MAXX/2,MAXY/2+1);
		printf("%s","����.\\Data\\DSA131.dat�ļ��Ƿ���ڣ�");
		gotoxy(MAXX/2,MAXY/2+2);
		system("PAUSE");
		exit(0);
	}
	while( !feof(pFile)){
		fscanf(pFile, "%s %s %f %f\n",  &city[i].province, &city[i].city, &city[i].latitude, &city[i].longtitude);
		i++;
	}
	fclose(pFile);

	memcpy(cityCB, city, N*sizeof(CITY));
}
//���Ʋ�ɫ��ʡ���е�ͼ
void drawProCity(void){
	int i,j;
	char * provinceName=city[0].province;
	system("CLS");
	mapFrame();
	
	for(i=0,j=0;i<totalCities;i++){
		if(strcmp(provinceName, city[i].province)!=0){
			j++;
			provinceName=city[i].province;
		}
		SetConsoleTextAttribute(hOut, (WORD)(j%34));//��ʡ����ɫ

		gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude);
		printf("%c",002);
		gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude+1);
		printf("%s\n", city[i].city);
	}
	SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );//WHITE
}
//���Ƴ��е�ͼ
void drawCity(void){
	int i;
	system("CLS");
	mapFrame();
	for(i=0;i<totalCities;i++){
		gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude);
		printf("%c",002);
		gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude+1);
		printf("%s\n", city[i].city);
	}
}
//��ͼ����ƽ�Ʋ���
void mapZoom(float m, float x, float y)
{
	float dx,dy,sx,sy;
	int i;
	float minx,miny,maxx,maxy;
	minx=city[0].longtitude;
	miny=city[0].latitude;
	maxx=city[0].longtitude;
	maxy=city[0].latitude;

	/*�õ���������������Сֵ*/
	for(i=0;i<totalCities;i++){
		minx = minx > city[i].longtitude?city[i].longtitude:minx;//��Ŀ���㣿��
		miny = miny > city[i].latitude?city[i].latitude:miny;
		maxx = maxx < city[i].longtitude?city[i].longtitude:maxx;
		maxy = maxy < city[i].latitude?city[i].latitude:maxy;
	}
	
	minLat=minx; maxLat=maxx; minLon=miny; maxLon=maxy;
	dx = maxx-minx;
	dy = maxy-miny;
	sx = MAXX/dx;
	sy = MAXY/dy;

	minx -= x-0.2F;//x��߾�;
	maxy += y+0.2F;//y�ϱ߾�;

	for(i=0;i<totalCities;i++){
		city[i].longtitude = (city[i].longtitude - minx)*sx*m;/*m����ϵ��*/
		city[i].latitude = (city[i].latitude - miny)*sy*m+5;
	}
	drawProCity();/*��ͼ*/
}

//�˻������˵��������棩
void mapMenu(void)
{
	char flag='x';
	char city[20]="";
	float m=1.0F,mm=1.0F, x=1.0F, xx=1.0F, y=1.0F, yy=1.0F;
	
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);//RED
	gotoxy(MAXX/2-8,5);
	printf("%s","�ַ��й����е�ͼ");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );//WHITE

	do{
		gotoxy(MAXX/2-strlen(menustr)/2,MAXY+1);
		printf("%s",menustr);
		flag = getchar();
		switch(flag)
		{
			case '+':
				m=1.2F;
				mapZoom(mm*=m,0,0);
				break;
			case '-':
				m=0.8F;
				mapZoom(mm=mm*m,0,0);
				break;
			case 'f': case 'F':
				mapZoom(1,0,0);
				break;
			case 'r': case 'R':
				x=0.2F;
				mapZoom(mm,xx-=x,0);
				break;
			case 'u': case 'U':
				y=0.2F;
				mapZoom(mm,0, yy+=y);
				break;
			case 'q': case 'Q':
				gotoxy(MAXX/2-strlen(menustr)/2,MAXY+2);
				printf("%s","�������������: ");
				scanf("%s", city);
				flashCity(city);
				break;
			case 'i': case 'I':
				insertCity();
				break;
			case 'x':/*�˳�*/
			case 'X':
				system("CLS");
				break;
		}

	} while(flag!='x' && flag!='X');
}
//DDA��ֱ�߶��㷨
void lineDDA(int xa,int ya,int xb,int yb) 
{ 
	int Dx=xb-xa,Dy=yb-ya,steps,k; 
	float xin,yin,X=(float)xa,Y=(float)ya; 
	if(abs(Dx)>abs(Dy)) 
		steps=abs(Dx); 
	else 
		steps=abs(Dy); 

	xin=Dx/(float)steps; 
	yin=Dy/(float)steps; 
	gotoxy(ROUND(X),ROUND(Y));
	printf("%c",001);

	for(k=0;k<steps;k++){ 
		X=X+xin; 
		Y=Y+yin; 
		gotoxy(ROUND(X),ROUND(Y));
		printf("%c",001);
	} 
}
//��ͼ���
void mapFrame(void)
{
	int i,j,jj,m;
	char ann[10]="";
	float xmin=70,xmax=150,ymin=10,ymax=60,sx=1,sy=1;
	sx=MAXX/(xmax-xmin);
	sy=MAXY/(ymax-ymin);
	for(i=0;i<MAXX;i+= 10*(int)sx)
		for(j=0;j<MAXY;j+=5*(int)sy){
			for(m=0;m<10;m++)
				ann[m]=' ';
			jj=MAXY-j;
			if(i==0){//ά�ȣ�y��
				itoa((int)(j/sy+ymin),ann,10);
				gotoxy(i+1,jj-1);
				printf("%s",ann);
				lineDDA(0,jj,2,jj);
			}
			if(j==0){//���ȣ�x��
				 //itoa((int)(i/sx+xmin),ann,10);
				 sprintf(ann, "%d",(int)(i/sx+xmin));
				 gotoxy(i+1,jj-2);
				 printf("%s",ann);
				 lineDDA(i,jj,i,jj-2);
			}
		}
    lineDDA(0,0,MAXX,0);/*��Ļ��Χ*/
	lineDDA(0,0,0,MAXY);
	lineDDA(MAXX,0,MAXX,MAXY);
	lineDDA(0,MAXY,MAXX,MAXY);
}

//���ҳ���ʱ��˸
void flashCity(char* cityname){
	int i=0, j=0, noFind=0;

	for(i=0;i<totalCities;i++){
		if(strcmp(cityname, city[i].city)==0){
			for(;j<9;j++){//��˸9��
				SetConsoleTextAttribute(hOut, FOREGROUND_RED);//RED
				gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude);
				printf("%c",002);
				gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude+1);
				printf("%s\n", city[i].city);
				SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );//WHITE
				
				Sleep(100);
				gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude);
				printf("%c",002);
				gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude+1);
				printf("%s\n", city[i].city);
				
				Sleep(100);
				SetConsoleTextAttribute(hOut, FOREGROUND_RED);//RED
				gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude);
				printf("%c",002);
				gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude+1);
				printf("%s\n", city[i].city);
				SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );//WHITE
				
				gotoxy(MAXX/2-strlen(menustr)/2,MAXY+3);
				printf("%s %s %5.2f %5.2f",cityCB[i].province,cityCB[i].city,cityCB[i].longtitude,cityCB[i].latitude);
				noFind=1;
			}
		}
	}
	if(noFind==0){
		gotoxy(MAXX/2-strlen(menustr)/2,MAXY+3);
		printf("%s",strcat(cityname," ����ͼ�У�"));
	}
	Sleep(1000);
}
//�������ʼ��
void init(void){
	WORD att;
	COORD size = {120-1, 70-1};
	SMALL_RECT rc = {0,0, 120-1, 70-1}; // ���ô���λ�úʹ�С

	hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���
	hIn = GetStdHandle(STD_INPUT_HANDLE); // ��ȡ��׼�����豸���
	att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE ;
	// ��������ɫ���ı���ɫ�ǻ�ɫ
	SetConsoleTextAttribute(hOut, att);

	SetConsoleScreenBufferSize(hOut,size); // �������û�������С	
	SetConsoleWindowInfo(hOut,true ,&rc);
	
	SetConsoleTitle("�ַ��й����е�ͼ"); // ���ô��ڱ���
	//system("mode con:MAXXs=120 lines=70"); 
}
//�������˳�
void quit(void){
	gotoxy(MAXX/2,MAXY/2);
	printf("%s","�˳����ַ��й����е�ͼ�����ټ���2012-08-18\n");
	gotoxy(MAXX/2,MAXY/2+1);
	//system("PAUSE");
	//CloseHandle(hOut); // �رձ�׼����豸���
	//CloseHandle(hIn); // �رձ�׼�����豸���
}
//�����µĳ��У������浽�ļ���
void insertCity(void)
{
	WORD att;
	DWORD dwMode, dwOldMode;    /* ԭ����ģʽ����ģʽ */
	INPUT_RECORD mouseRec;
	DWORD state = 0, res;
	COORD pos = {0, 0};
	FILE* pFile=fopen(".\\Data\\DSA131.dat","a");

	att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE ;
	// ��������ɫ���ı���ɫ�ǻ�ɫ
	SetConsoleTextAttribute(hOut, att);

	while(1) //����ѭ��
	{
		GetConsoleMode(hIn, &dwOldMode);   /* ȡ�ÿ���̨ԭ����ģʽ */
		dwMode = dwOldMode | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hIn, dwMode);//�ܹؼ���

		ReadConsoleInput(hIn, &mouseRec, 1, &res);
		if (mouseRec.EventType == MOUSE_EVENT)
		{
			// �Ҽ�������˳�ѭ��
			//if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)//?
			if (mouseRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				gotoxy(MAXX/2-strlen(menustr)/2,MAXY+3);
				printf("%s","����������У�");
				break;
			}
			
			pos = mouseRec.Event.MouseEvent.dwMousePosition;
			DispMousePos(pos);
			if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && totalCities<NN){
				FillConsoleOutputCharacter(hOut, '\001', 1, pos, NULL); 
				gotoxy(MAXX/2-strlen(menustr)/2,MAXY+3);
				printf("%s","������������ڵ�ʡ�ݡ��������ơ�ά�Ⱥ;��ȣ��Ҽ���������");
			
				SetConsoleMode(hIn, dwOldMode);//�ܹؼ���
				totalCities++;
				scanf("%s %s %f %f", &city[totalCities].province, &city[totalCities].city, \
					&city[totalCities].latitude, &city[totalCities].longtitude);
				fprintf(pFile, "\n%s %s %4.2f %5.2f", city[totalCities].province, city[totalCities].city, \
					city[totalCities].latitude, city[totalCities].longtitude);				
			}

		}
	} 
	SetConsoleCursorPosition(hOut, pos); // ���ù��λ��
	
	fclose(pFile);
}
//��ʾ���λ��
void DispMousePos(COORD pos) 
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;COORD home;WORD att0;
	char s[20];
	GetConsoleScreenBufferInfo( hOut, &bInfo ); 
	home.X = 0;//0��
	home.Y = bInfo.dwSize.Y-1;//���һ��
	att0 = BACKGROUND_INTENSITY ;
	FillConsoleOutputAttribute(hOut, att0, bInfo.dwSize.X, home, NULL);
	FillConsoleOutputCharacter(hOut, ' ', bInfo.dwSize.X, home, NULL);

	sprintf(s,"�����Ļ���꣺ X = %2lu, Y = %2lu",pos.X, pos.Y);
	SetConsoleTextAttribute(hOut, att0);
	SetConsoleCursorPosition(hOut, home);
	WriteConsole(hOut, s, strlen(s), NULL, NULL);
	SetConsoleTextAttribute(hOut, bInfo.wAttributes); // �ָ�ԭ��������
	SetConsoleCursorPosition(hOut, bInfo.dwCursorPosition); // �ָ�ԭ���Ĺ��λ��
}
//����,Ҳ����system("CLS");
void ClearScreen(void)
{
	unsigned long size;
	COORD home = {0, 0};
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo ); 
	size = bInfo.dwSize.X * bInfo.dwSize.Y;
	FillConsoleOutputAttribute(hOut, bInfo.wAttributes, size, home, NULL);
	FillConsoleOutputCharacter(hOut, ' ', size, home, NULL);
}