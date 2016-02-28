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
	unsigned int copies[n];
	for (int i = 0; i < n; i++)
	{
		copies[i] = values[i];
	}

	unsigned int counts[LIMIT] = { 0 };
	for (int i = 0; i < n; i++)
	{
		counts[copies[i]] += 1;
	}

	int smallers = 0;
	for (int i = 0; i < LIMIT; i++)
	{
		int count = counts[i];
		counts[i] = smallers;
		smallers += count;
	}

	for (int i = 0; i < n; i++)
	{
		int value = copies[i];
		int index = counts[value];
		counts[value]++;

		values[index] = value;
	}

    return;
}
