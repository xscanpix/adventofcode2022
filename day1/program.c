#include <stdio.h>

int main()
{
	FILE *file = fopen("input", "r");
	char c;
	int number, sum;
	number = sum = 0;

	int max[3] = {0, 0, 0}; // "Circular" buffer of maxes.
	int max_cur = 0;		// Index of current max.

	while (!feof(file))
	{
		fread(&c, sizeof(char), 1, file);

		if (c == '\n')
		{ // New number or end of sum.
			if (number > 0)
			{ // Previous number was not last number to sum.
				sum += number;
				number = 0;
			}
			else
			{ // Previous number was last number to sum.
				if (sum > max[max_cur])
				{ // Sum is greater than current max.
					// Next index is current max.
					max_cur = (max_cur + 1) % 3;
					max[max_cur] = sum;
				}
				sum = 0;
			}
		}
		else
		{
			// Iteratively calculate number in base 10.
			number *= 10;
			number += (c - '0');
		}
	}
	fclose(file);

	int max_3_sum = 0;

	for (int i = 0; i < 3; ++i)
	{
		max_3_sum += max[i];
	}

	printf("Day 1 Answer 1: %d\n", max[max_cur]);
	printf("Day 1 Answer 2: %d\n", max_3_sum);
}