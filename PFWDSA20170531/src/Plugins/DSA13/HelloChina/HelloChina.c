#include<stdio.h>
#include<windows.h>

void gotoxy(int x, int y) //xΪ������,yΪ������
{
 COORD pos = {x,y};//��������
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//����һ�����
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
