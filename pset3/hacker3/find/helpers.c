/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <math.h>

#include "helpers.h"

#define RADIX 10

void countingSort(int values[], int n);
int maxValue(int values[], int n);
void zeroOut(unsigned int positions[], int positions_len);
void buildHistogram(int values[], int n, unsigned int positions[]);
void sortyByPosition(int values[], int n, unsigned int positions[], int positions_len);
void radixSortLSB(int values[], int n);
void clearAry(int ary[], int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
	if (n > 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (array[i] == value)
			{
				return true;
			}
		}
	}

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
	radixSortLSB(values, n);
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

void radixSortLSB(int values[], int n)
{
	int buckets[RADIX][n];

	for (int i = 0; i < RADIX; i++)
	{
		clearAry(buckets[i], n);
	}

	int maxVal = maxValue(values, n);
	int maxPow = (int) log10(maxVal);

	for (int i = 0; i <= maxPow; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int index = (values[j] / ((int) pow(RADIX, i))) % RADIX;
			int k = 0;
			while (buckets[index][k] != -1)
			{
				k++;
			}
			buckets[index][k] = values[j];
		}

		int v = 0;
		for (int j = 0; j < RADIX; j++)
		{
			for (int k = 0; k < n && buckets[j][k] != -1; k++)
			{
				values[v++] = buckets[j][k];
				buckets[j][k] = -1;
			}
		}
	}
}

void clearAry(int ary[], int n)
{
	for (int i = 0; i < n; i++)
	{
		ary[i] = -1;
	}
}
