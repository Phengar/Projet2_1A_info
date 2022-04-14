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

// Copies arr1 starting at i1 to arr2 starting at i2 on length length
void copy_array(int * arr1, int * arr2, int i1, int i2, int length);

/*
	Sorts array arr1 in a decreasing order 
	using merge sort algorithm, arr2 contains
	the place of each arr1 index after the sort.
*/

// Decreasing merge sort sub-function 
void merge(int * arr1, int * arr2, int size, int i, int j, int * copy1, int * copy2);

// Decreasing merge sort function
void merge_sort(int * arr1, int * arr2, int length);

// Prints an array of integers of length length
void print_array(int * arr, int length);

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////