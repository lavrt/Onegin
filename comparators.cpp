#include "comparators.h"

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

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

int compare_strings_from_end(void * first_string_, void * second_string_)
{
    assert(first_string_ != NULL);
    assert(second_string_ != NULL);

    char * first_string = *(char **)first_string_;
    char * second_string = *(char **)second_string_;

    int index_first_string = strlen(first_string);
    int index_second_string = strlen(second_string);

    for (; (index_first_string > 0) && (index_second_string > 0); index_first_string--, index_second_string--)
    {
        while (!isalpha(first_string[index_first_string])) { index_first_string--; }
        while (!isalpha(second_string[index_second_string])) { index_second_string--; }

        if ((first_string[index_first_string] == '\0') || (second_string[index_second_string] == '\0')
           || (tolower(first_string[index_first_string]) != tolower(second_string[index_second_string]))) { break; }
    }
    return first_string[index_first_string] - second_string[index_second_string];
}
