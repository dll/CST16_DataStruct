/* 初始化 */
score=0;
totalscore=0;

/* 给10次机会计分(score)猜测magic */
void sGuessNumber(int magic)
{
	int i;
	int answer;
	int times=0;

	for (i=0; i<10; i++)
	{
		printf("请输入一个整数：");
		scanf("%d", &answer);
		times++;
		
		if (answer == magic)
			break;
		else if (answer > magic)
				printf("太大了!\n");
			else
				printf("太小了!\n");
	}
	
	printf("已猜[%2d]次!\n", times);
	score = times;
	totalscore += score;
	printf("你本次得分 %d, 累计得分 %d \n", score, totalscore);
}