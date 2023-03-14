#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int bruteforce(int* array, int n)
{
	int max_sum=INT_MIN;
	int sum=0;
	int i,j,start=0,end=0;
	
	for(i=0;i<n-1;i++){
		sum=0;
		
		for(j=i;j<n;j++){
			sum+=array[j];
			if(sum>max_sum){
				max_sum=sum;
				start=i;
				end=j;
			}
		}
	}
	printf("\nKazilmasi gereken kesintisiz blok butunu %d - %d\n",start,end);
	return max_sum;
}

int max(int x, int y) {
	if(x>y){
		return x;
	}
	else{
		return y;
	}
}

int divideandconquer(int* array, int start, int end, int x)
{
	int i;
	if (start==end){
		return array[start];
 	}

	int mid=(start+end)/2;

	int left_max=INT_MIN;
	int sum=0;
	int startindex,endindex;
	for (i=mid;i>=start;i--)
	{
		sum+=array[i];
		if (sum>left_max){
			left_max=sum;
			startindex=i;
			}
	}

	int right_max=INT_MIN;
	sum=0;
	for (i=mid+1;i<=end;i++)
	{
		sum+=array[i];
		if (sum>right_max){
			right_max=sum;
			endindex=i;
		}
	}
	int max_left_right = max(divideandconquer(array, start, mid, x),
		divideandconquer(array, mid + 1, end, x));
	int max_sum = max(max_left_right, left_max + right_max);
	
	if(end-start == x-1){
		printf("\nKazilmasi gereken kesintisiz blok butunu %d - %d\n",startindex,endindex);
	}
	
	return max_sum;
}


int main(void)
{
	int n, k;
	int* arr;
	
	printf("Blok sayisi: ");
	scanf("%d", &n);
	
	arr = (int*)malloc(n*sizeof(int));
	
	printf("\n%d tam sayi giriniz.\n\n", n);

	for (k=0; k<n; k++)
	{
		scanf("%d", &arr[k]);
	}
	printf("Brute Force yontemi ile cozmek icin 1'e, Divide and Conquer yontemiyle cozmek icin 2'ye basiniz: ");
	int selection;
	do{
	scanf("%d",&selection);
	}while(selection!=1 && selection!=2);
	
	switch(selection){
		case 1:
			printf("En yuksek kazanc: %d", bruteforce(arr,n));
			break;
		case 2:
			printf("En yuksek kazanc: %d", divideandconquer(arr,0, n-1,n));
			break;
	}
	return 0;
}
