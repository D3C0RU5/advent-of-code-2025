#include <stdio.h>
#include <stdlib.h>

#define INPUT_LIMIT 8
#define MOD 100
#define START_POSITION 50

int extractSteps(char *word)
{
    char number_as_string[INPUT_LIMIT] = {0};
    int i = 0;

    word++;

    while (*word != '\n' && *word != '\0' && i < INPUT_LIMIT - 1)
        number_as_string[i++] = *word++;

    return (int)strtol(number_as_string, NULL, 10);
}

int main()
{
    FILE *fp = fopen("./input.txt", "r");
    if (!fp)
    {
        perror("Error opening file.");
        return 1;
    }

    int position = START_POSITION;

    char line[INPUT_LIMIT];
    int zero_counter = 0;
    while (fgets(line, INPUT_LIMIT, fp))
    {
        int next_position;
        int steps = extractSteps(line) % MOD;
        char direction = line[0];

        if (direction == 'R')
        {
            next_position = (position + steps) % MOD;
            printf("position[R]: %d + %d => ", position, steps);
            position = next_position;
            printf("%d.\n", position);
        }
        else if (direction == 'L')
        {
            next_position = (position - steps + MOD) % MOD;
            printf("position[L]: %d - %d => ", position, steps);
            position = next_position;
            printf("%d.\n", position);
        }
        else
        {
            fprintf(stderr, "Error reading. Char: '%c' - ", line[0]);
            return 1;
        }
        if (position == 0)
            zero_counter++;
    }
    printf("🔑 ANSWER -> %d\n", zero_counter);

    fclose(fp);
    return 0;
}