/*
Author: Brady Anderson
Date: March 8, 2021

Program Description:

Code for questions 3-5

*/

#include <stdio.h>
#include <stdbool.h>

int SIZE = 5;

bool mySwap(int * x, int * y);

int main(void){
    // Q3
    // printf("\nQuestion 3");

    // // a 
    // printf("\n\nPart A");
    short numbers[] = {1,2,3,4,5};

    // // b
    // printf("\n\nPart B");
    short *nPtr = numbers;
    // printf("%p", nPtr);
    
    // // c
    // printf("\n\nPart C\n");
    // int i;
    // for(i = 0; i < SIZE; i++){
    //     printf("%hu, ", numbers[i]);
    // }

    // d
    // printf("\n\nPart D\n");
    // short * nPtr = (nPtr + SIZE);
    // short * nPtr1 = &numbers[SIZE];

    // printf("%p %p\n", nPtr, nPtr1);

    // e
    // printf("\n\nPart E\n");
    // short * nPtr = &numbers;
    // int i;
    // for(i = 0; i < SIZE; i++){
    //     printf("%hu, ", *(nPtr + i));
    // }
    // printf("\n");

    // f
    // printf("\n\nPart F\n");
    // int i;
    // for(i = 0; i < SIZE; i++){
    //     printf("%hu, ", *(numbers + i));
    // }
    // printf("\n");

    // g

    // int i;
    // for(i = 0; i < SIZE; i++){
    //     printf("%hu, ", nPtr[ i ]);
    // }

    // h
    // printf("%hu %hu %hu %hu\n", numbers[1], *(numbers + 1), nPtr[1], *(nPtr + 1) );
    
    

    // i

    // j


    // // q4 testing
    // float number1, number2 = 5.3;
    // // a
    // float *fPtr;
    // // b
    // float *fPtr2;
    // // c
    // fPtr = &number2;
    // // d
    // printf("%f\n", *fPtr);
    // // e
    // number1 = *fPtr;
    // // f
    // fPtr2 = &fPtr;
    // // g
    // printf("%f\n", number1);
    // // h
    // printf("%p\n", &number2);
    // // i
    // printf("%p\n", fPtr);
    // // j
    // printf("%p\n", fPtr2);

    int x = 1, y = 2;

    printf("%d\n", mySwap(&x, &y));


    return 0;
}


bool mySwap(int * x, int * y){
    /*
    Switch the values of each pointer and return true if succesful
    */
    int x_val = *x;
    int y_val = *y;
    int * temp = x;

    x = y;
    y = temp;

    if(*x == y_val && *y == x_val){
        return true;
    } else {
        return false;
    }


}
