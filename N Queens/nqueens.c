#include "stdio.h"
#include "stdlib.h"
int isValidPosition(int *x, int n){
	for(int j = 0 ; j < n ; j++){
		if((abs(x[j] - x[n]) == abs(j - n)) || (x[j] == x[n]))
			return 0;
	}
	return 1;
}
void printCheckBoard(int *x, int n){
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
}
int recursive_nqueen(int *x, int i, int n, int *n_sol, int max_sol){
	if(i >= n)
		return 0;
	for(int k = 0 ; k < n ; k++){
		x[i] = k;
		if(isValidPosition(x, i)){
			if(i == n - 1){
				if(max_sol > (*n_sol)){
					printf("Solution :: %d\n", *n_sol + 1);
					printCheckBoard(x, n);
					(*n_sol)++;
					return 1;
				}
			}
			recursive_nqueen(x, i + 1, n, n_sol, max_sol);
		}
	}
	return *n_sol;
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
				printf("Enter the number of queens :: ");
				scanf("%d", &n);
				int *x = (int *)malloc(n*sizeof(int)); 
				int max_sol, n_sol;

				max_sol = getMaxSolutions();
				n_sol = iterative_nqueen(x, n, max_sol);
				printf("Number of solutions :: %d\n", n_sol);
				free(x);
				break;
			}
			case 2: {
				printf("Enter the number of queens :: ");
				scanf("%d", &n);
				int *x = (int *)malloc(n*sizeof(int)); 
				int max_sol, n_sol = 0;

				max_sol = getMaxSolutions();
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