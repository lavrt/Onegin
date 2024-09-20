#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>

struct position
{
    char * start_of_string;
    char * end_of_string;
};

void text_to_file(struct position * strings_position, FILE * file_name, size_t number_of_strings);
size_t file_size(FILE * file_name);

#endif // PROCESSING_H
