#include "processing.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

size_t file_size(FILE * file_name)
{
    assert(file_name != NULL);

    fseek(file_name, 0, SEEK_END);
    size_t size = (long unsigned)ftell(file_name);
    fseek(file_name, 0, SEEK_SET);

    return size;
}

size_t file_to_text(position ** strings, char * buffer, const size_t size)
{
    assert(strings != NULL);
    assert(buffer != NULL);

    size_t number_of_strings = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            number_of_strings++;
            *strings = (position *)realloc(*strings, sizeof(position) * (number_of_strings + 1));
            (*strings)[number_of_strings].start = buffer + i + 1;
            (*strings)[number_of_strings - 1].end = buffer + i;
        }
    }

    return number_of_strings;
}

void text_to_file(const position * strings, FILE * file_name, const size_t number_of_strings)
{
    assert(file_name != NULL);
    assert(strings != NULL);

    for (size_t i = 0; i < number_of_strings; i++)
    {
        fputs((strings[i]).start, file_name);
        fputc('\n', file_name);
    }
}
