#include "comparators.h"

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "processing.h"
#include "debug.h"

int compare_strings_direct(void * first_string_, void * second_string_)
{
    assert(first_string_ != NULL);
    assert(second_string_ != NULL);

    fprintf(stderr, "first_string.start_of_string %p\n", *(struct position *)first_string_);
    fprintf(stderr, "second_string.end_of_string %p\n", *(struct position *)second_string_);

    struct position first_string = *(struct position *)first_string_;
    struct position second_string = *(struct position *)second_string_;

    int index_first_string = 0;
    int index_second_string = 0;

    for (; ((first_string.start_of_string)[index_first_string] != '\0') && ((second_string.start_of_string)[index_second_string] != '\0');
        index_first_string++, index_second_string++)
    {
        while (!isalpha((first_string.start_of_string)[index_first_string])) { index_first_string++; }
        while (!isalpha((second_string.start_of_string)[index_second_string])) { index_second_string++; }

        if (((first_string.start_of_string)[index_first_string] == '\0') || ((second_string.start_of_string)[index_second_string] == '\0')
           || (tolower((first_string.start_of_string)[index_first_string]) != tolower((second_string.start_of_string)[index_second_string]))) { break; }
    }
    return (first_string.start_of_string)[index_first_string] - (second_string.start_of_string)[index_second_string];
}

int compare_strings_from_end(void * first_string_, void * second_string_)
{
    assert(first_string_ != NULL);
    assert(second_string_ != NULL);

    struct position first_string = **(struct position **)first_string_;
    struct position second_string = **(struct position **)second_string_;

    fprintf(stderr, "first_string: [%p][%p]\n", first_string.start_of_string, first_string.end_of_string);
    fprintf(stderr, "second_string: [%p][%p]\n", second_string.start_of_string, second_string.end_of_string);

    int index_first_string = 0;
    int index_second_string = 0;

    for (; (first_string.end_of_string - index_first_string != first_string.start_of_string)
        || (second_string.end_of_string - index_second_string != second_string.start_of_string);
        index_first_string++, index_second_string++)
    {
        while (!isalpha(*(first_string.end_of_string - index_first_string))) { index_first_string++; }
        while (!isalpha(*(second_string.end_of_string - index_second_string))) { index_second_string++; }
        //printf("%c\n", *(second_string.end_of_string));
        if ((*(first_string.end_of_string - index_first_string) == '\0')
           || (*(second_string.end_of_string - index_second_string) == '\0')
           || (tolower(*(first_string.end_of_string - index_first_string))
           != tolower(*(second_string.end_of_string - index_second_string)))) { break; }
    }

    fprintf(stderr, "dif: %d\n\n", *(first_string.end_of_string-index_first_string) - *(second_string.end_of_string-index_second_string));

    return *(first_string.end_of_string - index_first_string) - *(second_string.end_of_string - index_second_string);
}

/* прямая сортировка с преобразованием структур к чарам
int compare_strings_direct(void * first_string_, void * second_string_)
{
    assert(first_string_ != NULL);
    assert(second_string_ != NULL);

    char * first_string = *(char **)first_string_;
    char * second_string = *(char **)second_string_;

    int index_first_string = 0;
    int index_second_string = 0;

    for (; (first_string[index_first_string] != '\0') && (second_string[index_second_string] != '\0');
        index_first_string++, index_second_string++)
    {
        while (!isalpha(first_string[index_first_string])) { index_first_string++; }
        while (!isalpha(second_string[index_second_string])) { index_second_string++; }

        if ((first_string[index_first_string] == '\0') || (second_string[index_second_string] == '\0')
           || (tolower(first_string[index_first_string]) != tolower(second_string[index_second_string]))) { break; }
    }
    return first_string[index_first_string] - second_string[index_second_string];
}
*/
