/*
	author: dai liang
	date: 2021.09.13 19:40:12 CST
	top-k
	This question was solved in two ways. Through the test, you can find that 
	the second method takes less time when the k value is small. Otherwise, 
	the opposite
*/
#include<stdio.h>
#include<stdlib.h>
//#include<fcntl.h>
#include<assert.h>
#include<errno.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int * GenerateRandomNum(int n){
	assert(n > 0);
	
	int * res = (int *)malloc(sizeof(int)*n);
	srand(time(NULL));
	
	while(--n >= 0){
		res[n] = rand();
	}
	
	return res;
}

void swap(int* a, int* b){
	int c;
	c = *a;
	*a = *b;
	*b = c;
	return;
}

/*
	little->big
*/
void quickSort(int * arr, int lhs, int rhs){
	int x = lhs;
	int y = rhs;
	int tmp;
	if(lhs < rhs){
		tmp = arr[lhs];
		while(x < y){
			while(x < y && arr[y] > tmp){
				y--;
			}
			if(x < y){
				swap(&arr[x], &arr[y]);
				x++;
			}
			while(x < y && arr[x] < tmp){
				x++;
			}
			if(x < y){
				swap(&arr[x], &arr[y]);
				y--;
			}
		}
		//tmp = arr[x];
		quickSort(arr, lhs, x - 1);
		quickSort(arr, x + 1, rhs);
	}
}

/*
	big -> little
*/
void insertSort(int * arr, int n){
	assert(n >= 0);
	
	int i;
	int j;
	int tmp;
	for(i = 1; i < n; i++){
		tmp = arr[i];
		j = i - 1;
		while(j >= 0 && tmp > arr[j]){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = tmp;
	}
}

void solutionQuick(int * arr, int n, int k){
	int * nums = (int*)malloc(sizeof(int)*n);
	memcpy(nums, arr, sizeof(int)*n);
	
	clock_t begin = clock();
	quickSort(nums, 0, n - 1);
	
	
	printf("quick %d  %f\n", nums[n - k], (double)(clock() - begin)/CLOCKS_PER_SEC);
	
	free(nums);
}

int main(int argc, char ** argv){
	if(argc != 3){
		fprintf(stderr, "usage: exe n k\n");
		return 0;
	}
	
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	
	printf("n = %d, k = %d\n", n, k);
	
	int * arr = GenerateRandomNum(n);
	int * queue = (int *)malloc(sizeof(int) * (k));
	
	#if 0
	int tmp;
	//quickSort(arr, 0, n-1);
	for(tmp = 0; tmp < n; tmp++){
		printf("%d\n", arr[tmp]);
	}
	#endif
	
	printf("------------------\n");
	
	int i = 0;
	int j = 0;
	
	//way1
	solutionQuick(arr, n, k);
	
	//way2
	clock_t begin = clock();
	for(i = 0; i < n; i++){
		if(j < k){
			queue[j] = arr[i];
			//insertSort(queue, j);
			j++;
			//quickSort(queue, 0, j);
		}
		else{
			if(queue[k - 1] > arr[i]){
				continue;
			}
			else{
				queue[k - 1] = arr[i];
				insertSort(queue, k);
			}
		}
	}
	
	printf("the K-th largest value of array is %d  %f\n", queue[k-1], (double)(clock() - begin)/CLOCKS_PER_SEC);
	
	free(arr);
	free(queue);
}
