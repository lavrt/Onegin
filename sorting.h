#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>

void bubble_sort(void * array, const size_t number_of_strings, const size_t element_size,
                 int comparator(const void * first_string, const void * second_string));
void exchanging_strings(void * first_string, void * second_string);

#endif // SORTING_H
