/*10次默认(default)模式猜测magic */
void dGuessNumber(int magic)
{
	int i;
	int answer;
	int times=0;

	for (i=0; i<10; i++)
	{
		printf("\n请输入一个整数:");
		scanf("%d", &answer);
		times++;
		
		if (answer == magic)
			break;
		else if (answer > magic)
			printf("太多了!\n");
		else
			printf("太小了!\n");
	}
	
	printf("已猜[%2d]次!\n", times);
}
