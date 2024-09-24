#include "sorting.h"

#include <stdio.h>
#include <assert.h>

#include "debug.h"
#include "processing.h"

void bubble_sort(void * array, const size_t number_of_strings, const size_t element_size,
                int comparator(const void * first_string, const void * second_string))
{
    assert(array != NULL);

    for (size_t j = 0; j < number_of_strings; j++)
    {
        for (size_t i = 0; i < number_of_strings - 1; i++)
        {
            if (comparator((char *)array + i * element_size, (char *)array + (i + 1) * element_size) > 0)
            {
                exchanging_strings((char *)array + i * element_size, (char *)array + (i + 1) * element_size);
            }
        }
    }
}

void exchanging_strings(void * first_string, void * second_string)
{
    assert(first_string != NULL);
    assert(second_string != NULL);
    assert(first_string != second_string);

    position temp = *(position *)first_string;
                    *(position *)first_string = *(position *)second_string;
                                                *(position *)second_string = temp;
}
