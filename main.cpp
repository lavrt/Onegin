#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main (void)
{
    struct stat st;
    stat("onegin.txt", &st);
    size_t size = st.st_size;

    FILE * file = fopen("onegin.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return 0;
    }

    char * buffer = (char *)calloc(size, sizeof(char));
    char ** strings = (char **)calloc(1, sizeof(char *));

    fread(buffer, sizeof(char), 1 + size, file);

    int number_of_strings = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] != EOF)
        {
            if (buffer[i] == '\n')
            {
                strings[number_of_strings] = buffer + i;
                number_of_strings++;
                strings = (char **)realloc(strings, sizeof(char *) * (number_of_strings + 1)); // поч не работает без char **
            }
        }
    }

    printf("%c", *(*strings + 1));









    free(buffer); buffer == NULL;
    free(strings); strings == NULL;

    return 0;
}
