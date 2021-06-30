// Program to count the input characters. 
// It reads the input from the keyboard until user hits ENTER
// and then prints it on screen.  
// Number of errors/bugs = 13

//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/*
Changes I made:
1.changed c to char
2.changed main function declaration return value and input value
3.declared i as an int variable 
4.put comma in printf statement instead of colon
5.make loop output the char being processed
6.add condition to for loop to end when null character entered
7.put comma between i and count vars in for loop
8.remove count-- from loop
9.change \m to \t
10.added \n to end of the printf statment post loop
11.change %s to %d to print num of chars
12.change count to i
13.put getchar() in the loop so the value can change
14.add a getchar() before loop 
*/


#include<stdio.h>
int main(void)
{
	char allinput[1000];
	char count;
	int i;

	count =	getchar();

	for (i=0; count != '\n'; ++i)
	{	
		allinput[i] = count;
		count = getchar();	
 	} 
 	printf("Input: %s\n num of chars including spaces: %d\n",allinput, i);
 	return 1; 
}
