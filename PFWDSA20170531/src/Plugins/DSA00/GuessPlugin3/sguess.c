/* ��ʼ�� */
score=0;
totalscore=0;

/* ��10�λ���Ʒ�(score)�²�magic */
void sGuessNumber(int magic)
{
	int i;
	int answer;
	int times=0;

	for (i=0; i<10; i++)
	{
		printf("������һ��������");
		scanf("%d", &answer);
		times++;
		
		if (answer == magic)
			break;
		else if (answer > magic)
				printf("̫����!\n");
			else
				printf("̫С��!\n");
	}
	
	printf("�Ѳ�[%2d]��!\n", times);
	score = times;
	totalscore += score;
	printf("�㱾�ε÷� %d, �ۼƵ÷� %d \n", score, totalscore);
}