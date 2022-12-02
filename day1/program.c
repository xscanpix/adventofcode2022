#include <stdio.h>

#define NUM_MAXES 3
static const char *FILE_NAME = "input";

void update_max(const int sum, int *const current_max_index, int *const maxes)
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
	int current_max_index = 0;	// Index of current max.

	while (1)
	{
		fread(&c, sizeof(char), 1, file);

		if (c == '\n' || feof(file))
		{
			if (sum > 0)
			{
				update_max(sum, &current_max_index, maxes);
				sum = 0;
			}

			if (feof(file))
			{
				break;
			}
		}
		else if (c >= '0' && c <= '9')
		{
			while (c != '\n' && !feof(file))
			{
				number *= 10;
				number += (c - '0');
				fread(&c, sizeof(char), 1, file);
			}

			sum += number;
			number = 0;
		}
		else
		{
			break;
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
