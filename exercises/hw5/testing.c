/*
Author: Brady Anderson

Date Updated: February 26, 2021

Program Description:
    This file is used to test things I am curious about that pertain to logic I am trying to implement
    for this specific assignment.

    ideas I was testing:
    1.How rand works with srand and w/o srand

*/

#include <time.h> 

int main(void)
{
    srand(time(0));

    int rv = (rand() % (20 - 8 + 1)) + 7;

    printf("%d\n", rv);

    return 0;
}