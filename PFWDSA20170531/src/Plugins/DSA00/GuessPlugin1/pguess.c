
/* 给10次机会猜测magic 折半查找算法提示(prompt) */
void pGuessNumber(int magic){
	int i;
	int answer, low=1, high=100, mid=(low+high)/2;
	int times=0;
	for (i=0; i<100; i++){
		printf("\n请输入[%d - %d]之间的整数:", low, high);
		scanf("%d", &answer);
		times++;
		
		mid = (low+high)/2;
		if (answer == magic){
			break;
		}
		else if (answer > magic){
			if(magic > mid){
				low = mid + 1;	
				printf("\n太大了!");	
			}
			else if( magic < mid){
				high = mid - 1;
				printf("\n太大了!");
			}
			else{
				low = mid;
				high = mid;
				printf("魔数是[ %d ]!\n", mid);
			}
		}
		else{
			if(magic > mid){
				low = mid + 1;	
				printf("\n太小了!");
			}
			else if( magic < mid){
				high = mid - 1;
				printf("\n太小了!");
			}
			else{
				low = mid;
				high = mid;
				printf("魔数是[ %d ]!\n", mid);
				break;
			}
		}
	}	
	printf("已猜[%2d]次!\n", times);
}