/*Debugging quiz - File No: 3 */
/* This program should perform the duties of a calculator 
    The program should ask for the input until 'q' is entered. 
    For each operation, print the result and then print whether the result is >100 or <100 or equal to 100
    Finally, print the number of calculations done until 'q' is entered */

// Check for possible logical errors and rectify them 

/*
changelog
1.Fixed syntax errors
2.Make the proper logic flow with case and if statements
3.added a quit option to menu
4.fixed memory reference errors with scanf
5.fixes typos

*/


#include<stdio.h>

int main(void){
  char input;
  int num1, num2, result, count = 0;
   
  while(input != 'Q' )
  {
  printf("Welcome to the Calculator\nOperation choices:\tAddition(A)\n\t\t\tSubtraction(S)\n\t\t\tMultiplication(M)\n\t\t\tDivision(D)\n\t\t\tQuit(Q)\nEnter choice: ");

  scanf(" %c", &input);

  if(input == 'A' || input == 'S' || input == 'M' || input == 'D'){
    printf("Enter both numbers in required sequence: \n");
    scanf("%d %d", &num1, &num2);
    switch(input){
        case 'A': 
                result = num1 + num2;
                break;  
        case 'S': 
                result = num1 - num2;
		break; 
       case 'M': 
                result = num1 * num2;
		break;
	case 'D':
		result = num1 / num2;
		break;  
    }
    printf("Result is %d \n", result);
    if(result > 50){
      printf("Greater than 50.\n");
    }
    else if(result < 50) {
      printf("Less than 50\n");
    }
    else if(result == 50){
      printf("Equal to 50\n");
    }
    else{
	printf("Please choose a valid operation\n");   
   }
  count++;
  printf("Number of operations performed: %d\n",count);
  } 
  if(input == 'Q')
  printf("Quit the menu.\n");
  }
 return(0);
}
