//This program should read a string from the user and print it using a character pointer
//The program is setup to use pointer offset notation to get each character of the string

/*
Changes made
1.Syntax errors in scanf
2.While loop iteration logic
  pointer offset notation, not decrementing the value
  added a prompt for ease of grading
3.corrected the printf format type specifier
4.adding a return value
5.Make the main a int return type
*/

#include <stdio.h>
#include <string.h>

int main(void){
    char s[20];
    char *cPtr;
    printf("Enter a string and press ENTER:\n");
    scanf(" %s", s);
    cPtr = s;
    while(*(cPtr) != '\0'){
        printf("%c", *(cPtr++));
    }
  printf("\n");
  return 0;
}