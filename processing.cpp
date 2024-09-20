#include "processing.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void text_to_file(struct position * strings_position, FILE * file_name, size_t number_of_strings)
{
    assert(file_name != NULL);

    for (size_t i = 0; i < number_of_strings; i++)
    {
        fputs(strings_position[i].start_of_string, file_name);
        fputc('\n', file_name);
    }
}

size_t file_size(FILE * file_name)
{
    assert(file_name != NULL);

    size_t size = 0;
    fseek(file_name, 0, SEEK_END);
    size = ftell(file_name);
    fseek(file_name, 0, SEEK_SET);
    return size;
}
