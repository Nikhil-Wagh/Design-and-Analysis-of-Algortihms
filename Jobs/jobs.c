#include "stdio.h"
#include "stdlib.h"
typedef struct job{
  int length;
  int id;
}job;
void merg(job j[], int low, int mid, int high){
  int n1, n2;
  n1 = mid - low + 1;
  n2 = high - mid;
  job *L = (job *)malloc(sizeof(job)*n1);
  job *R = (job *)malloc(sizeof(job)*n2);
  for (int i = 0; i < n1; i++) {
    L[i] = j[low + i];
  }
  for (int i = 0; i < n2; i++) {
    R[i] = j[mid + 1 + i];
  }
  int i = 0, r = 0, k = low;
  while(i < n1 && r < n2){
    if (L[i].length < R[r].length) {
      j[k++] = L[i++];
    }
    else{
      j[k++] = R[r++];
    }
  }
  while(i < n1){
    j[k++] = L[i++];
  }
  while(r < n2){
    j[k++] = R[r++];
  }
}

void mergesort(job j[], int low, int high){
  if(low < high){
    int mid = (low + high)/2;
    mergesort(j, low, mid);
    mergesort(j, mid+1, high);
    merg(j, low, mid, high);
  }
}
int main(){
  int n, mrt = 0;
  printf("%s", "Enter n :: ");
  scanf("%d", &n);
  job *j = (job *)malloc(sizeof(job[n]));
  printf("%s%d%s\n", "Enter id and length of ", n, " jobs");
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &j[i].id, &j[i].length);
  }
  mergesort(j, 0, n-1);
  printf("\n%s\n", "S.NO\tJob ID\tLength\tRetTime");
  int *t = (int *)malloc(sizeof(int)*n);
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      t[i] += t[i-1] + j[i].length;
    }
    else{
      t[i] = j[i].length;
    }
    mrt += t[i];
    printf("%d\t%d\t%d\t%d\n", i+1, j[i].id, j[i].length, t[i]);
  }
  printf("%s%f\n", "MRT :: ", (double)mrt/n);
  free(j);
}
