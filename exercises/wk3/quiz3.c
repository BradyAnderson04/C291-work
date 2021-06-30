/* Instructions:
 *
 *
 1. Write a program to assign a grade to Student. 
	Get the number of assignmnets from user.
  Get the students score out of how many points for each assignmnet.
	Calculate percentage and return the grade associated with a range of marks.
 2. The overall score range and the associated grades are as follows:
     a. [97-100] = A+
     b. [90-97] = A
     c. [80-90] = B
     d. [70-80] = C
     e. less than 70 is a failing grade and should be given an F
     e. greater than 100 or less than 0 is invalid and your code should print "Invalid"
 3. Use the skeleton code provided below to create a new function "printGrade" to assign a grade based on the score ranges.
 4. Use print statements in your function to display the grade. For example, if the input marks is 77, the output should read:
        "Your grade is : C"
 5. Please adhere to standard C syntax conventions and use comments to explain your code. Failure to do so will result in a penalty.
 *
 *
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printGrade(double score);
double calcPercentage(float score, int assignments);

int main(void){
	char ch;
	float score; // just the total of all assignments summed together
	int assignments;
	do {
		// reinit vars to 0
		score = 0;

	//get the number of assignmnets from the student
		printf("How many assignmnets did you have ? ");
		scanf(" %d", &assignments);

    // for each assignment get the score
		int i;
		for(i=0;i<assignments;i++){
			float temp;
			printf("Enter your score for assignment %d : \n", i);
			scanf(" %f", &temp);

			score += temp;
		}

    //calculate the student's percentage in the class using the information you've gathered.
		double percent = score / assignments;

		printGrade(percent);

		printf(" \n Do you want to continue? (Y/N) ");
		scanf(" %c",&ch);
	} while(ch == 'y'|| ch == 'Y');
}

// function def

void printGrade(double score){
	char grade[2];
	//print the students grade based on their score in the class
	if(score >= 90){
		if(score >= 97){
			strcpy(grade, "A+");
		} else {
			strcpy(grade, "A");
		}
	} else if (score >= 80){
		strcpy(grade, "B");
	} else if(score >= 70){
		strcpy(grade, "C");
	} else {
		strcpy(grade, "F");
	}
	printf("Your grade is a : %s", grade);
}