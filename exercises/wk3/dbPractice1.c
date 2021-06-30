// The factorial of an integer is the product of the number with all
// the positive integers below it.

// For example: Factorial of 5 = 5 * 4 * 3 * 2 * 1 = 120

// Number of errors/bugs = 7

//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/*
Things I changed:
1.changed %f to %d for correct type
2.added \n to printf statment
3.change %c to %d in the last printf of main loop
4.fixed factorial return statment from recursive call that increases input to recursive call that decreaes input
5.changed the retrun in the if statement to return number * 1
6.fixed function input in function declaration to match the prototype
7.added & to scanf to avoid seg fault
*/

#include<stdio.h>

int factorial(int);

int main(void) {
	int n,fact;
	printf("Debugging Practice 1 - Quiz 3, Q3\n\n");
	printf("Please enter the number whose factorial you wish to find: \n");
	scanf(" %d",&n);
	fact = factorial(n);
	printf("The factorial of %d is %d\n", n, fact);
}


int factorial(int number) {
  if(number<=1)
    return number*1;
  return number * factorial(number-1);
}


 

