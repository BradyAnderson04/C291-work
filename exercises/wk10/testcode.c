/*
Author: Brady Anderson
Date: 05/04/2021

Program:
A file that is used to test ideas quickly in C

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct a {double x, y;};

typedef struct a P;

// struct Node{
//     char ch;
//     int in;
//     P *pt;
// } n;

struct Point {double x, y, z;} pt = {.y=10};

// #define override(a, b) a##b

int main(void){
    // char * *myarray = {"A", "Very", "Weird", "Year"};
    // // myarray = myarray + 5;
    // // printf("%s\n", myarray);
    // printf("here\n");
    // char* p = *myarray+2;
    // printf("here\n");
    // printf("%c \n", *p);
    // int xy, z = 10;
    // printf("%x\n", override(xy, z));
    printf("%f %f %f\n", pt.x, pt.y, pt.z);
}


