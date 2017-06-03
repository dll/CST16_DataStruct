#ifndef PROCHINACITYMAP_H
#define PROCHINACITYMAP_H

#define NN 625+100
#define N 625
#define MAXX 110
#define MAXY 60

int totalCities=N;

float minLat,maxLat, minLon, maxLon;
//宏函数
#define ROUND(val) (int)(val+0.5) 

typedef struct tagCHINACITY{
	char province[20],city[20];
	float longtitude, latitude;
}CITY;

CITY city[NN], cityCB[NN];

HANDLE hOut;//标准输出句柄
HANDLE hIn;//标准输入句柄

char * menustr = "放大+ 缩小- 全屏f 左移r 上移u 查询q 插入i 退出x";

void mapFrame(void);
void mapZoom(float m, float x, float y);
void loadData(void);
void drawProCity(void);
void drawCity(void);
void mapMenu(void);
void lineDDA(int xa,int ya,int xb,int yb); 
void mapFrame(void);
void flashCity(char* city);
void init(void);
void quit(void);
void insertCity(void);
void ClearScreen(void);
void DispMousePos(COORD pos);
void insertCity(void);

#endif