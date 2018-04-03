#include "stdio.h"
#include <stdlib.h>
#define INT_MAX 2147483647

typedef struct edge{
	int src, dest, wgt;
}edge;

int alreadyPresent(edge* edges, int x, int y, int n){
	// printf("%d\n", e);
	for(size_t i = 0 ; i < n ; i++){
		if((x - 1) == edges[i].src && (y - 1) == edges[i].dest)
			return 1;
	}
	return 0;
}

int main(int argc, char const *argv[]) {
	int e, v, src;
	printf("Enter number of vertices :: ");
	scanf("%d", &v);
	while(v <= 0){
		printf("Incorrect data\nEnter number of vertices :: ");
		scanf("%d", &v);
	}
	printf("Enter number of edges :: ");
	scanf("%d", &e);
	while(e >  v*(v-1) || e < 0){
		printf("Incorrect data\nEnter number of edges :: ");
		scanf("%d", &e);
	}

	edge *edges=(edge *)malloc(sizeof(edge[e]));
	printf("Enter edges :: \n");
	for (size_t i = 0; i < e; i++) {
		int x, y;
		do{
			scanf("%d %d %d", &x, &y, &edges[i].wgt);
			if(x == y){
				printf("Self loop\n");
			}
			else if(!((x > 0 && x <= v) && (y > 0 && y <= v))){
				printf("Vertex out of range\n");
			}
			else if (alreadyPresent(edges, x, y, i)){
				printf("Edge already present\n");
			}
			else{
				break;
			}
			printf("Enter again\n\n");
		}while(1);
		edges[i].src = x - 1;
		edges[i].dest = y - 1;
	}

	while(1){
		printf("Enter source :: ");
		scanf("%d", &src);
		if(src <= v && src > 0)
			break;
		printf("Incorrect data\n");
	}

	int *dist=(int *)malloc(v*sizeof(int));
	for (size_t i = 0; i < v; i++) {
		dist[i] = INT_MAX;
	}
	dist[--src] = 0;
	int found;
	size_t i;
	for (i = 1; i < v ; i++) {
		found = 0;
		for (size_t j = 0; j < e; j++) {
			if(dist[edges[j].src] != INT_MAX && dist[edges[j].dest] > dist[edges[j].src] + edges[j].wgt){
				dist[edges[j].dest] = dist[edges[j].src] + edges[j].wgt;
				found = 1;
			}
		}
		if(!found)
		break;
	}
	if(found) {
		i--;
		for (size_t i = 0; i < e; i++) {
			if(dist[edges[i].src] != INT_MAX && dist[edges[i].dest] > dist[edges[i].src] + edges[i].wgt){
				printf("Graph contains negative weight cycles\n");
				return 0;
			}
		}
	}

	printf("\nNumber of iterations :: %zu\n", i);
	printf("DISTANCE FROM SOURCE TO VERTICES\n");
	printf("Vertex\tDistance\n");
	for (i = 0; i < v; i++) {
		if(dist[i] == INT_MAX)
			printf("%zu\tNo Path\n", i + 1);
		else if(i != src)
			printf("%zu\t%d\n", i + 1, dist[i]);
	}
	printf("\n");
	free(dist);
	free(edges);
	return 0;
}


/*


5 7
1 3 20
1 2 20
1 5 30
2 5 40
2 4 10
2 3 10
4 3 12


*/