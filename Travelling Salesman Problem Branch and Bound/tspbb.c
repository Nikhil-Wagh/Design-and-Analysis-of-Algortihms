#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct list_st{
	int city,cost,levelno;
	int *RCM;
	struct list_st *parent;
}list_st;

typedef struct node{
	list_st *info;
	struct node *next;
}node;

void initialise_RCM(int *CRCM,int *PRCM,int ncities){
	int i,j;
	for(i = 0 ; i < ncities ; i++)
		for(j=0 ; j < ncities ; j++)
			*(CRCM+i*ncities+j) = *(PRCM+i*ncities+j);
}

int reduced_cost(int *RCM,int ncities){
	int i,j,cost=0;
	for(i = 0 ; i < ncities ; i++){
		int mini = INT_MAX;
		for(j = 0 ; j < ncities ; j++){
			if(mini > *(RCM+i*ncities+j))
				mini = *(RCM+i*ncities+j);
		}
		if(mini != INT_MAX && mini != 0){
			cost += mini;
			for(j = 0 ; j < ncities ; j++){
				if(*(RCM+i*ncities+j) != INT_MAX)
					*(RCM+i*ncities+j) -= mini;
			}
		}
	}
	for(i = 0 ; i < ncities ; i++){
		int mini = INT_MAX;
		for(j = 0 ; j < ncities ; j++){
			if(mini > *(RCM+i+j*ncities))
				mini = *(RCM+i+j*ncities);
		}
		if(mini != INT_MAX && mini != 0){
			cost += mini;
			for(j = 0 ; j < ncities ; j++){
				if(*(RCM+i+j*ncities) != INT_MAX)
					*(RCM+i+j*ncities) -= mini;
			}
		}
	}
	
	return cost;
}

int not_found(int *path,int c,int v){
	int i;
	for(i = 0 ; i < v-1 ; i++)
		if(*(path+i) == c)
			return 0;
	return 1;
}

void initialise_infi(int *RCM,int p,int c,int ncities){
	int i,j;
	for(i = 0 ; i < ncities ; i++){
		*(RCM+p*ncities+i) = INT_MAX;
		*(RCM+i*ncities+c) = INT_MAX;
	}
	*(RCM+c*ncities) = INT_MAX;
}

node *newnode(list_st *d){
	node *temp = (node *)malloc(sizeof(node));
	temp->info = d;
	temp->next = NULL;
	return temp;
}

node *enqueue(node *l,list_st *d){
	node *start = l;
	node *temp = newnode(d);
	if(l == NULL || l -> info -> cost > d -> cost){
		temp -> next = l;
		l = temp;
	}
	else{
		while(start -> next != NULL && start -> info -> cost < d-> cost){
			start = start -> next;
		}
		temp -> next = start -> next;
		start -> next = temp;
	}
	
	return l;
}

list_st *dequeue(node *l){
	node *temp = l;
	l = l -> next;
	list_st *t = temp -> info;
	free(temp);
	return t;
}

