#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <cstring>

const int BUFFER_SIZE = 128;

#define $ fprintf(stderr, "%s:%d in function: %s\n", __FILE__, __LINE__, __func__);
#define CLEAR(x) memset(x, '\0' , BUFFER_LENGTH)

int my_strcmp(char first_array[], char second_array[]);
void bubble_sort(char array[][40]);
void exchanging_strings(char first_array[], char second_array[]);
int my_strlen(char first_array[]);
void print_array(char ** pointers_to_strings);
char ** reading_strings(const char * file_name, int number_of_strings);

int main(void)
{
    FILE * file = fopen("onegin.txt", "r");
    char buffer[BUFFER_LENGTH] = {};
    char ** pointers_to_strings = (char **)calloc(1, sizeof(char *));
    char * text = (char *)calloc(BUFFER_LENGTH, sizeof(char));
    int length_of_array = 0;

    for (int number_of_strings = 0; fgets(buffer, BUFFER_LENGTH, file) != NULL; number_of_strings++)
    {
        length_of_array += my_strlen(buffer) + 1;
        if (number_of_strings != 0)
        {
            char * text = (char *)calloc(my_strlen(buffer) + 1, sizeof(char));
        }
        strcpy(text, buffer);
        pointers_to_strings[number_of_strings] = text;
        char ** pointers_to_strings = (char **)realloc(pointers_to_strings, sizeof(char *) * (number_of_strings + 1));
        CLEAR(buffer);
    }

/*    char onegin[14][40]
    {
        {"My uncle used to be so sound,"         },
        {"But after falling gravely ill"         },
        {"Is craving homage, and has found"      },
        {"That could not make a better deal."    },
        {"It is for others a good lesson,"       },
        {"But what a boredom is the session:"    },
        {"To watch a sick man day and night"     },
        {"And do not make a step aside!"         },
        {"What mean deceitfulness it is:"        },
        {"To feign compassion, dose the drugs,"  },
        {"To set and fluff the pillows, thus,"   },
        {"To entertain a half deceased,"         },
        {"To show fake sympathy, then, sigh"     },
        {"And think: Oh gosh, when will you die!"},
    };

    bubble_sort(onegin);*/
    print_array(pointers_to_strings);

    fclose(file);
    free(pointers_to_strings);
    pointers_to_strings = NULL;
    text = NULL;
    free(text);
    return 0;
}

int my_strcmp(char first_array[], char second_array[])
{
    int a = 0;
    int b = 0;
    for (; first_array[a] != '\0' && second_array[b] != '\0'; a++, b++)
    {
        while (!isalpha(first_array [a])) { a++; }
        while (!isalpha(second_array[b])) { b++; }

        if ((first_array[a] == '\0') || (second_array[b] == '\0')
           || (tolower(first_array[a]) != tolower(second_array[b]))) { break; }
    }
    return first_array[a] - second_array[b];
}

void bubble_sort(char array[][40])
{
    for (int j = 0; j < 14; j++)
    {
        for (int i = 0; i < 13; i++)
        {
            if (my_strcmp(array[i], array[i+1]) > 0)
            {
                exchanging_strings(array[i], array[i+1]);
            }
        }
    }
}

void exchanging_strings(char first_array[], char second_array[])
{
    int max_length = (my_strlen(first_array) > my_strlen(second_array))
                    ? my_strlen(first_array) : my_strlen(second_array);

    for (int i = 0; i < 1 + max_length; i++)
    {
        int temp = 0;
        temp = first_array[i];
               first_array[i] = second_array[i];
                                second_array[i] = temp;
    }
}

int my_strlen(char string[])
{
    int length = 0;
    for (; string[length] != '\0'; length++);
    return length;
}

void print_array(char ** pointers_to_strings)
{
    for (int i = 0; i < 14; i++)
    {
        puts(pointers_to_strings[i]);
    }
}

char ** reading_strings(const char * file_name, int * number_of_strings)
{
    FILE * file = fopen(file_name, "r");
    char buffer[BUFFER_SIZE] = {};
    char ** strings = (char **)calloc(1, char *);

}
