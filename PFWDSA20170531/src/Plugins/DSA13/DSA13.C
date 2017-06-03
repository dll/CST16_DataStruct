#include"DSA13.h"
//定位函数，行列屏幕坐标，单位像素
void gotoxy(int x, int y) //x为列坐标,y为行坐标
{
	COORD pos = {x,y};//定义坐标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//设置一个句柄
	SetConsoleCursorPosition(hOut, pos);
} 