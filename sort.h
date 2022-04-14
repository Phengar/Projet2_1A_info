//////////////////////////////////////////////////////////////////////////

/*
	File that contains a merge sort implementation
	--
	DAVAL Quentin - HUBINET Benjamin
	ISMIN 1A - EI21
*/

//////////////////////////////////////////////////////////////////////////

#ifndef SORT_H_
#define SORT_H_

//////////////////////////////////////////////////////////////////////////

// Swaps values at i and j in array arr
void swap(int * arr, int i, int j);

/*
	Sorts array arr1 in a decreasing order 
	using quick sort algorithm, arr2 contains
	the place of each arr1 index after the sort.
*/

// Decreasing quick sort sub-function 
int pivot(int * arr1, int * arr2, int i, int j);

// Decreasing quick sort function
void quick_sort(int * arr1, int * arr2, int length);

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////