#include "stdio.h"
#include "stdlib.h"
#define INT_MAX 2147483647

int isValidPosition(int *x, int n){
	for(int j = 0 ; j < n ; j++){
		if((abs(x[j] - x[n]) == abs(j - n)) || (x[j] == x[n]))
			return 0;
	}
	return 1;
}

// int n_iter = 0;

void printCheckBoard(int *x, int n){
	// printf("No :: %d\n", n_iter);
	for(int i = 0 ; i < n ; i++)
		printf(" _");
	printf("\n");
	for(int i = 0 ; i < n ; i++){
		printf("|");
		for(int j = 0 ; j < n ; j++){
			if(x[i] == j)
				printf("Q");
			else
				printf("_");
			printf("|");
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void recursive_nqueen(int *x, int i, int n, int *n_sol, int max_sol){
	// if(*n_sol < max_sol)
	// 	return 0;
	if(i >= n)
		return;
	int f = 0;
	for(int k = 0 ; k < n && (!f); k++){
		if(*n_sol >= max_sol)
			return;
		x[i] = k;
		if(isValidPosition(x, i)){
			if(i == n - 1){
				printCheckBoard(x, n);
				(*n_sol)++;
				return;
			}
			else 
				recursive_nqueen(x, i + 1, n, n_sol, max_sol);
		}
	}
	return;
}

int iterative_nqueen(int *x, int n, int max_sol){
	for(int i = 0 ; i < n ; i++)
		x[i] = -1;
	int r = 0, n_sol = 0;
	while(r != -1){
		x[r]++;
		if(x[r] < n){
			if(isValidPosition(x, r)){
				if(r == n - 1){
					if(max_sol > n_sol){
						printf("Solution :: %d\n", n_sol + 1);
						printCheckBoard(x, n);
						n_sol++;
					}
					else{
						return n_sol;
					}
				}
				else{
					r++;
				}
			}
		}
		else{
			x[r] = -1;
			r--;
		}
	}
	return n_sol;
}

int getMaxSolutions(){
	int x;
	printf("Enter Max number of solutions :: ");
	scanf("%d", &x);
	if(x < 0)
		x = INT_MAX;
	printf("\n");
	return x;
}

int main(int argc, char const *argv[])
{
	int choice, n;
	do{
		printf("\n1. Iterative\n2. Recursive\n3. Exit\n\n");
		printf("Enter your choice :: ");
		scanf("%d", &choice);
		switch(choice){
			case 1: {
				do{
					printf("Enter the number of queens (Should be strictly greater than 3):: ");
					scanf("%d", &n);
				}while(n < 4);
				int *x = (int *)malloc(n*sizeof(int)); 
				int max_sol, n_sol;

				max_sol = getMaxSolutions();
				n_sol = iterative_nqueen(x, n, max_sol);
				printf("Number of solutions :: %d\n", n_sol);
				free(x);
				break;
			}
			case 2: {
				do{
					printf("Enter the number of queens (Should be strictly greater than 3):: ");
					scanf("%d", &n);
				}while(n < 4);
				int *x = (int *)malloc(n*sizeof(int)); 
				int max_sol, n_sol = 0;

				max_sol = getMaxSolutions();
				if(n == 1){
					x[0] = 0;
					printCheckBoard(x, 1);
					break;
				}
				recursive_nqueen(x, 0, n, &n_sol, max_sol);
				printf("Number of solutions :: %d\n", n_sol);
				free(x);
				break;
			}
			case 3:{
				printf("Good Bye!!\n");
				choice = -1;
				break;
			}
			default: 
				printf("Invalid Choice\n");
		}
	}while(choice != -1);
	return 0;
}
