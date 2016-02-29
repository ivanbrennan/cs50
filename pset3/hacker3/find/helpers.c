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

#define RADIX 10

bool binarySearch(int value, int array[], int iMin, int iMax);
void countingSort(int values[], int n);
int maxValue(int values[], int n);
void zeroOut(unsigned int positions[], int positions_len);
void buildHistogram(int values[], int n, unsigned int positions[]);
void sortyByPosition(int values[], int n, unsigned int positions[], int positions_len);
void radixSortLSB(int values[], int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
	if (n > 0)
	{
		int iMin = 0;
		int iMax = n - 1;

		return binarySearch(value, array, iMin, iMax);
	}
	else
	{
		return false;
	}
}

bool binarySearch(int value, int array[], int iMin, int iMax)
{
	if (iMin <= iMax)
	{
		int iMid = (iMin + iMax) / 2;

		if (value == array[iMid])
		{
			return true;
		}
		else if (value > array[iMid])
		{
			return binarySearch(value, array, iMid+1, iMax);
		}
		else
		{
			return binarySearch(value, array, iMin, iMid-1);
		}
	}
	else
	{
		return false;
	}
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
	countingSort(values, n);
}

void countingSort(int values[], int n)
{
	int positions_len = maxValue(values, n) + 1;
	unsigned int positions[positions_len];
	zeroOut(positions, positions_len);

	buildHistogram(values, n, positions);

	sortyByPosition(values, n, positions, positions_len);

    return;
}

int maxValue(int values[], int n)
{
	int max = 0;

	for (int i = 0; i < n; i++)
	{
		if (values[i] > max)
		{
			max = values[i];
		}
	}

	return max;
}

void zeroOut(unsigned int positions[], int positions_len)
{
	for (int i = 0; i < positions_len; i++)
	{
		positions[i] = 0;
	}
}

void buildHistogram(int values[], int n, unsigned int positions[])
{
	for (int i = 0; i < n; i++)
	{
		positions[values[i]] += 1;
	}
}

void sortyByPosition(int values[], int n, unsigned int positions[], int positions_len)
{
	int index = 0;

	for (int i = 0; i < positions_len; i++)
	{
		for (int j = 0, entries = positions[i]; j < entries; j++)
		{
			values[index++] = i;
		}
	}
}

// this was an interesting challenge, but is significantly slower than countingSort
void radixSortLSB(int values[], int n)
{
	// build buckets to hold grouped numbers
	int buckets[RADIX][n];
	for (int group = 0; group < RADIX; group++)
	{
		for (int entry = 0; entry < n; entry++)
		{
			buckets[group][entry] = -1;
		}
	}

	// find max unit (place-value)
	int maxVal = maxValue(values, n);
	int maxUnit = 1;
	while (maxUnit * RADIX <= maxVal)
	{
		maxUnit *= RADIX;
	}

	// iterate from least to most significant unit
	for (int unit = 1; unit <= maxUnit; unit *= RADIX)
	{
		// group numbers by digit
		for (int v = 0; v < n; v++)
		{
			int value = values[v];
			int group = (value / unit) % RADIX;
			int entry = 0;
			while (buckets[group][entry] != -1)
			{
				entry++;
			}
			buckets[group][entry] = value;
		}

		// write numbers to original array
		int v = 0;
		for (int group = 0; group < RADIX; group++)
		{
			for (int entry = 0; entry < n && buckets[group][entry] != -1; entry++)
			{
				values[v++] = buckets[group][entry];
				// clear bucket entries as we go
				buckets[group][entry] = -1;
			}
		}
	}
}
