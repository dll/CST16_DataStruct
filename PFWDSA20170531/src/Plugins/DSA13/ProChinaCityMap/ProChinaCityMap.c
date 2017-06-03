
#include "../DSA13.h"
#include "stdbool.h"
#include "ProChinaCityMap.h"

//带投影的中国城市地图
void ProChinaCityMap(void){
	
	init();	//初始化

	loadData();//加载数据

	mapZoom(.8F,0,0);//初始显示

	drawCity();//绘制城市地图

	drawProCity();/*绘制分省城市地图*/

	mapMenu();//地图操作

	quit();//退出
}

//读取城市数据
void loadData(void){
	int i=0;
	FILE* pFile=fopen(".\\Data\\DSA131.dat","r");
	if(pFile==NULL){
		gotoxy(MAXX/2,MAXY/2);
		printf("%s","加载《字符中国城市地图》地图数据失败！");	
		gotoxy(MAXX/2,MAXY/2+1);
		printf("%s","请检查.\\Data\\DSA131.dat文件是否存在！");
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
//绘制彩色分省城市地图
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
		SetConsoleTextAttribute(hOut, (WORD)(j%34));//按省份着色

		gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude);
		printf("%c",002);
		gotoxy((int)city[i].longtitude,MAXY-(int)city[i].latitude+1);
		printf("%s\n", city[i].city);
	}
	SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );//WHITE
}
//绘制城市地图
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
//地图缩放平移操作
void mapZoom(float m, float x, float y)
{
	float dx,dy,sx,sy;
	int i;
	float minx,miny,maxx,maxy;
	minx=city[0].longtitude;
	miny=city[0].latitude;
	maxx=city[0].longtitude;
	maxy=city[0].latitude;

	/*得到城市坐标的最大、最小值*/
	for(i=0;i<totalCities;i++){
		minx = minx > city[i].longtitude?city[i].longtitude:minx;//三目运算？：
		miny = miny > city[i].latitude?city[i].latitude:miny;
		maxx = maxx < city[i].longtitude?city[i].longtitude:maxx;
		maxy = maxy < city[i].latitude?city[i].latitude:maxy;
	}
	
	minLat=minx; maxLat=maxx; minLon=miny; maxLon=maxy;
	dx = maxx-minx;
	dy = maxy-miny;
	sx = MAXX/dx;
	sy = MAXY/dy;

	minx -= x-0.2F;//x左边距;
	maxy += y+0.2F;//y上边距;

	for(i=0;i<totalCities;i++){
		city[i].longtitude = (city[i].longtitude - minx)*sx*m;/*m比例系数*/
		city[i].latitude = (city[i].latitude - miny)*sy*m+5;
	}
	drawProCity();/*绘图*/
}

//人机交互菜单（主界面）
void mapMenu(void)
{
	char flag='x';
	char city[20]="";
	float m=1.0F,mm=1.0F, x=1.0F, xx=1.0F, y=1.0F, yy=1.0F;
	
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);//RED
	gotoxy(MAXX/2-8,5);
	printf("%s","字符中国城市地图");
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
				printf("%s","请输入城市名称: ");
				scanf("%s", city);
				flashCity(city);
				break;
			case 'i': case 'I':
				insertCity();
				break;
			case 'x':/*退出*/
			case 'X':
				system("CLS");
				break;
		}

	} while(flag!='x' && flag!='X');
}
//DDA画直线段算法
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
//地图框架
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
			if(i==0){//维度，y轴
				itoa((int)(j/sy+ymin),ann,10);
				gotoxy(i+1,jj-1);
				printf("%s",ann);
				lineDDA(0,jj,2,jj);
			}
			if(j==0){//经度，x轴
				 //itoa((int)(i/sx+xmin),ann,10);
				 sprintf(ann, "%d",(int)(i/sx+xmin));
				 gotoxy(i+1,jj-2);
				 printf("%s",ann);
				 lineDDA(i,jj,i,jj-2);
			}
		}
    lineDDA(0,0,MAXX,0);/*屏幕范围*/
	lineDDA(0,0,0,MAXY);
	lineDDA(MAXX,0,MAXX,MAXY);
	lineDDA(0,MAXY,MAXX,MAXY);
}

