/*
*猜数游戏的基础模块
*
*
*
*/

#include"bguess.h"

/* 初始化 */
void Init(void)
{
	srand(time(NULL));
}
/* 结束 */
void Goodbye(void)
{
	printf("退出猜数插件!\n");
}
/* 返回从1到100的随机数 */
int MakeNumber(void)
{
	return rand()%100+1;
}
