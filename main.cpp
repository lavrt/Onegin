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

    fread(buffer, sizeof(char), size + 1, text_input);
    strings[0].start = buffer;
    size_t number_of_strings = file_to_text(&strings, buffer, size);

    bubble_sort(strings, number_of_strings, sizeof(position), compare_strings_direct);
    text_to_file(strings, text_output_sorted_direct, number_of_strings);

    bubble_sort(strings, number_of_strings, sizeof(position), compare_strings_from_end);
    text_to_file(strings, text_output_sorted_from_end, number_of_strings);

    FCLOSE(text_input);
    FCLOSE(text_output_sorted_direct);
    FCLOSE(text_output_sorted_from_end);

    FREE(strings);
    FREE(buffer);

    return 0;
}
