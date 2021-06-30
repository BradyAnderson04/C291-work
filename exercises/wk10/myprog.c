/*
Bugs I fixed:
1.make p a char instead of a pointer to char bc of how the loop was setup
2.remove wrongly placed semicolon on line 16
3.Have the initialize alphabet function use the value of 'a' as initial value instead of an undefined variable
4.make the array a have an element added to the end using strcat
5.changed bound of for loop from a to a + 26
6.made the value printed the pointer that was iterating through the provided argument
7.made it so the pointer set was not made null
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS 26

char alphabet[MAX_LETTERS];

void initialize_alphabet(char *a) {
  char *p = (char*)malloc(MAX_LETTERS*sizeof(char));
  char current_letter = 'a';
  for (p=a;p<(a + MAX_LETTERS);p++){
    *p = current_letter++;
  }
  printf("\n");
}  

void reverse_print_alpha(char *b) {
  static int var = 0;
  char *p;
  
  // var?(p=NULL):(b=NULL);
  var += 1;
  printf("\nReverse alpha...\n");
  initialize_alphabet(b);
  for (p=(b+MAX_LETTERS-1);p>=b;p--){
    printf("%c ",*p);
  }
  printf("\n");
  return ;
}

int main(void) {
  int i = 0;
  while (i++ < 5) {
    reverse_print_alpha(alphabet);
  }
}

  

  
