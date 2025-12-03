#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    long start;
    long end;
} Tuple;

char *read_line(const char *file_path)
{
    FILE *fp = fopen(file_path, "r");
    if (!fp)
    {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    size_t size = 128;
    size_t len = 0;
    char *buffer = malloc(size);
    if (!buffer)
        return NULL;

    while (fgets(buffer + len, size - len, fp))
    {
        len += strlen(buffer + len);
        if (buffer[len - 1] == '\n')
            break;

        size *= 2;
        char *tmp = realloc(buffer, size);
        if (!tmp)
        {
            free(buffer);
            fclose(fp);
            return NULL;
        }
        buffer = tmp;
    }

    fclose(fp);
    return buffer;
}

Tuple *extract_ranges(char *line, size_t *count)
{
    Tuple *list = NULL;
    *count = 0;

    char *token = strtok(line, ",");
    while (token)
    {
        char *dash = strchr(token, '-');
        if (!dash)
        {
            token = strtok(NULL, ",");
            continue;
        }

        *dash = '\0';
        long start = atol(token);
        long end = atol(dash + 1);

        Tuple *tmp = realloc(list, (*count + 1) * sizeof(Tuple));
        if (!tmp)
        {
            free(list);
            return NULL;
        }
        list = tmp;
        list[*count].start = start;
        list[*count].end = end;
        (*count)++;

        token = strtok(NULL, ",");
    }

    return list;
}

bool is_invalid(long value)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "%ld", value);
    size_t len = strlen(buf);

    if (len < 2)
        return false;

    if (len % 2 != 0)
        return false;

    size_t half = len / 2;
    for (size_t i = 0; i < half; i++)
    {
        if (buf[i] != buf[i + half])
            return false;
    }
    return true;
}

long sum_invalid_ids(Tuple t)
{
    long sum = 0;
    for (long i = t.start; i <= t.end; i++)
    {
        if (is_invalid(i))
            sum += i;
    }
    return sum;
}

int main()
{
    char *line = read_line("./input.txt");

    size_t n;
    Tuple *ranges = extract_ranges(line, &n);
    long total_sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        total_sum += sum_invalid_ids(ranges[i]);
    }

    printf("SUM: %ld", total_sum);

    return 0;
}