/*10��Ĭ��(default)ģʽ�²�magic */
void dGuessNumber(int magic)
{
	int i;
	int answer;
	int times=0;

	for (i=0; i<10; i++)
	{
		printf("\n������һ������:");
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
}
