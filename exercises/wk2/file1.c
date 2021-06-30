/* Print the sum of products of odd and even numbers from 1 to 10
*  Print alternate characters from 'A' to 'Z' in the reverse order starting with 'Z'
*  Ouput of the program should look like:
    The value of limit is 10
    The Sum = 4785
    Z X V T R P N L J H F D B
*/

#include <stdio.h>

int main(){
    int limit = 10, even_product = 1, odd_product = 1, sum = 0, i = 0;
    char c;
    printf("The value of limit is %d\n", limit);
    for(i = 1; i <= limit; i++){ 
       if(i % 2 == 0){
           even_product *= i;
       }   
        if(i % 2 == 1){
           odd_product *= i;
       }
    }
    sum += even_product + odd_product;
    printf("The Sum = %d \n", sum);
    for(c = 'Z'; c >= 'B'; c-=2){
        printf("%c ", c);
    }
    printf("\n");
    fflush(stdout);
    
    return 0;
}


/*
Some changes I made:

1.changed first for loop bounds from 0 to 1-limit
2.made the for loop decipher between odd and even using modulus
3.calculated sum of products instead of sum of sums
4.made the letter for loop for capitals, fixed synatx errors, and added a final new line
5.fixed syntax errors
6.set initial int values to appropiate values

*/
