/* ��ʼ�� */
guesstimes=0;

/* ��guesstimes��(times)����²�magic */
void tGuessNumber(int magic)
{
	int i;
	int answer;
	int times=0;
	int flag=0;

	printf("��������Ҫ�����Ĵ���: ");
	scanf("%d", &guesstimes);
	for (i=0; i<guesstimes; i++)
	{
		printf("���Ѳ� %d ��! ������һ������:", times);
		scanf("%d", &answer);
		times++;
		
		if (answer == magic)
		{
			flag=1;
			break;
		}
		else if (answer > magic)
			printf("̫����!\n");
		else
			printf("̫С��!\n");
	}
	printf("�Ѳ�[ %d ]��\n", times);
	if(flag==0)
		printf("��û�в���!\n");
	else
		printf("��ϲ, �������!\n");
}