#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *lowercase(char *x)
{
    int l = strlen(x);
    for (int i = 0; i < l; i++)
    {
        x[i] = tolower(x[i]);
    }
    return x;
}

int main(int argc, char *argv[argc + 1])
{
    if (argc != 2 && argc != 3)
    {
        printf("error\n");
        return 0;
    }
    char *input = NULL;
    size_t len = 0;
    int val = getline(&input, &len, stdin);
    char *x = argv[argc - 1];
    while (val != -1)
    {
        if (argc == 2)
        {
            if (strstr(input, x))
            {
                printf("%s", input);
            }
        }
        else
        {
            char *checkifi = argv[1];
            if (strcmp(checkifi, "-i") == 0)
            {
                char *temp = (char *)calloc(len, sizeof(char));
                strcpy(temp, input);
                temp = lowercase(temp);
                x = lowercase(x);
                if (strstr(temp, x))
                {
                    printf("%s", input);
                }
                free(temp);
            }
            else
            {
                return 0;
            }
        }
        val = getline(&input, &len, stdin);
    }
}