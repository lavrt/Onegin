#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>

void bubble_sort(void * array, size_t number_of_strings, size_t element_size, int comparator(void * a, void * b));
void exchanging_strings(void * first_array_, void * second_array_);

#endif // SORTING_H
