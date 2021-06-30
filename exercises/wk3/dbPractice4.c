// Program to calculate the power of given equation - > x^n
// example - 2^10 -> 1024
// Number of errors/bugs = 13

//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/*
changes made
1.change return type of main
2.change return type of my_power function to match the definition (double)
3.changing some function logic
4.removed extra args from prototype
5.declared return_value_function type
6.fixed definition of function args to match prototype
7.added semicolon missing in my_power
8.declared ans type
9.fixed syntax for ternary opertor in my_power
10.changed other function arg to int and switched all chars to int type to fix seg fault
11.fixed recursive call to have proper types
12. Removed buggy hard to read code from my_power with simple recursion which imo is the best solution
*/

#include<stdio.h>

double my_power(int x, int n);

int main() 
{
		int x =2, return_value_function;
		int n = 10;
		
		return_value_function = my_power(x, n);
		printf("The power value of %d ^ %d is :: %d \n", x,n,return_value_function);
		return 0;
}


//the return value of your func should be x^n result
double my_power(int x, int n) {
    double ans=1.0;
    if(n == 0)
        return 1.0;
    if(n == 1)
        return x;

    int m = n>0 ? n : -n; // reverse the sign if negative for loop reasons
    int cur = 1.0;

    // while loop should basically result in getting m - 1 recursively 
    // while(cur < m) {
    //     cur += 1;
    // }
    // ans *= my_power(x, (m-cur));
    // return n>0 ? ans : 1.0/ans;

    return n>0 ? x * my_power(x, n-1) : 1.0/(x * my_power(x, n-1));
    // esstially want to do this in the loop
}

