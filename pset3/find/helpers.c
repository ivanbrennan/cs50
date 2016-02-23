/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

bool iterativeSearch(int value, int values[], int n);
bool recursiveSearch(int value, int values[], int n);

void bubbleSort(int values[], int n);
void selectionSort(int values[], int n);
void insertionSort(int values[], int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
	return iterativeSearch(value, values, n);
}

bool iterativeSearch(int value, int values[], int n)
{
	int iMin = 0;
	int iMax = n-1;
	int iMid = (iMin + iMax) / 2;

	while (iMin < iMax)
	{
		if (value == values[iMid]) {
			break;
		} else if (value < values[iMid]) {
			iMax = iMid - 1;
			iMid = (iMin + iMax) / 2;
		} else {
			iMin = iMid + 1;
			iMid = (iMin + iMax) / 2;
		}
	}

	return (value == values[iMid]);
}

bool recursiveSearch(int value, int values[], int n)
{
	int iMin = 0;
	int iMax = n-1;
	int iMid = (iMin + iMax) / 2;

	if (iMax < iMin) {
		return false;
	} else if (value == values[iMid]) {
		return true;
	} else if (value < values[iMid]) {
		return recursiveSearch(value, values, n/2);
	} else {
		return recursiveSearch(value, &values[n/2], n/2);
	}
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
	insertionSort(values, n);

    return;
}

void bubbleSort(int values[], int n)
{
	for (int i = n-1; i > 0; i--) {
		int swaps = 0;

		for (int j = 0; j < i; j++) {
			if (values[j] > values[j+1]) {
				int temp    = values[j+1];
				values[j+1] = values[j];
				values[j]   = temp;
				swaps++;
			}
		}

		if (!swaps) {
			break;
		}
	}
}

void selectionSort(int values[], int n)
{
	for (int i = 0; i < n-1; i++) {
		int iMin = i;

		for (int j = i+1; j < n; j++) {
			if (values[j] < values[iMin]) {
				iMin = j;
			}
		}

		int temp = values[i];
		values[i] = values[iMin];
		values[iMin] = temp;
	}
}

void insertionSort(int values[], int n)
{
	for (int i = 0; i < n; i++) {
		int j = i;
		while (j > 0 && values[j-1] > values[j]) {
			int temp = values[j-1];
			values[j-1] = values[j];
			values[j] = temp;
			j--;
		}
	}
}
