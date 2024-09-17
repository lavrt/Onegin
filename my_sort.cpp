#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define $ fprintf(stderr, "%s:%d in function: %s\n", __FILE__, __LINE__, __func__);
#define FILE_ERROR(file_name_) \
    do { fprintf(stderr, "The file \"%s\" could not be opened.\n", file_name_); return -1; } while (0)
#define FREE(ptr_) \
    do { free(ptr_); ptr_ = NULL; } while (0)

void bubble_sort(void * array, int number_of_strings, int comparator(void * a, void * b), size_t element_size);
int compare_strings_direct(void * first_string_, void * second_string_);
int compare_strings_reverse(void * first_string_, void * second_string_);
void exchanging_strings(char ** array, int first_array, int second_array);
void text_to_file(char ** strings, FILE * file_name, int number_of_strings);

int main (void)
{
    struct stat st;
    stat("onegin.txt", &st);
    size_t size = st.st_size;

    FILE * text_input = fopen("onegin.txt", "r");
    if (text_input == NULL) { FILE_ERROR("onegin.txt"); }

    FILE * text_output_sorted_direct = fopen("onegin_sorted_direct.txt", "w");
    if (text_output_sorted_direct == NULL) { FILE_ERROR("onegin_sorted_direct.txt"); }

    FILE * text_output_sorted_reverse = fopen("onegin_sorted_reverse.txt", "w");
    if (text_output_sorted_reverse == NULL) { FILE_ERROR("onegin_sorted_reverse.txt"); }

    char * buffer = (char *)calloc(size + 1, sizeof(char));
    char ** strings = (char **)calloc(1, sizeof(char *));

    *strings = buffer;

    fread(buffer, sizeof(char), size + 1, text_input);

    int number_of_strings = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            number_of_strings++;
            strings = (char **)realloc(strings, sizeof(char *) * (number_of_strings + 1));
            strings[number_of_strings] = buffer + i + 1;
            buffer[i] = '\0';
        }
    }

    bubble_sort(strings, number_of_strings, compare_strings_direct, sizeof(char *));
    text_to_file(strings, text_output_sorted_direct, number_of_strings);

    bubble_sort(strings, number_of_strings, compare_strings_reverse, sizeof(char *));
    text_to_file(strings, text_output_sorted_reverse, number_of_strings);

    fclose(text_input);
    fclose(text_output_sorted_direct);
    fclose(text_output_sorted_reverse);

    FREE(buffer);
    FREE(strings);

    return 0;
}

void bubble_sort(void * array, int number_of_strings, int comparator(void * a, void * b), size_t element_size)
{
    for (int j = 0; j < number_of_strings; j++)
    {
        for (int i = 0; i < number_of_strings - 1; i++)
        {
            if (comparator(array + i * element_size, array + (i + 1) * element_size))
            {
                exchanging_strings((char **)array, i, i + 1);
            }
        }
    }
}

int compare_strings_direct(void * first_string_, void * second_string_)
{
    char * first_string = *(char **)first_string_;
    char * second_string = *(char **)second_string_;

    int a = 0;
    int b = 0;

    for (; (first_string[a] != '\0') && (second_string[b] != '\0'); a++, b++)
    {
        while (!isalpha(first_string [a])) { a++; }
        while (!isalpha(second_string[b])) { b++; }

        if ((first_string[a] == '\0') || (second_string[b] == '\0')
           || (tolower(first_string[a]) != tolower(second_string[b]))) { break; }
    }
    return (first_string[a] > second_string[b]) ? true : false;
}

int compare_strings_reverse(void * first_string_, void * second_string_)
{
    char * first_string = *(char **)first_string_;
    char * second_string = *(char **)second_string_;

    int a = 0;
    int b = 0;

    for (; (first_string[a] != '\0') && (second_string[b] != '\0'); a++, b++)
    {
        while (!isalpha(first_string [a])) { a++; }
        while (!isalpha(second_string[b])) { b++; }

        if ((first_string[a] == '\0') || (second_string[b] == '\0')
           || (tolower(first_string[a]) != tolower(second_string[b]))) { break; }
    }
    return (first_string[a] < second_string[b]) ? true : false;
}

void exchanging_strings(char ** array, int first_array, int second_array)
{
    char * temp = array[first_array];
                  array[first_array] = array[second_array];
                                       array[second_array] = temp;
}

void text_to_file(char ** strings, FILE * file_name, int number_of_strings)
{
    for (int i = 0; i < number_of_strings; i++)
    {
        fputs(strings[i], file_name);
        fputc('\n', file_name);
    }
}
