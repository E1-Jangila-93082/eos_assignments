#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct array{
	int *arr;
	int size;
}arr_t;

void swap(int *arr1, int *arr2){
	int temp = *arr1;
	*arr1 = *arr2;
	*arr2 = temp;
}

void *bsort(void *param){
	arr_t *ptr = (arr_t *)param;
	int *p = ptr->arr; 
	int n = ptr->size;
	int i,j;
	for(i=0; i<n-1; i++){
		for(j=0; j<n-i-1; j++){
			if(p[j]>p[j+1])
			swap(&p[j],&p[j+1]);
		}
	}
	return NULL;
}

int main(){

	pthread_t t;
	arr_t st;
	printf("Enter the no. of integers :");
	scanf("%d",&st.size);

	st.arr = (int *)malloc(st.size*sizeof(int));

	printf("Enter %d integers :",st.size);
	for(int a=0; a<st.size; a++)
		scanf("%d",&st.arr[a]);	
	printf("Before sorting :");
	for(int b=0; b<st.size; b++){
		printf(" %d",st.arr[b]);
	}	
	int ret = pthread_create(&t,NULL,bsort,&st);
	if(ret!=0){
		perror("Thread creation failed\n");
		exit(-1);
	}
	pthread_join(t,NULL);
	printf("\nAfter sorting :");
	for(int c=0; c<st.size; c++){
		printf(" %d",st.arr[c]);
		fflush(stdout);
		usleep(400000);		
	}	
	printf("\n");
	free(st.arr);
return 0;}









