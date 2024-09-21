#include "sorting.h"

#include <stdio.h>
#include <assert.h>

void bubble_sort(void * array, size_t number_of_strings, size_t element_size, int comparator(void * a, void * b))
{
    assert(array != NULL);

    for (size_t j = 0; j < number_of_strings; j++)
    {
        for (size_t i = 0; i < number_of_strings - 1; i++)
        {
            if (comparator(array + i * element_size, array + (i + 1) * element_size) > 0) // TODO cast to char* for pointer arithmetic
            {
                exchanging_strings(array + i * element_size, array + (i + 1) * element_size);
            }
        }
    }
}

void exchanging_strings(void * first_string, void * second_string)
{
    void * temp = first_string;
                  first_string = second_string;
                                        second_string = temp;
}
