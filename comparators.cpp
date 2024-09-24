#include "comparators.h"

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "processing.h"
#include "debug.h"

int compare_strings_direct(const void * first_string_, const void * second_string_)
{
    assert(first_string_ != NULL);
    assert(second_string_ != NULL);
    assert(first_string_ != second_string_);

    const position first_string = *(const position *)first_string_;
    const position second_string = *(const position *)second_string_;

    int index_first_string = 0;
    int index_second_string = 0;

    for (; (first_string.start[index_first_string] != '\0') && (second_string.start[index_second_string] != '\0');
        index_first_string++, index_second_string++)
    {
        while (!isalpha(first_string.start[index_first_string])) { index_first_string++; }
        while (!isalpha(second_string.start[index_second_string])) { index_second_string++; }

        if ((first_string.start[index_first_string] == '\0')
           || (second_string.start[index_second_string] == '\0')
           || (tolower(first_string.start[index_first_string])
           != tolower(second_string.start[index_second_string]))) { break; }
    }

    return first_string.start[index_first_string] - second_string.start[index_second_string];
}

int compare_strings_from_end(const void * first_string_, const void * second_string_)
{
    assert(first_string_ != NULL);
    assert(second_string_ != NULL);
    assert(first_string_ != second_string_);

    const position first_string = *(const position *)first_string_;
    const position second_string = *(const position *)second_string_;

    int index_first_string = 0;
    int index_second_string = 0;

    for (; (first_string.end - index_first_string != first_string.start)
        || (second_string.end - index_second_string != second_string.start);
        index_first_string++, index_second_string++)
    {
        while (!isalpha(*(first_string.end - index_first_string))) { index_first_string++; }
        while (!isalpha(*(second_string.end - index_second_string))) { index_second_string++; }

        if ((*(first_string.end - index_first_string) == '\0')
           || (*(second_string.end - index_second_string) == '\0')
           || (tolower(*(first_string.end - index_first_string))
           != tolower(*(second_string.end - index_second_string)))) { break; }
    }

    return *(first_string.end - index_first_string) - *(second_string.end - index_second_string);
}
