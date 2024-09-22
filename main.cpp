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

    struct position * strings = (struct position *)calloc(2, sizeof(position));
    if (strings == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    struct position ** pointer = (struct position **)calloc(1, sizeof(position *));
    if (pointer == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    fread(buffer, sizeof(char), size + 1, text_input);

    (strings[0]).start_of_string = buffer;
    pointer[0] = strings;

    fprintf(stderr, "\n\nbuffer %p\n", buffer);
    fprintf(stderr, "first_string %p\n\n", (strings[0]).start_of_string);
    fprintf(stderr, "first_string %p\n\n", &((strings[0])));

    size_t number_of_strings = 0;
    //TODO отдельная функция
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            number_of_strings++;
            pointer = (struct position **)realloc(pointer, sizeof(position *) * (number_of_strings + 1));
            pointer[number_of_strings] = &strings[number_of_strings];
            strings = (struct position *)realloc(strings, sizeof(position) * (number_of_strings + 1));
            (strings[number_of_strings]).start_of_string = buffer + i + 1;
            (strings[number_of_strings-1]).end_of_string = buffer + i - 1;

            buffer[i] = '\0';
        }
    }

    bubble_sort(*pointer, number_of_strings, sizeof(position *), compare_strings_direct);
    text_to_file(*pointer, text_output_sorted_direct, number_of_strings);

    bubble_sort(*pointer, number_of_strings, sizeof(position *), compare_strings_from_end);
    text_to_file(*pointer, text_output_sorted_from_end, number_of_strings);

    FCLOSE(text_input);
    FCLOSE(text_output_sorted_direct);
    FCLOSE(text_output_sorted_from_end);
    FREE(pointer);
    FREE(strings);
    FREE(buffer);


    return 0;
}
