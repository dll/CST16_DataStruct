/* 初始化 */
guesstimes=0;

/* 给guesstimes次(times)机会猜测magic */
void tGuessNumber(int magic)
{
	int i;
	int answer;
	int times=0;
	int flag=0;

	printf("请输入你要猜数的次数: ");
	scanf("%d", &guesstimes);
	for (i=0; i<guesstimes; i++)
	{
		printf("你已猜 %d 次! 请输入一个整数:", times);
		scanf("%d", &answer);
		times++;
		
		if (answer == magic)
		{
			flag=1;
			break;
		}
		else if (answer > magic)
			printf("太大了!\n");
		else
			printf("太小了!\n");
	}
	printf("已猜[ %d ]次\n", times);
	if(flag==0)
		printf("你没有猜中!\n");
	else
		printf("恭喜, 你猜中啦!\n");
}