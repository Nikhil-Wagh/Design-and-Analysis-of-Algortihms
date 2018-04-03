#include "stdio.h"
#include "stdlib.h"
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

typedef struct node{
	int cost, cityno, levelno, nodeno;
	int *RCM;
	struct node *parent;
}node;

typedef struct list{
	node *data;
	struct list *next;
}list;


void copyRCM(int *a, int *b, int n){
	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){
			*(b + i*n + j) = *(a + i*n + j);
		}
	}
}

void printRCM(int *a, int n){
	printf("RCM\n");
	for(int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < n ; j++){
			if(*(a + i*n + j) == INT_MAX){
				printf("~ ");
			}
			else{
				printf("%d ", *(a + i*n + j));
			}	
		}
		printf("\n");
	}
}
int minimum(int a, int b){
	if(a < b)
		return a;
	return b;
}
int reduceCost(int *a, int n){
	int cost = 0;
	for(int i = 0 ; i < n ; i++){
		int min = INT_MAX;
		for(int j = 0 ; j < n ; j++){
			min = minimum(min, *(a + i*n + j));
		}
		if(min != INT_MAX && min != 0){
			cost += min;
			for(int k = 0 ; k < n ; k++)
				*(a + i*n + k) -= min; 
		}
	}

	for(int i = 0 ; i < n ; i++){
		int min = INT_MAX;
		for (int j = 0 ; j < n ; j++){
			min = minimum(min, *(a + i + j*n));
		}
		if(min != INT_MAX && min != 0){
			cost += min;
			for(int k = 0 ; k < n ; k++){
				*(a + i + k*n) -= min;
			}
		}
	}
	return cost;
}

void enque(list *l, node *d){
	if(l == NULL){
		l -> next = NULL;
		l -> data = d;
		return;
	}
	//node *temp_node = (node *)malloc(sizeof(node));
	list *temp_list = l;
	temp_node = l -> data;
	while(temp_list -> next != NULL && temp_list -> next -> data -> cost < d -> cost){
		temp_list = temp_list -> next;
		// temp_node = temp_list -> data;
	}
	list *temp = temp_list -> next;
	list 
	temp_list -> next = 


}

void tsp(node *root, int * adj, int n_cities){

}

int main(int argc, char const *argv[])
{
	int n_cities;
	printf("Enter number of cities :: ");
	scanf("%d", &n_cities);
	int * adj = (int *)malloc(n_cities*n_cities*sizeof(int));

	printf("Enter the adjacency matrix\n");
	for(int i = 0 ; i < n_cities ; i++){
		for(int j = 0 ; j < n_cities ; j++){
			scanf("%d", (adj + i*n_cities + j));
			if(*(adj + i*n_cities + j) == -1)
				*(adj + i*n_cities + j) = INT_MAX;		
		}
	}

	node *root = (node *)malloc(sizeof(node *));
	root -> RCM = (int *)malloc(sizeof(n_cities * n_cities * sizeof(int)));
	root -> cityno = 0;
	root -> levelno = 1;
	root -> parent = NULL;
	root -> nodeno = 1;

	copyRCM(adj, root -> RCM, n_cities);

	printf("For root node (%d)\n", root -> nodeno);
	printf("City Number :: %d\n", root -> cityno + 1);
	printRCM(root -> RCM, n_cities);

	root -> cost = reduceCost(root -> RCM, n_cities);
	printf("Reduced cost of city %d is (%d)\n", root -> cityno + 1, root -> cost);

	tsp(root, adj, n_cities);
	return 0;
}