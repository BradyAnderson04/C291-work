/*
Notes for week 3

*/


#include <stdio.h>
#include <math.h>


// function prototypes
int maximum(int x, int y, int z); // function declaration ie: prototype also optional

void myfunction(int); // example declaration

int main(void){  
    int myVar = 100;
    printf("Inside main loop before call\n");
    myfunction(myVar); // calling the function
    printf("Inside main loop after call\n");

    return 0;
}

void myfunction(int myVar){
    printf("I am running from a function: %d\n", myVar);
}

/*
x y and z are parameteres
*/
int maximum(int x, int y, int z){
    int max = x;

    if ( y > max){
        max = y;
    }

    if(z > max){
        max = z;
    }

    return max;
}