//查找城市时闪烁
void flashCity(char* cityname){
	int i=0, j=0, noFind=0;

	for(i=0;i<totalCities;i++){
		if(strcmp(cityname, city[i].city)==0){
			for(;j<9;j++){//闪烁9次
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
		printf("%s",strcat(cityname," 不在图中！"));
	}
	Sleep(1000);
}
//主程序初始化
void init(void){
	WORD att;
	COORD size = {120-1, 70-1};
	SMALL_RECT rc = {0,0, 120-1, 70-1}; // 重置窗口位置和大小

	hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
	hIn = GetStdHandle(STD_INPUT_HANDLE); // 获取标准输入设备句柄
	att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE ;
	// 背景是蓝色，文本颜色是黄色
	SetConsoleTextAttribute(hOut, att);

	SetConsoleScreenBufferSize(hOut,size); // 重新设置缓冲区大小	
	SetConsoleWindowInfo(hOut,true ,&rc);
	
	SetConsoleTitle("字符中国城市地图"); // 设置窗口标题
	//system("mode con:MAXXs=120 lines=70"); 
}
//主程序退出
void quit(void){
	gotoxy(MAXX/2,MAXY/2);
	printf("%s","退出《字符中国城市地图》，再见！2012-08-18\n");
	gotoxy(MAXX/2,MAXY/2+1);
	//system("PAUSE");
	//CloseHandle(hOut); // 关闭标准输出设备句柄
	//CloseHandle(hIn); // 关闭标准输入设备句柄
}
//插入新的城市，并保存到文件中
void insertCity(void)
{
	WORD att;
	DWORD dwMode, dwOldMode;    /* 原来的模式与新模式 */
	INPUT_RECORD mouseRec;
	DWORD state = 0, res;
	COORD pos = {0, 0};
	FILE* pFile=fopen(".\\Data\\DSA131.dat","a");

	att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE ;
	// 背景是蓝色，文本颜色是黄色
	SetConsoleTextAttribute(hOut, att);

	while(1) //无限循环
	{
		GetConsoleMode(hIn, &dwOldMode);   /* 取得控制台原来的模式 */
		dwMode = dwOldMode | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hIn, dwMode);//很关键！

		ReadConsoleInput(hIn, &mouseRec, 1, &res);
		if (mouseRec.EventType == MOUSE_EVENT)
		{
			// 右键击鼠标退出循环
			//if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)//?
			if (mouseRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				gotoxy(MAXX/2-strlen(menustr)/2,MAXY+3);
				printf("%s","结束插入城市！");
				break;
			}
			
			pos = mouseRec.Event.MouseEvent.dwMousePosition;
			DispMousePos(pos);
			if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && totalCities<NN){
				FillConsoleOutputCharacter(hOut, '\001', 1, pos, NULL); 
				gotoxy(MAXX/2-strlen(menustr)/2,MAXY+3);
				printf("%s","请输入城市所在的省份、城市名称、维度和经度（右键结束）：");
			
				SetConsoleMode(hIn, dwOldMode);//很关键！
				totalCities++;
				scanf("%s %s %f %f", &city[totalCities].province, &city[totalCities].city, \
					&city[totalCities].latitude, &city[totalCities].longtitude);
				fprintf(pFile, "\n%s %s %4.2f %5.2f", city[totalCities].province, city[totalCities].city, \
					city[totalCities].latitude, city[totalCities].longtitude);				
			}

		}
	} 
	SetConsoleCursorPosition(hOut, pos); // 设置光标位置
	
	fclose(pFile);
}
//显示鼠标位置
void DispMousePos(COORD pos) 
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;COORD home;WORD att0;
	char s[20];
	GetConsoleScreenBufferInfo( hOut, &bInfo ); 
	home.X = 0;//0列
	home.Y = bInfo.dwSize.Y-1;//最后一行
	att0 = BACKGROUND_INTENSITY ;
	FillConsoleOutputAttribute(hOut, att0, bInfo.dwSize.X, home, NULL);
	FillConsoleOutputCharacter(hOut, ' ', bInfo.dwSize.X, home, NULL);

	sprintf(s,"鼠标屏幕坐标： X = %2lu, Y = %2lu",pos.X, pos.Y);
	SetConsoleTextAttribute(hOut, att0);
	SetConsoleCursorPosition(hOut, home);
	WriteConsole(hOut, s, strlen(s), NULL, NULL);
	SetConsoleTextAttribute(hOut, bInfo.wAttributes); // 恢复原来的属性
	SetConsoleCursorPosition(hOut, bInfo.dwCursorPosition); // 恢复原来的光标位置
}
//清屏,也可用system("CLS");
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