// Program to check if the given number is a palindrome
// Number of errors/bugs = 15

//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/*
Changes made
1.add return value to main of int type and made input void
2.add return type to function prototype and definition
3.initialize given_number in function to n
4.add a ; to end of main function return statement
5.made if statment evaluate if function returns a 0
6.made function definiton have a return type of int
7.change fucntion input to only be an int
8.chnaged return_value_function to an int
9.changed arg name to x in prototype
10.changed all instances of n to x
11.while loop runs while x != 0 now
12.Changed function call to func from func4
13.Changed logic in the func
*/

#include<stdio.h>

int func(int x);

int main(void) {
        int return_value_function = 12321;        


        return_value_function = func(return_value_function);
        if(!return_value_function){
                printf("It is not a palindrome \n");
        }
        else{
               printf("It is a palindrome \n");
        }
		
	return 0;
}


//the return value of your func should be true / false only
int func(int x)
{
                int given_number=x;
                int remainder=0;
		int temp=0;
                
                while (x != 0) {
                        remainder = x % 10;
                        temp = temp * 10 + remainder;
			x /=10;                        
                }
		printf("Given Number: %d\n Reversed Number: %d\n", given_number, temp);
                if (given_number == temp)
                {
                        return 1; // is a palindrome number
                }
                else
                {
                        return 0; // is not a palindrome number
                }
}

