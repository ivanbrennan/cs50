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

int maxValue(int values[], int n);
void zeroOut(unsigned int positions[], int positions_len);
void buildHistogram(int values[], int n, unsigned int positions[]);
void sortyByPosition(int values[], int n, unsigned int positions[], int positions_len);

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
