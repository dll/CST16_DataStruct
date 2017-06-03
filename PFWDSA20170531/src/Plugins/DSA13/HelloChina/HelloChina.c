#include<stdio.h>
#include<windows.h>

void gotoxy(int x, int y) //x为列坐标,y为行坐标
{
 COORD pos = {x,y};//定义坐标
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//设置一个句柄
 SetConsoleCursorPosition(hOut, pos);
} 

int main(){
	
	gotoxy(10,10);
	printf("%c\n",001);
	gotoxy(10,11);
	printf("Hello China!\n");
	gotoxy(10,12);
	system("PAUSE");

	return 0;
}
