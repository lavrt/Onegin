#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>

void text_to_file(char ** strings_start, FILE * file_name, size_t number_of_strings);
size_t file_size(FILE * file_name);

#endif // PROCESSING_H
