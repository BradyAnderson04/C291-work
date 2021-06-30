/*
Author: Brady Anderson
Date: 03/19/2021

Program: This is a file that is testing my syntax for assignment 7 answers

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define partTwoSize 10

// function prototypes
char* oppositeCaseString(char* word);
char* sumAllNums(char* data);

int main(void){

    // 1a Use an appropriate pointer to dynamically allocate memory for one integer value.
    int *ptr;
    ptr = (int*)malloc (1 * sizeof(int));

    // 1b Use an appropriate pointer to dynamically allocate memory for two double values

    double *dptr;
    dptr = (double*)malloc(2 * sizeof(double));

    // 1c Use an appropriate pointer to dynamically allocate memory for 5 integers, initialize them to some values and print them. Can’t use [].

    int *iptr, i;
    iptr = (int*)malloc (5 * sizeof(int));

    for(i = 0; i < 5; i++)
    {
        *(iptr + i) = i;
        printf("%d\n", *(iptr + i));
    }

    // 1d Use an appropriate pointer to dynamically allocate memory for 20 characters, initialize them to something and print them. Can’t use [].

    char *name;
    name = malloc(20 * sizeof(char));

    strcpy(name, "Brady Anderson");
    printf("Data stored in char pointer: %s\n", name);

    // 1e Use  an  appropriate  (double)  pointer  to  dynamically  allocate  memory  for  25  characters  for  2D  array,  initialize  them  to  some  values  and  print  them  in  2D  array  format  (like  a  matrix  or  table).  Can’t use [].

    char **phrases = (char**)malloc(25 * sizeof(char));
    for(i = 0; i < 5; i++){
        *(phrases + i) = (char*)malloc(5 * sizeof(char));
        strcpy(*(phrases + i), "Hello");
        printf("Phrase: %s\n", *(phrases + i));
    }

    // 1f Repeat part (e) with single pointer (Hint: 2D array is really a 1D array). 

    char *singlePhrase = (char*)malloc(25 * sizeof(char));
    for(i = 0; i < 25; i+=5){
        *(phrases + i) = (char*)malloc(5 * sizeof(char));
        strcpy(*(phrases + i), "World");
        printf("Phrase2: %s\n", *(phrases + i));
    }

    // 2. Opposite case string
    printf("\n\nIf you want to test bigger strings just change the value of the partTwoSize variable at the top of the file!\n");
    char* word = (char*)malloc(partTwoSize * sizeof(char));
    strcpy(word, "HelLoWorLD");

    printf("Input: %s\n", word);

    oppositeCaseString(word);

    printf("Output: %s\n", word);

    // 3. Sum values in a string
    /*
    double format YYYY.YY at most 2 decimal places
    integer format XXXX at most 4 numbers in a row

    */

    char* input = (char*)malloc(250 * sizeof(char));
    strcpy(word, "My 2 friends who are both 19.5 years old and also eat 3 meals a day sleeping for 6.8 hours on average a night.\n");
    
    printf("\n\nInput data: %s\n", word);

    sumAllNums(input);

    printf("\nOutput data: %s\n", word);

    // freeing up memory after using it -- cleanliness is important! -- please give feedback on where the freeing up of memory should be done / when it should be done


    return 0;
}

// function definitions
char* oppositeCaseString(char* word)
{
    /*
    Given a pointer iterate through and then change lower case to upper case and upper case to lower case.
    */
   int i;
   for(i = 0; i < strlen(word); i++){
        char temp = *(word + i);

        if(islower(temp))
        {
            *(word + i) = toupper(*(word + i));
        } 
        else 
        {
            
            *(word + i) = tolower(*(word + i));
        }
   }

   return word;
}

char* sumAllNums(char* data){
    // vars to store important data
    int i, intsum = 0;
    double doublesum = 0.0;
    const char* delim = (char*)malloc(2 * sizeof(char));
    char* token = (char*)malloc(15 * sizeof(char));

    delim = " ";

    token = strtok(data, delim);

    while(token != NULL)
    {
       	printf("%s\n", token);

        token = strtok(NULL, delim);
    }

    return data;
}