void tsp(list_st *R,int *adjm,int v){
	list_st *E = (list_st *)malloc(sizeof(list_st));
	E = R;
	int upper = INT_MAX,i,j,c;
	list_st *T;
	list_st *ans = NULL;
	int *path = (int *)malloc((v-1)*sizeof(int));
	node *live_list = NULL,*ll = NULL;
	node *dead_list = NULL;
	
	while(1){
		if(E -> cost > upper){
			printf("\nThe node %d gets killed because %d>%d\n",E -> city + 1, E -> cost, upper);
			free(E -> RCM);
			free(E);
		}
		else{
			i = 0;
			T = E;
			while(T != R){
				path[i] = T -> city;
				T = T -> parent;
				i++;
			}
			for(c = 1 ; c < v ; c++){
				int p = E -> city;
				if(*(adjm+p*v+c) != INT_MAX){
					if(E -> levelno < (v - 1) || (E -> levelno == (v - 1) && *(adjm+c*v) != INT_MAX)){
						if(not_found(path,c,v)){
							list_st *child = (list_st *)malloc(sizeof(list_st));
							child->RCM = (int *)malloc(v*v*sizeof(int));
							initialise_RCM(child -> RCM, E -> RCM, v);
							initialise_infi(child -> RCM, p, c, v);
							
							child -> city = c;
							child -> levelno = E -> levelno + 1;
							child -> parent = E;
							
							printf("\nPath array --> ");
							if(p == 0)
								printf("Currently at root\n");
							else{
								for(i = 0; i < v - 1 ; i++){
									if(*(path+i) == 0)
										break;
									else
										printf("%d ",*(path + i) + 1);
								}
								printf("\n");
							}
						
							printf("\nFor node %d\n",child -> city + 1);
							printf("child->city :: %d\n",child -> city + 1);
							printf("child->levelno :: %d\n",child -> levelno);
							
							int t=reduced_cost(child -> RCM, v);
							child -> cost = E -> cost + t + (*(E -> RCM + p*v + c ));
							
							printf("\nRCM\n");
							for(i = 0 ;i < v ; i++){
								for(j = 0 ; j < v ; j++){
									if(*(child -> RCM + i*v + j) == INT_MAX)
										printf("~ ");
									else
										printf("%d ",*(child -> RCM + i*v + j));
								}
								printf("\n");
							}
							printf("\n");
							
							printf("cost(%d)=E->cost+reduced_cost(%d)+parent->RCM[%d][%d]\n", child -> city + 1, child -> city, p, c);
							printf("cost(%d)=%d+%d+%d\n", child -> city + 1, E -> cost, t,*(E -> RCM + p*v + c));
							printf("cost(%d)=%d\n",child -> city + 1 ,child -> cost);
							
							printf("--------------------------------");
							
							if(child -> cost > upper){
								free(child -> RCM);
								free(child);
							}
							else{
								if(child -> levelno == v){
									if(*(adjm + c*v ) != INT_MAX){
										upper = child -> cost;
										if(ans != NULL)
											free(ans);
										ans = child;
									}
									else{
										free(child -> RCM);
										free(child);
									}
								}
								else{
									live_list = enqueue(live_list ,child);
									ll = live_list;
								}
							}
						}
					}
				}
			}
			dead_list = enqueue(dead_list, E);
		}
		if(live_list == NULL)
			break;
		ll = live_list -> next;
		E = dequeue(live_list);
		live_list = ll;
	}
	if(upper != INT_MAX){
		i = 0;
		T = ans;
		while(T != R){
			path[i] = T -> city;
			T = T -> parent;
			i++;
		}
		printf("\nPATH --> 1 -> ");
		for(i = v - 2 ; i >= 0 ; i--)
			printf("%d -> ",*(path + i) + 1);
		printf("1\n");
		printf("the total cost is%d\n", upper);
	
		free(ans -> RCM);
		free(ans);
	}
	else
		printf("\nNo path present!!!\n");

	while(dead_list != NULL){
		ll = dead_list;
		dead_list = dead_list -> next;
		T = ll -> info;
		free(T -> RCM);
		free(T);
		free(ll);
	}
}

int main(){
	int ncities, i, j, ch;
	int s, d, w;
	
	printf("Enter number of cities :: ");
	scanf("%d", &ncities);
	
	int *adjm = (int *)malloc(ncities*ncities*sizeof(int));
	
	for(i = 0 ; i < ncities ; i++)
		for(j = 0 ; j < ncities ; j++)
			*(adjm + i*ncities + j) = INT_MAX;

	i=0;	
	printf("Enter the edges\n");
	do{
		printf("Enter source, dest and weight for edge number %d :: ",i);
		scanf("%d%d%d",&s,&d,&w);
		*(adjm + (s-1)*ncities + (d - 1)) = w;
		i++;
		printf("Continue(1/0) :: ");
		scanf("%d",&ch);
	}while(ch==1);
	
	list_st *root = (list_st *)malloc(sizeof(list_st));
	root -> RCM = (int *)malloc(ncities*ncities*sizeof(int));
	root -> city = 0;
	root -> levelno = 1;
	root -> parent = NULL;
	
	initialise_RCM(root -> RCM, adjm, ncities);
	
	printf("--------------------------------");
	
	printf("\nFor root node %d\n",root -> city + 1);
	printf("root->city :: %d\n",root -> city + 1);
	printf("root->levelno :: %d\n", root -> levelno);
	printf("\nRCM\n");
	for(i = 0 ; i < ncities ; i++){
		for(j = 0 ; j < ncities ; j++){
			if(*(root -> RCM + i*ncities + j) == INT_MAX)
				printf("~ ");
			else
				printf("%d ",*(root -> RCM + i*ncities + j));
		}
		printf("\n");
	}
	printf("\n");
	
	root -> cost = reduced_cost(root -> RCM, ncities);
	printf("root->cost :: %d\n", root -> cost);
	
	printf("--------------------------------");
	
	tsp(root,adjm,ncities);
	
	return 0;
}

/*

4
12
1 2 1
1 3 15
1 4 6
2 1 2
2 3 7
2 4 3
3 1 9
3 2 6
3 4 12
4 1 10 
4 2 4
4 3 8


*/
