#include <stdio.h>

static const char *FILE_NAME = "input";

int main()
{
    FILE *file = fopen(FILE_NAME, "r");

    int points_matrix[3][3] = // [Your choice][Their choice]
        {
            {3, 0, 6}, // Rock
            {6, 3, 0}, // Paper
            {0, 6, 3}  // Scissor
        };

    char buf[2] = {0};
    int total_points = 0;

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

            // Choice points: Second choice ASCII-value ('X', 'Y' or 'Z') - 'X' + 1
            // Result points: Index into points_matrix
            total_points += (buf[1] - 'X') + 1 + points_matrix[buf[1] - 'X'][buf[0] - 'A'];
        }
    }

    fclose(file);

    printf("Day 2 Answer 1: %d\n", total_points);
}