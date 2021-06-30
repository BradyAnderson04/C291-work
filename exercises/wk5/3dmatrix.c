// Program to read 3-dimensional matrix and display the elements as 1x9 matrix
// Review the slide titled "Mmeory Organization of Arrays in Ch6" for more details
// TODO
// User may specify any number of rows, columns and depth. Use those to create matrix
// initize matrix using update_3d method
// display method must not be able to modify array elements (update the code as needed)
// display method must use a single loop/iterator to print the entire array with addresses
// display cannot use nested loops
// 

// you will define the size of the array by using the size variable. I am making this a square n dimentional array so n x n x n arrays only

#include <stdio.h>
#define SIZE 3

void update_3d(double Matrix_3d[][SIZE][SIZE],int size); 
void display_1d(double Matrix_3d[][SIZE][SIZE],int size); 

int main(void) {
	//prompt the use to enter appropriate dimensions and initializ the matrix accordingly
	double Matrix_3d[SIZE][SIZE][SIZE] = {};
	//initialize the array to non-zero values (use scanf or random numbers generator)
	update_3d(Matrix_3d, SIZE);
	//display the values
	display_1d(Matrix_3d, SIZE);
	return 0;
}

void update_3d(double matrix[][SIZE][SIZE], int size) {
	printf("Enter 27 elements of the matrix:\n");
	int i;
	for (i = 0; i < SIZE; i++)
    {
      int j;
      for (j = 0; j < SIZE; j++)
	  {
	      int k;
	      for (k = 0; k < SIZE; k++)
		  {
	        scanf(" %lf", &matrix[i][j][k]);
	      }
      }
    }
}


//update as needed. 1 for loop only with 1 iterator to print all values with addresses
//must not be able to update the array.
//Share any observations.
void display_1d(double Matrix_3d[][SIZE][SIZE],int size) {
	int i;
	for (i = 0; i < (size * size * size); i++) {
		int height = i / size % size;
		int column = i % size;
		int row = i / size / size;
       	printf("%p (%0.2f)\n\n", &Matrix_3d[row][column][height], Matrix_3d[row][column][height]);
    }
}

/*
observations:
1.the array can have indexes generated
2.I could also index by memory iterating the memory spot by how ever many bits the element takes
3.the elements memory inc by 8 every single time (base 16) so the size of a double must bew 8 bits
4.Additionally, I had trouble with a segfault when writing and then displaying data so the writing process does something important in terms of memory
	|-> this wasn't too clever of a statement my seg fault error was from me not initializing the array's values
*/
