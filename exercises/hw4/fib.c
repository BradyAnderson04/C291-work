/*
    Author: Brady Anderson
    Date: 2/19/2021

    Program:
    checks if the nth number in the fibbonaci sequence is prime or not

*/
// headers
#include <stdio.h>
#include <stdlib.h>

// function prototypes
int is_prime(int n);
int is_fib_prime(int n);

int main(void){

    // composite: 9, 18, 26, 77, 54
    // prime: 2, 11, 23, 47, 97

    // test values under 10
    int b1 = is_fib_prime(4);
    int b2 = is_fib_prime(6);
    int b3 = is_fib_prime(8);
    
    // prime tests
    int b4 = is_fib_prime(3);
    int b5 = is_fib_prime(5);
    int b6 = is_fib_prime(7);

    printf("Not Prime: %d %d %d\n", b1, b2, b3);

    printf("Prime: %d %d %d\n", b4, b5, b6);


    // test values greater than 9
    // composite tests
    int b7 = is_fib_prime(10);
    int b8 = is_fib_prime(12);
    int b9 = is_fib_prime(14);
    int b10 = is_fib_prime(16);
    int b11 = is_fib_prime(18);
    
    // prime tests
    int b12 = is_fib_prime(11);
    int b13 = is_fib_prime(13);
    int b14 = is_fib_prime(17);
    int b15 = is_fib_prime(19);
    

    printf("Not Prime: %d %d %d %d %d\n", b7, b8, b9, b10, b11);

    printf("Prime: %d %d %d %d\n", b12, b13, b14, b15);

/*
For n between 3 and 10 it is not true that the nth fibonachi number is prime an example of this is when 
n = 4, the output value is expected to be not prime by the hypothesis, however the output value is 3 which 
is prime so the hypothesis is incorrect for the range defined. In every other test case from 3-9 the output is indeed
prime  when the in put n is prime, while the output is compositive when the input is composite


When the n in put gets above 10....

for values 10-19 the when n is prime, the output is prime and when the input is composite the fibonacci number is composite

this remains true for all values except 19 which is evidently not prime as a fibonacci number


*/


}

int is_prime(int n)
{
    // check if a value is prime
    int i; 

    for(i=2;i<n;i++){
        if(n%i == 0 && n != i){
            // value is not prime
            return 0;
        }
    }
    // end of loop value is prime
    return 1;
}

int is_fib_prime(int n)
{
    /*
    implement the iterative appraoch to fibbinachi sequence and 
    check if the value is prime

    for n 3-10 fib value is prime when n is prime
    */
    int i;
    // iterative sequence -- could use memoization to make more efficient
    int t1 = 0;
    int t2 = 1;

    if(n == 0)
        // 0th term is 0 n is not prime or composite
        return 0;
    else if(n <= 2)
        return 1;
    else {
        for(i=0;i<n-1;i++){
            int temp = t1 + t2;
            // printf("%d + %d = %d\n", t1, t2, temp); // for printing out sequence 
            t1 = t2;
            // t2 will be out output that we are looking for
            t2 = temp;  
        }
    }

    // printf("%d\n", t2);

    printf("\n");
    // check prime
    return is_prime(t2);
}
