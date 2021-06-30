// Program to read integers into a 3X3 matrix and display them
// Todo: Fix bugs and makesure program works as intended.
// for each bug fix, add a comments specifying what you fixed.
// Number of errors/bugs = 12


/*
Bug fixes:
1-6 : general syntax errors such as missing semicolon and improper declaration of a for loop, or wrong characters used
7-8 : function implementation didn't match function declaration
9-10 : fixing bounds of loop in display
11 : fixed array size to be the proper size to store the values
12 : made the reference to the value in display [i][size-j] (took away +1 in second index)
*/


#include <stdio.h>
void display(int Matrix[3][3],int size);

int main(void) {
	int size=3;
	int Matrix[size][size];
	printf("Enter 9 elements of the matrix:\n");
	int i;
	for (i = 0; i < size; i++)
    {
      int j;
      for (j = 0; j < size; j++){
        scanf(" %d", &Matrix[i][j]);
      }
    }
	display(Matrix,3);
	return 0;
}

void display(int Matrix[3][3], int size) {
	int i;
	for (i = 0; i < size; i++) {
		int j;
		for (j = size; j > 0; j--) 
        {
            printf("%d, ", Matrix[i][size-j]);
        }
        printf("\n");
	}
    
}
