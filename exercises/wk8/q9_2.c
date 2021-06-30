//This program uses a function called CharacterScan to read a char from the user
//The function must take an int pointer as a parameter
//The program should print the char and ascii code for each character the user enters
//The program should only exit whe nthe user enters escape


/*
Changes
1.acode mistypes as aCode
2.changed to use the value of the pointer in line 24 rather than the memory address of pointer
3.Syntax errors and adding \n in printf statements
4.Making the while loop actually run with a true condition
5.Making the code logic print the character entered unless it is the exit character w/ a code 27
*/

#include <stdio.h>
#include <stdlib.h>
char CharacterScan(int*);

int main(void){
    int* iPtr;
    char exit;
    while(1){
        char c = CharacterScan(iPtr);
	printf("%c %d\n", c, c);
        if((int)c == 27){
            printf("Exiting the code!\n");
            break;
        }
        else{	
            printf("%c is ASCII code %d.\n", c, c);
        }
    }
    return 0;
}

char CharacterScan(int* iPtr){
    char c;
    printf("Enter a character: \n");
    scanf(" %c", &c);
    int a = (int) c;
    iPtr = &a;
    return c;
}
