
/* ��10�λ���²�magic �۰�����㷨��ʾ(prompt) */
void pGuessNumber(int magic){
	int i;
	int answer, low=1, high=100, mid=(low+high)/2;
	int times=0;
	for (i=0; i<100; i++){
		printf("\n������[%d - %d]֮�������:", low, high);
		scanf("%d", &answer);
		times++;
		
		mid = (low+high)/2;
		if (answer == magic){
			break;
		}
		else if (answer > magic){
			if(magic > mid){
				low = mid + 1;	
				printf("\n̫����!");	
			}
			else if( magic < mid){
				high = mid - 1;
				printf("\n̫����!");
			}
			else{
				low = mid;
				high = mid;
				printf("ħ����[ %d ]!\n", mid);
			}
		}
		else{
			if(magic > mid){
				low = mid + 1;	
				printf("\n̫С��!");
			}
			else if( magic < mid){
				high = mid - 1;
				printf("\n̫С��!");
			}
			else{
				low = mid;
				high = mid;
				printf("ħ����[ %d ]!\n", mid);
				break;
			}
		}
	}	
	printf("�Ѳ�[%2d]��!\n", times);
}