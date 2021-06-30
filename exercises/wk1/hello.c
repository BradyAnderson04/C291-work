/* 
 * Basic C program to print out hello world! 
 * Author: Adeel Bhutta


   Assignment 0 - print name and how old the person is, by using user input

   Assignment 1 - create a program that counts down from 100

   Author: brjoande
*/

#include <stdio.h>
#include <unistd.h> // adding this for the sleep function for ease of grader

int main(void) {
  // init value to be printed
  int value = 1000;
  // welcome message
  printf("\"*****{Welcome to C291 Spring 2021 @IU}, %%%% Golden Rule: Start working on everything as early as possible %%% Thanks *****\"\n");
  // loop that prints as specified in assignment 1
  while(1==1){
    printf("%04d ", value);
    fflush(stdout);
    if(value % 2 == 0){
      // is even
      int i;
      for(i = 0; i < 5; i++){
        printf(".");
        fflush(stdout);
	sleep(1);
      }
    } 
    else {
	// this is odd case
      sleep(1);
    }
  value--;
  printf("\n");
  }
  return(0); 
}


