#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int input = atoi(argv[1]), factor = 2;

    while (input > 1)
    {
        if (input % factor == 0)
        {
            printf("%d ", factor);
            input /= factor;
        }
        else
            factor += 1;
    };

    printf("\n");
    return 0;
}