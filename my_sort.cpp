#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

// TODO вынести $ в debug.h, FREE и FCLOSE в helpful.h
#define $ fprintf(stderr, "%s:%d in function: %s\n", __FILE__, __LINE__, __func__);
#define FREE(ptr_) \
    do { free(ptr_); ptr_ = NULL; } while (0)

void bubble_sort(void * array, size_t number_of_strings, size_t element_size, int comparator(void * a, void * b));
int compare_strings_direct(void * first_string_, void * second_string_);
int compare_strings_from_end(void * first_string_, void * second_string_);
void exchanging_strings(char ** array, int first_array, int second_array);
void text_to_file(char ** strings_start, FILE * file_name, size_t number_of_strings);
size_t file_size(FILE * file_name);

int main (void)
{
    FILE * text_input = fopen("onegin.txt", "r");
    if (text_input == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return -1;
    }

    FILE * text_output_sorted_direct = fopen("onegin_sorted_direct.txt", "w");
    if (text_output_sorted_direct == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return -1;
    }

    FILE * text_output_sorted_from_end = fopen("onegin_sorted_reverse.txt", "w");
    if (text_output_sorted_from_end == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return -1;
    }

    size_t size = file_size(text_input);

    char * buffer = (char *)calloc(size + 1, sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    char ** strings_start = (char **)calloc(1, sizeof(char *)); // TODO сделать структуру которая хранит начало и конец строки
    if (strings_start == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    char ** strings_end = (char **)calloc(1, sizeof(char *));
    if (strings_end == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return -1;
    }

    *strings_start = buffer;

    fread(buffer, sizeof(char), size + 1, text_input);

    size_t number_of_strings = 0;
    //TODO отдельная функция
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            number_of_strings++;
            strings_start = (char **)realloc(strings_start, sizeof(char *) * (number_of_strings + 1));
            strings_end = (char **)realloc(strings_end, sizeof(char *) * (number_of_strings + 1));
            strings_start[number_of_strings] = buffer + i + 1;
            strings_end[number_of_strings] = buffer + i;
            buffer[i] = '\0';
        }
    }

    bubble_sort(strings_start, number_of_strings, sizeof(char *), compare_strings_direct);
    text_to_file(strings_start, text_output_sorted_direct, number_of_strings);

    bubble_sort(strings_start, number_of_strings, sizeof(char *), compare_strings_from_end);
    text_to_file(strings_start, text_output_sorted_from_end, number_of_strings);

    fclose(text_input); //TODO макрос
    fclose(text_output_sorted_direct);
    fclose(text_output_sorted_from_end);

    FREE(buffer);
    FREE(strings_start);
    FREE(strings_end);

    return 0;
}

void bubble_sort(void * array, size_t number_of_strings, size_t element_size, int comparator(void * a, void * b))
{//TODO add asserts
    for (int j = 0; j < number_of_strings; j++)
    {
        for (int i = 0; i < number_of_strings - 1; i++)
        {
            if (comparator(array + i * element_size, array + (i + 1) * element_size) > 0)
            {
                exchanging_strings((char **)array, i, i + 1);
            }
        }
    }
}

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

void exchanging_strings(char ** array, int first_array, int second_array)
{   // TODO pass pointers to strings itself
    char * temp = array[first_array];
                  array[first_array] = array[second_array];
                                       array[second_array] = temp;
}

void text_to_file(char ** strings_start, FILE * file_name, size_t number_of_strings)
{
    assert(strings_start != NULL);
    assert(file_name != NULL);

    for (int i = 0; i < number_of_strings; i++)
    {
        fputs(strings_start[i], file_name);
        fputc('\n', file_name);
    }
}

size_t file_size(FILE * file_name)
{
    assert(file_name != NULL);

    size_t size = 0;
    fseek(file_name, 0, SEEK_END);
    size = ftell(file_name);
    fseek(file_name, 0, SEEK_SET);
    return size;
}
