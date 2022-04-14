//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

//////////////////////////////////////////////////////////////////////////




// Swaps values at i and j in array arr
void swap(int * arr, int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}


// Quick sort sub-function
int pivot(int * arr1, int * arr2, int i, int j) {
	int p = i;
	int cur = j;
	while(cur > p) {
		if(arr1[p] < arr1[p+1]) {
			swap(arr1, p, p+1);
			swap(arr2, p, p+1);
			p++;
		} else {
			swap(arr1, p+1, cur);
			swap(arr2, p+1, cur);
			cur--;
		}
	}
	return p;
}


// Decreasing quick sort function
void quick_sort(int * arr1, int * arr2, int size) {
	void sort(int i, int j) {
		if(i < j) {
			int p = pivot(arr1, arr2, i, j);
			sort(i, p-1);
			sort(p+1, j);
		}
	}
	return sort(0, size-1);
}




/*
void print_array(int * array, int length) {
	for(int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}


int main() {
	int N;
	int arr1[100], arr2[100];
	printf("N : ");
	scanf("%d", &N);
	for(int i = 0; i < N; i++) {
		arr2[i] = i;
	}
	printf(">>");
	for(int i = 0; i < N; i++) {
		scanf("%d", &arr1[i]);
	}
	quick_sort(arr1, arr2, N);
	print_array(arr1, N);
	print_array(arr2, N);
	return 0;
}
*/




//////////////////////////////////////////////////////////////////////////