#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    int num;
    char *string;
    struct node *next;
    int strLength;
};

char *toLowercase(
    char *string,
    int length)
{
    char *newString = (char *)calloc(length, sizeof(char));
    for (int i = 0; string[i] != '\0'; i++)
    {
        newString[i] = tolower(string[i]);
    }
    return newString;
}

struct node *sortedItems = NULL;

void sorted_insert(
    int num,
    char *str,
    int lexicographically,
    int strlength)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->num = num;
    newNode->string = (char *)calloc(strlength, sizeof(char));
    if (strlength > 0)
        strcpy(newNode->string, str);

    newNode->strLength = strlength;

    if (lexicographically == 1)
    {

        if (sortedItems == NULL)
        {
            newNode->next = sortedItems;
            sortedItems = newNode;
        }
        else
        {
            char *cmp1 = toLowercase(newNode->string, newNode->strLength);
            char *cmp2 = toLowercase(sortedItems->string, sortedItems->strLength);
            int compareVal = strcmp(cmp1, cmp2);
            if (compareVal < 0)
            {

                newNode->next = sortedItems;
                sortedItems = newNode;
            }
            else
            {
                struct node *ptr = sortedItems;
                struct node *prev = sortedItems;
                while (ptr->next != NULL && compareVal >= 0)
                {
                    prev = ptr;
                    ptr = ptr->next;
                    free(cmp2);
                    cmp2 = toLowercase(ptr->string, ptr->strLength);
                    compareVal = strcmp(cmp1, cmp2);
                }

                newNode->next = prev->next;
                prev->next = newNode;
            }
            free(cmp1);
            free(cmp2);
        }
    }
    else
    {
        // newNode->string = NULL;
        if (sortedItems == NULL || num < sortedItems->num)
        {
            newNode->next = sortedItems;
            sortedItems = newNode;
        }
        else
        {
            struct node *ptr = sortedItems;

            while (ptr->next != NULL && ptr->next->num <= num)
            {
                ptr = ptr->next;
            }

            newNode->next = ptr->next;
            ptr->next = newNode;
        }
    }
}

int main(int argc, char **argv)
{

    int lexicographically = 1;
    char *sortType = NULL;
    if (argc > 1)
    {
        sortType = argv[1];
        int cmp = strcmp(sortType, "-n");
        if (cmp == 0)
            lexicographically = cmp;
    }

    char *input = NULL;
    size_t len = 0;
    int val = getline(&input, &len, stdin); // Checks to see if input is null
    if (val == -1)
        return 1;

    if (lexicographically == 1)
    { // with letters

        while (val != -1)
        {
            sorted_insert(0, input, lexicographically, len);
            val = getline(&input, &len, stdin);
        }

        while (sortedItems != NULL)
        {
            printf("%s", sortedItems->string);
            struct node *tempNode = sortedItems;
            sortedItems = sortedItems->next;
            free(tempNode->string);
            free(tempNode);
        }
    }
    else
    { // with numbers
        int num;
        while (val != -1)
        {
            num = atoi(input);
            sorted_insert(num, NULL, lexicographically, 0);
            val = getline(&input, &len, stdin);
        }

        while (sortedItems != NULL)
        {
            printf("%d\n", sortedItems->num);
            struct node *tempNode = sortedItems;
            sortedItems = sortedItems->next;
            free(tempNode);
        }
    }
    free(input);
}