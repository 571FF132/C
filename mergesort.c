
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

int threadCount = 6;

struct Parameters {
	int *A;
	int p;
	int r;
};

// function prototypes
void serial_mergesort(int A[], int p, int r);
void merge(int A[], int p, int q, int r);
void insertion_sort(int A[], int p, int r);

//my new function prototype
void *mergesort_thread(void *pv);

const int INSERTION_SORT_CUTOFF = 100; //based on trial and error

/*
 * insertion_sort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void insertion_sort(int A[], int p, int r) 
{
	int j;

	for (j=p+1; j<=r; j++) {
		int key = A[j];
		int i = j-1;
		while ((i > p-1) && (A[i] > key)) {	
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

/*
 *   just for passing the parameters
 */
void *mergesort_thread(void *pv){
	struct Parameters *params = pv;
	serial_mergesort(params->A, params->p, params->r);
	return pv;
}
		
/*
 * serial_mergesort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void serial_mergesort(int A[], int p, int r) 
{
	if (r-p+1 <= INSERTION_SORT_CUTOFF)  {
			insertion_sort(A,p,r);
	} else {
		pthread_t thread1;
		

		int q = (p+r)/2;
		
		if (threadCount>0){
		
		threadCount--;
                struct Parameters params = {A, p, q};

                pthread_create(&thread1, NULL, mergesort_thread, &params);

                serial_mergesort(A, q+1, r);
		
		pthread_join(thread1, NULL);

		merge(A, p, q, r);
                                                              
		}else{

                serial_mergesort(A, p, q);		                             
		serial_mergesort(A, q+1, r);
		
	     	merge(A, p, q, r);
		}
	}
}

/*
 * merge(int A[], int p, int q, int r):
 *
 * description: Merge two sorted sequences A[p..q] and A[q+1..r] 
 *              and place merged output back in array A. Uses extra
 *              space proportional to A[p..r].
 */     
void merge(int A[], int p, int q, int r) 
{
	int *B = (int *) malloc(sizeof(int) * (r-p+1));
		
	int i = p;
	int j = q+1;
	int k = 0;
	int l;
		
	// as long as both lists have unexamined elements
	// this loop keeps executing.
	while ((i <= q) && (j <= r)) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
		
	// now only at most one list has unprocessed elements.
		
	if (i <= q) { 
		// copy remaining elements from the first list
		for (l=i; l<=q; l++) {
			B[k] = A[l];
			k++;
		}
	} else {
		// copy remaining elements from the second list
		for (l=j; l<=r; l++) {
			B[k] = A[l];
			k++;
		}
	}
		
	// copy merged output from array B back to array A
	k=0;
	for (l=p; l<=r; l++) {
		A[l] = B[k];
		k++;
	}

	free(B);
}

