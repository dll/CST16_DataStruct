/*
*������Ϸ�Ļ���ģ��
*
*
*
*/

#include"bguess.h"

/* ��ʼ�� */
void Init(void)
{
	srand(time(NULL));
}
/* ���� */
void Goodbye(void)
{
	printf("�˳��������!\n");
}
/* ���ش�1��100������� */
int MakeNumber(void)
{
	return rand()%100+1;
}
