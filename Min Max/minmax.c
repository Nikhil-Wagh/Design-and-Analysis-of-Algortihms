#include "stdio.h"
#include "stdlib.h"
typedef struct element{
	int min, max;
}element;
int minimum(int x, int y){
	if(x < y)
		return x;
	return y;
}
int maximum(int x, int y){
	if(x > y)
		return x;
	return y;
}
element MinMax(int x[], int low, int high){
	element temp;
	if(high - low <= 1){
		if(x[low] < x[high]){
			temp.min = x[low];
			temp.max = x[high];
		}
		else{
			temp.min = x[high];
			temp.max = x[low];
		}
		return temp;
	}
	element left, right;
	int mid = (low + high)/2;
	left = MinMax(x, low, mid);
	right = MinMax(x, mid + 1, high);
	temp.min = minimum(left.min, right.min);
	temp.max = maximum(left.max, right.max);
	return temp;
}
int main(int argc, char const *argv[])
{
	int n, *x;
	printf("Enter the size of the arrar :: ");
	scanf("%d", &n);
	x = (int *)malloc(n*sizeof(int));
	printf("Enter the elements\n");
	for(int i = 0 ; i < n ; i++)
		scanf("%d", &x[i]);
	element temp = MinMax(x, 0, n - 1);
	printf("Min :: %d\nMax :: %d\n", temp.min, temp.max);
	free(x);
	return 0;
}