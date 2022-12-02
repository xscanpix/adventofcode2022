#include <stdio.h>

#define CHOICES 3

static const char *FILE_NAME = "input";

int calc_points(const int our_choice, const int their_choice, int points_matrix[CHOICES][CHOICES])
{
    // Choice points: Our choice index + 1
    // Result points: Index into points_matrix
    return (our_choice) + 1 + points_matrix[our_choice][their_choice];
}

int main()
{
    FILE *file = fopen(FILE_NAME, "r");

    int points_matrix[CHOICES][CHOICES] = // [Our choice][Their choice]
        {
            // R|P|S
            {3, 0, 6}, // Rock
            {6, 3, 0}, // Paper
            {0, 6, 3}  // Scissor
        };

    char buf[2] = {0};
    int total_points_part1 = 0;
    int total_points_part2 = 0;

    while (1)
    {
        if (feof(file))
        {
            break;
        }

        // Read newline or first choice.
        fread(&buf[0], sizeof(char), 1, file);

        if (buf[0] == '\n' || feof(file))
        { // New row or EOF
            continue;
        }
        else
        {
            // Seek past 'space'
            fseek(file, 1, SEEK_CUR);

            // Read second choice.
            fread(&buf[1], sizeof(char), 1, file);

            int our_index = buf[1] - 'X';
            int their_index = buf[0] - 'A';

            total_points_part1 += calc_points(our_index, their_index, points_matrix);

            if (buf[1] == 'X')
            {
                // Loosing choice is the previous modular index from their choice.
                our_index = (their_index + (CHOICES - 1)) % CHOICES;
            }
            else if (buf[1] == 'Y')
            {
                // Draw means choose their index.
                our_index = their_index;
            }
            else
            {
                // Winning choice is the next modular index from their choice.
                our_index = (their_index + 1) % CHOICES;
            }

            total_points_part2 += calc_points(our_index, their_index, points_matrix);
        }
    }

    fclose(file);

    printf("Day 2 Answer 1: %d\n", total_points_part1);
    printf("Day 2 Answer 2: %d\n", total_points_part2);
}