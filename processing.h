#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>

struct position
{
    char * start;
    char * end;
};

size_t file_size(FILE * file_name);
size_t file_to_text(position ** strings, char * buffer, const size_t size);
void text_to_file(const position * strings, FILE * file_name, const size_t number_of_strings);

#endif // PROCESSING_H
