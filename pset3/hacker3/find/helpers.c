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
void setQueuePositions(unsigned int positions[], int positions_len);
void sortValues(int values[], int n, unsigned int positions[]);
void copyFromValues(int values[], int n, int copies[]);
void insertValue(int value, unsigned int positions[], int values[]);

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

	setQueuePositions(positions, positions_len);

	sortValues(values, n, positions);

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

void setQueuePositions(unsigned int positions[], int positions_len)
{
	int position = 0;

	for (int i = 0; i < positions_len; i++)
	{
		int entries = positions[i];
		positions[i] = position;
		position += entries;
	}
}

void sortValues(int values[], int n, unsigned int positions[])
{
	// copy original values to a new array so we can iterate
	// over them while modifying the original array in place
	int copies[n];
	copyFromValues(values, n, copies);

	for (int i = 0; i < n; i++)
	{
		insertValue(copies[i], positions, values);
	}
}

void copyFromValues(int values[], int n, int copies[])
{
	for (int i = 0; i < n; i++)
	{
		copies[i] = values[i];
	}
}

void insertValue(int value, unsigned int positions[], int values[])
{
	int position = positions[value];
	positions[value]++;

	values[position] = value;
}
