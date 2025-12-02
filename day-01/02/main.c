#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INPUT_LIMIT 32
#define MOD 100
#define START_POSITION 50
#define MINIMUM_VALUE 0
typedef enum
{
    DIR_LEFT = 'L',
    DIR_RIGHT = 'R'
} Direction;

int extractSteps(const char *word)
{
    word++;

    char buffer[INPUT_LIMIT] = {0};
    int i = 0;

    while (*word && *word != '\n' && i < INPUT_LIMIT - 1)
    {
        if (!isdigit(*word))
            break;
        buffer[i++] = *word++;
    }

    char *end;
    long value = strtol(buffer, &end, 10);

    if (end == buffer)
    {
        fprintf(stderr, "Error: invalid number founded.\n");
        return 0;
    }

    return (int)value;
}

int moveCircular(int position, int steps, int direction)
{
    int newPos = (position + direction * steps) % MOD;
    if (newPos < 0)
        newPos += MOD;
    return newPos;
}

int crossesZero(int oldPos, int newPos, int direction)
{
    if (direction == +1)
        return newPos < oldPos;
    else
        return newPos > oldPos;
}

int main()
{
    FILE *fp = fopen("./input.txt", "rb");
    if (!fp)
    {
        perror("Error opening file");
        return 1;
    }

    int position = START_POSITION;
    int zero_counter = 0;

    char line[INPUT_LIMIT];
    while (fgets(line, INPUT_LIMIT, fp))
    {

        if (line[0] != DIR_RIGHT && line[0] != DIR_LEFT)
        {
            fprintf(stderr, "Invalid line: %s\n", line);
            continue;
        }

        int direction = (line[0] == DIR_RIGHT) ? +1 : -1;

        int raw_steps = extractSteps(line);
        int wraps = raw_steps / MOD;
        int steps = raw_steps % MOD;

        if (wraps > 0)
            zero_counter += wraps;

        int newPos = moveCircular(position, steps, direction);

        if (crossesZero(position, newPos, direction))
            zero_counter++;

        position = newPos;
    }

    fclose(fp);

    printf("🔑 ANSWER -> %d\n", zero_counter);
    return 0;
}
