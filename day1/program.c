#include <stdio.h>

#define NUM_MAXES 3

static const char *FILE_NAME = "input";

void update_max(int sum, int *current_max_index, int maxes[])
{
	if (sum > maxes[*current_max_index])
	{ // Sum is greater than current max.
		// Next modular index is current max.
		*current_max_index = (*current_max_index + 1) % NUM_MAXES;
		maxes[*current_max_index] = sum;
	}
}

int main()
{
	FILE *file = fopen(FILE_NAME, "r");

	char c;
	int number = 0, sum = 0;

	int maxes[NUM_MAXES] = {0}; // "Circular" buffer of maxes.
	int current_max_index = 0;		  // Index of current max.

	while (1)
	{
		if (feof(file))
		{
			break;
		}

		c = fgetc(file);

		if (c == '\n' || feof(file))
		{ // New number, end of sum or EOF.
			if (number > 0)
			{ // Previous number was not last number to sum.
				sum += number;
				number = 0;
			}
			else
			{ // Previous number was last number to sum.
				update_max(sum, &current_max_index, maxes);
				sum = 0;
			}

			if (feof(file))
			{ // Handle last sum (if no linebreak at the end).
				update_max(sum, &current_max_index, maxes);
				break;
			}
		}
		else
		{
			// Calculate number in base 10.
			number *= 10;
			number += (c - '0');
		}
	}

	fclose(file);

	int max_sum = 0;

	for (int i = 0; i < NUM_MAXES; ++i)
	{
		max_sum += maxes[i];
	}

	printf("Day 1 Answer 1: %d\n", maxes[current_max_index]);
	printf("Day 1 Answer 2: %d\n", max_sum);
}