#include <stdio.h>     //for printf
#include <stdlib.h>    //for exit
#include "list.h"


void INITIALIZE_list (int length, struct List *list)
{
    (*list).pointer = (int *) malloc (length * sizeof(int));

    (*list).position = 0;

    for (int i = 0; i < length; i++)
        (*list).pointer[i]=0;
}

void ADD_list (int item, struct List *list)
{
    (*list).pointer[(*list).position] = item;
    (*list).position++;
}

void PRINT_list (struct List *list)
{
    for (int i = 0; i < (*list).position ; i++)
    {
        int num = (*list).pointer[i];
        if (num >= 1 && num <= 15) printf("L%02d ", num);
        if (num >= 16 && num <= 30) printf("I%02d ", num);
        if (num >= 31 && num <= 45) printf("N%02d ", num);
        if (num >= 46 && num <= 60) printf("U%02d ", num);
        if (num >= 61 && num <= 75) printf("X%02d ", num);
    }
    printf("\n\n");
}

int CHECK_list (int item, struct List *list)
{
    for (int i = 0; i < (*list).position ; i++)
    {
        if ( (*list).pointer[i] == item)
            return 1;
    }
    return 0;
}

long RANDOM (struct List *list)
{
    long num;
    int duplicate = 0;

    while (duplicate == 0)
    {
        num = (rand() % 75) + 1;
        if (CHECK_list (num, list) == 1) duplicate = 1;
        if (duplicate == 0) break;
        duplicate = 0;
    }
    return num;
}



