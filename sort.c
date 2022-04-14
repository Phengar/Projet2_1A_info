//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

//////////////////////////////////////////////////////////////////////////




// Copies arr1 starting at i1 to arr2 starting at i2 on length length
void copy_array(int * arr1, int * arr2, int i1, int i2, int length) {
	for(int i = 0; i < length; i++) {
		arr2[i2 + i] = arr1[i1 + i];
	}
}


// Decreasing merge sort sub-function
void merge(int * arr1, int * arr2, int size, int i, int j, int * copy1, int * copy2) {
	int mid_size = (size - 1) / 2;
	int cur = i, cur1 = i, cur2 = i+mid_size+1;
	while(cur1 <= i+mid_size || cur2 <= j) {
		if(cur2 > j || (cur1 <= i+mid_size && arr1[cur1] > arr1[cur2])) {
		 	copy1[cur] = arr1[cur1];
		 	copy2[cur] = arr2[cur1];
		 	cur1++;
		} else {
			copy1[cur] = arr1[cur2];
		 	copy2[cur] = arr2[cur2];
		 	cur2++;
		}
		cur++;
	}
	copy_array(copy1, arr1, i, i, size);
	copy_array(copy2, arr2, i, i, size);
}

// Merge sort function
void merge_sort(int * arr1, int * arr2, int length) {
	int * copy1 = (int *) malloc(length * sizeof(int));
	int * copy2 = (int *) malloc(length * sizeof(int));
	if(copy1 == NULL || copy2 == NULL) {
		printf("Cannot allocate enough memory.\n");
		exit(1);
	}
	copy_array(arr1, copy1, 0, 0, length);
	copy_array(arr2, copy2, 0, 0, length);
	void sort(int i, int j) {
		int size = j - i + 1;
		int mid_size = (size - 1) / 2;
		if(size > 1) {
			sort(i, mid_size);
			sort(i+mid_size+1, j);
			merge(arr1, arr2, size, i, j, copy1, copy2);
		}
	}
	return sort(0, length - 1);
}


// Prints an array of length integers
void print_array(int * arr, int length) {
	for(int i = 0; i < length; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}




//////////////////////////////////////////////////////////////////////////