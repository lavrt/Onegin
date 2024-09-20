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

    struct position * strings_position = (struct position *)calloc(1, sizeof(position));
    if (strings_position == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    strings_position[0].start_of_string = buffer;

    fread(buffer, sizeof(char), size + 1, text_input);

    size_t number_of_strings = 0;
    //TODO отдельная функция
    for (size_t i = 1; i < size + 1; i++)
    {
        if (buffer[i] == '\n')
        {
            number_of_strings++;
            strings_position = (struct position *)realloc(strings_position, sizeof(position) * (number_of_strings + 1));
            strings_position[number_of_strings].start_of_string = buffer + i + 1;
            strings_position[number_of_strings-1].end_of_string = buffer + i;
            buffer[i] = '\0';
        }
    }

    bubble_sort(strings_position, number_of_strings, sizeof(position), compare_strings_direct);
    text_to_file(strings_position, text_output_sorted_direct, number_of_strings);

    bubble_sort(strings_position, number_of_strings, sizeof(position), compare_strings_from_end);
    text_to_file(strings_position, text_output_sorted_from_end, number_of_strings);

    FCLOSE(text_input);
    FCLOSE(text_output_sorted_direct);
    FCLOSE(text_output_sorted_from_end);

    FREE(buffer);
    FREE(strings_position);

    return 0;
}
