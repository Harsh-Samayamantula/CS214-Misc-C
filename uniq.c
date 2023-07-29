#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char *string;      // Input string
    int count;         // Keeps track of frequency
    struct node *next; // Link to next node
};

// struct node* list = (struct node*) malloc(sizeof(struct node));
struct node *list = NULL;

int main(int argc, char **argv)
{
    // printf()
    char *input = NULL;
    size_t len = 0;
    getline(&input, &len, stdin);
    char *temp = (char *)calloc(len, sizeof(char));
    int res = 1; // Checks to see if input is different than previous input
    int val = 1; // Checks to see if input is null
    int frequency = 1;

    list = (struct node *)malloc(sizeof(struct node));
    list->string = (char *)calloc(len, sizeof(char));
    strcpy(list->string, input);
    list->count = frequency;
    // printf("List: %s", list->string);
    struct node *pointer = list;
    while (val != -1)
    {
        strcpy(temp, input);
        // printf("This is the input: %s", input);
        // printf("This is the temp string: %s", temp);

        val = getline(&input, &len, stdin);
        if (val == -1)
            break;

        res = strcmp(temp, input);

        // printf("Compare: %d\n", res);
        if (res == 0)
        {
            frequency++;
            pointer->count = frequency;
        }
        else
        {
            frequency = 1;
            struct node *newNode = (struct node *)malloc(sizeof(struct node));
            newNode->string = (char *)calloc(len, sizeof(char));
            strcpy(newNode->string, input);
            // newNode->string
            // printf("Making a new node and here is what is being inputted as the string: %s", newNode->string);
            newNode->count = frequency;
            newNode->next = NULL;
            // printf("List: %s", newNode->string);

            pointer->next = newNode;
            pointer = pointer->next;
        }

        free(temp);
        temp = (char *)calloc(len, sizeof(char));
    }

    pointer = list; // pointer looking at the very beginning of the list
    while (pointer != NULL)
    {
        printf("%d %s", pointer->count, pointer->string);
        struct node *tempNode = pointer;
        pointer = pointer->next;
        free(tempNode->string);
        free(tempNode);
    }
    free(temp);
    free(input);
}