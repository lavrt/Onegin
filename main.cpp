#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "comparators.h"
#include "processing.h"
#include "sorting.h"
#include "debug.h"
#include "helper.h"

int main(void)
{
    FILE * text_input = fopen("onegin.txt", "r");
    if (text_input == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return -1;
    }

    FILE * text_output_sorted_direct = fopen("onegin_sorted_direct.txt", "w");
    if (text_output_sorted_direct == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return -1;
    }

    FILE * text_output_sorted_from_end = fopen("onegin_sorted_reverse.txt", "w");
    if (text_output_sorted_from_end == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return -1;
    }

    size_t size = file_size(text_input);

    char * buffer = (char *)calloc(size + 1, sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    char ** strings_start = (char **)calloc(1, sizeof(char *)); // TODO сделать структуру которая хранит начало и конец строки
    if (strings_start == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    char ** strings_end = (char **)calloc(1, sizeof(char *));
    if (strings_end == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    *strings_start = buffer;

    fread(buffer, sizeof(char), size + 1, text_input);

    size_t number_of_strings = 0;
    //TODO отдельная функция
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            number_of_strings++;
            strings_start = (char **)realloc(strings_start, sizeof(char *) * (number_of_strings + 1));
            strings_end = (char **)realloc(strings_end, sizeof(char *) * (number_of_strings + 1));
            strings_start[number_of_strings] = buffer + i + 1;
            strings_end[number_of_strings] = buffer + i;
            buffer[i] = '\0';
        }
    }

    bubble_sort(strings_start, number_of_strings, sizeof(char *), compare_strings_direct);
    text_to_file(strings_start, text_output_sorted_direct, number_of_strings);

    bubble_sort(strings_start, number_of_strings, sizeof(char *), compare_strings_from_end);
    text_to_file(strings_start, text_output_sorted_from_end, number_of_strings);

    FCLOSE(text_input);
    FCLOSE(text_output_sorted_direct);
    FCLOSE(text_output_sorted_from_end);

    FREE(buffer);
    FREE(strings_start);
    FREE(strings_end);

    return 0;
}
