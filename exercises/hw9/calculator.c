/*
Author:Brady Anderson
Date: April 9, 2021
Program:

    This program implements function pointers to perform simple operations of add, subtract,
    mulitply, divide, remainder, power.

    User provides input values and correct signals (+, -, *, /, %, ^) then prints the result

    additionally the program tries to be super simple for the user so simply typing an equation in a specified format 
    will output the result. the format does require a weird quit code but clear instruction is provided

*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// prototypes
double add(int a, int b);
double subtract(int a, int b);
double multiply(int a, int b);
double divide(int a, int b);
double rem(int a, int b);
double power(int a, int b);

void displayMenu();
int processChoice(char choice);

enum operations{ADD = '+', SUB='-', MUL='*', DIV='/', MOD='%', POW='^'};

int main(void){
    // create array of pointers to functions
    double (*f[6])(int, int) = {add, subtract, multiply, divide, rem, power};
    char* choice = malloc(sizeof(char) * 10);
    char op;
    int a, b;

    while(true){
        // allow user to chooce and display a menu
        displayMenu();
        // scanf to scan a specific format -> I view this as a bad thing but couldn't figure out enum reasonable quickly
        scanf(" %d%c%d", &a, &op, &b);
        // if quit code leave
        if(op == 'q'){
            break;
        } else {
            // convert the operation char to a relevant index
            int func = processChoice(op);

            if(func != -1){
                // if no errors then run the function with input args
                double result = (*f[func])(a, b);
                printf("%d %c %d = %.2lf\n", a, op, b, result);
            }
        }
    }
}


void displayMenu(){
    printf("Please enter one of the following codes to perform the action specified\n\ta+b\n\ta-b\n\ta*b\n\ta/b\n\ta%cb\n\ta^b\n\t0q0 to quit\n\tMake sure the values a and b are integers rather than the letters a and b.\n\n", '%');
}

double add(int a, int b){
    return a + b;
}
double subtract(int a, int b){
    return a - b;
}
double multiply(int a, int b){
    return a * b;
}
double divide(int a, int b){
    return (double)a / (double)b;
}
double rem(int a, int b){
    return a % b;
}
double power(int a, int b){
    return pow(a, b);
}

int processChoice(char choice){
    if(choice == '+'){
        return 0;
    }
    else if(choice == '-'){
        return 1;
    }
    else if(choice == '*'){
        return 2;
    }
    else if(choice == '/'){
        return 3;
    }
    else if(choice == '%'){
        return 4;
    }
    else if(choice == '^') {
        return 5;
    }
    else {
        printf("Invalid input please retry\n");
        return -1;
    }
}
