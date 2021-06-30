/*
Author: Brady Anderson
Date: April 8, 2021
Program:
    opens a file and records 30 records with appropiate default values / inputted values

    implement a way to write new data to the file

    allow a user to search the file for specific data based off last name, gender, covid test results or
    a combination of 2 of these search parameters. When record(s) are found print them ow. print No info found

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 30
// define this var to update it over time if needed
int updatedSize = SIZE;


// structs and function prototypes as well as simple helper function implementation

struct covidData {
    // chose to interpret bool as an int 1 = true, 0 = false
    int isCovidPositive;
    char testDate[15];
};

typedef struct patient{
    char lastName[15];
    char firstName[15];
    char gender;
    struct covidData *covidInfo;
} Patient;

void displayMenu();
void searchFile(Patient* data);
void createNewInstance(Patient* data);
void deleteRepeatData(Patient* data);
void readData(FILE *fPtr, Patient* data);
void writeData(FILE *fPtr, struct patient data[30]);
int compareDates(Patient one, Patient two);

void lower(char* word){
    int i;
    for(i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
}

int main(void){

    printf("%d\n", strcmp("2020", "2021"));
    printf("%d\n", strcmp("2021", "2020"));
    FILE *fPtr;
    Patient* data = malloc(sizeof(Patient) * 30);
    
    // init data structure
    readData(fPtr, data);

    // menu for user action
    bool menuActive = true;
    while(menuActive){
        char menuChoice;
        displayMenu();

        scanf(" %c", &menuChoice);

        switch(menuChoice){
            case 'N':
                printf("Create New User Portal\n\n");
                createNewInstance(data);
                break;
            case 'S':
                printf("Search for a user portal\n\n");
                searchFile(data);
                break;
            case 'Q':
                menuActive = false;
                // delete and write operations performed automatically at the end of the program running
                deleteRepeatData(data);
                writeData(fPtr, data);
                // memory management and pointer management
                free(data);
                break;
            default:
                printf("The menu is case sensitive please type the code in upper case as shown.\n\n");
        }

    }
    

}

void displayMenu(){
    printf("Please enter one of the following codes to perform the action specified\n\tInput New User Data: \tN\n\tSearch Dataset: \tS\n\tQuit: \t Q\n");
}

void searchFile(Patient* data){
    // local vars
    int i, menuOption, covidResult;
    char lName[15];
    char gender;
    bool resultFound = false;
    // prompt for search option...not most effective but without a gui don't have a selective manner to do this will unfortuantely have to repeat code
    printf("Decide how to search:\n\t1-Last Name Only\n\t2-Gender Only\n\t3-covid result only\n\t4-Last name and gender\n\t5-Last name and covid result\n\t6-Gender and covid result\n\n");
    scanf(" %d", &menuOption);

    if(menuOption == 1){
        printf("Please provide the last name and press ENTER\n");
        scanf(" %s", lName);
        lower(lName);

        for(i = 0; i< updatedSize; i++){
            if(strcmp(data[i].lastName, lName) == 0){
                printf("%s %s %c %d %s\n", data[i].lastName, data[i].firstName, data[i].gender, data[i].covidInfo->isCovidPositive, data[i].covidInfo->testDate);
                resultFound = true;
            }
        }
    }
    else if(menuOption == 2){
        printf("Please provide the gender and press ENTER\n");
        scanf(" %c", &gender);

        for(i = 0; i< updatedSize; i++){
            if(data[i].gender == gender){
                printf("%s %s %c %d %s\n", data[i].lastName, data[i].firstName, data[i].gender, data[i].covidInfo->isCovidPositive, data[i].covidInfo->testDate);
                resultFound = true;
            }
        }
    }
    else if(menuOption == 3){
        printf("Please provide the covid result and press ENTER\n");
        scanf(" %d", &covidResult);

        for(i = 0; i< updatedSize; i++){
            if(data[i].covidInfo->isCovidPositive == covidResult){
                printf("%s %s %c %d %s\n", data[i].lastName, data[i].firstName, data[i].gender, data[i].covidInfo->isCovidPositive, data[i].covidInfo->testDate);
                resultFound = true;
            }
        }
    }
    else if(menuOption == 4){
        printf("Please provide the last name and press ENTER\n");
        scanf(" %s", lName);
        lower(lName);

        printf("Please provide the gender and press ENTER\n");
        scanf(" %c", &gender);

        for(i = 0; i< updatedSize; i++){
            if(strcmp(data[i].lastName, lName) == 0 && data[i].gender == gender){
                printf("%s %s %c %d %s\n", data[i].lastName, data[i].firstName, data[i].gender, data[i].covidInfo->isCovidPositive, data[i].covidInfo->testDate);
                resultFound = true;
            }
        }

    }
    else if(menuOption == 5){
        printf("Please provide the last name and press ENTER\n");
        scanf(" %s", lName);
        lower(lName);
        
        printf("Please provide the covid result and press ENTER\n");
        scanf(" %d", &covidResult);

        for(i = 0; i< updatedSize; i++){
            if(strcmp(data[i].lastName, lName) == 0 && data[i].covidInfo->isCovidPositive == covidResult){
                printf("%s %s %c %d %s\n", data[i].lastName, data[i].firstName, data[i].gender, data[i].covidInfo->isCovidPositive, data[i].covidInfo->testDate);
                resultFound = true;
            }
        }
    }
    else {        
        printf("Please provide the gender and press ENTER\n");
        scanf(" %c", &gender);

        printf("Please provide the covid result and press ENTER\n");
        scanf(" %d", &covidResult);

        for(i = 0; i< updatedSize; i++){
            if(data[i].covidInfo->isCovidPositive == covidResult && data[i].gender == gender){
                printf("%s %s %c %d %s\n", data[i].lastName, data[i].firstName, data[i].gender, data[i].covidInfo->isCovidPositive, data[i].covidInfo->testDate);
                resultFound = true;
            }
        }
    }

    if(!resultFound){
        printf("No info found\n");
    }

}

void createNewInstance(Patient* data){
    // local vars
    int i;
    char lName[15], fName[15], date[15];
    char gender;
    // could remove boolean checker since making use of the break now
    bool userAdded = false;
    // get user input 
    printf("Enter your first name and press ENTER\n");
    scanf(" %s", fName);
    
    printf("Enter your last name and press ENTER\n");
    scanf(" %s", lName);

    printf("Enter your biological gender as m or f or o and press ENTER\n");
    scanf(" %c", &gender);

    printf("Enter your covid test date in format dd-mm-yyyy and press ENTER\nNote, the amount of digits in the formatted date must be the same as characters shown ex: 02-07-2008.");
    scanf(" %s", date);
    // place it in array to be written to file later
    for(i = 0; i< updatedSize; i++){
        if(strcmp(data[i].firstName, "''") == 0 && !userAdded){
            printf("%d\n", i);

            // found a default value enter data and leave loop
            lower(lName);
            lower(fName);

            strcpy(data[i].firstName, fName);
            strcpy(data[i].lastName, lName);
            data[i].gender = gender;
            data[i].covidInfo->isCovidPositive = (i % 2 == 0) ? 0 : 1;
            strcpy(data[i].covidInfo->testDate, date);
            
            userAdded = true;
            break;
        }
    }
}

void deleteRepeatData(Patient* data){
    // double nested for loops to make unique compairsons
    int i, j;
    for(i = 0; i <updatedSize-1; i++){
        for(j = i + 1; j < updatedSize; j++){
            if(strcmp(data[i].lastName, data[j].lastName) == 0 && strcmp(data[i].lastName, data[j].lastName) == 0){
                // duplicate entry will be someone with the same first and last name
                if(strcmp(data[i].lastName, "Unassigned") != 0){
                    // only process non default values
                    // compare dates - if value < 0 then change data[i] o.w. change data[j]
                    int date = compareDates(data[i], data[j]);
                    // reset correct val to default
                    if(date < 0){
                        // change data[i]
                        strcpy(data[i].firstName, "''");
                        strcpy(data[i].lastName, "Unassigned");
                        data[i].gender = 'm';
                        data[i].covidInfo->isCovidPositive = (i % 2 == 0) ? 0 : 1;
                        strcpy(data[i].covidInfo->testDate, "1-1-2021");
                    } 
                    else {
                        strcpy(data[j].firstName, "''");
                        strcpy(data[j].lastName, "Unassigned");
                        data[j].gender = 'm';
                        data[j].covidInfo->isCovidPositive = (j % 2 == 0) ? 0 : 1;
                        strcpy(data[j].covidInfo->testDate, "1-1-2021");
                    }

                }
            }
        }
    }
}

int compareDates(Patient one, Patient two){
    char oneDate[15];
    char twoDate[15];
    strcpy(oneDate, one.covidInfo->testDate);
    strcpy(twoDate, two.covidInfo->testDate);

    char* substring1 = malloc(sizeof(char) * 5);
    char* substring2 = malloc(sizeof(char) * 5);
    
    if(strcmp(strncpy(substring1, oneDate+6, 4), strncpy(substring2, twoDate+6, 4)) != 0){
        // check year
        return strcmp(strncpy(substring1, oneDate+6, 4), strncpy(substring2, twoDate+6, 4));
    }
    else if(strcmp(strncpy(substring1, oneDate+3, 2), strncpy(substring2, twoDate+3, 2)) != 0){
        // years equal check months
        return strcmp(strncpy(substring1, oneDate+3, 2), strncpy(substring2, twoDate+3, 2));
    } 
    else {
        // months equal check days
        return strcmp(strncpy(substring1, oneDate, 2), strncpy(substring2, twoDate, 2));
    }
}

void readData(FILE *fPtr, Patient* data){
    if((fPtr = fopen("nameage.dat", "r+")) == NULL){
        puts("File could not be opened\n");
    }
    else {
        int temp;
        int i = 0;
        while(!feof(fPtr)){
            if(i+1 > SIZE){
                // need to realloc for another spot -- not sure if this is a good way of doing it as it seems taxing but can't think of another way
                data = realloc(data, i * sizeof(Patient));
                updatedSize++;
            }
            data[i].covidInfo = malloc(sizeof(struct covidData));
            // scan data of the structure defined below -- an empty newline will cause an error
            fscanf(fPtr, "%s %s %c %d %s", data[i].lastName, data[i].firstName, &data[i].gender, &data[i].covidInfo->isCovidPositive, data[i].covidInfo->testDate);
            i++;
        }
        // reset the pointer since we want to use this pointer on other functions
        rewind(fPtr);
    }
}

void writeData(FILE *fPtr, struct patient data[30]){
    if((fPtr = fopen("nameage.dat", "w+")) == NULL){
        puts("File could not be opened\n");
    }
    else {
        int temp;
        int i = 0;
        for(i = 0; i < updatedSize; i++){
            fprintf(fPtr, "%s %s %c %d %s", data[i].lastName, data[i].firstName, data[i].gender, data[i].covidInfo->isCovidPositive, data[i].covidInfo->testDate);
            if(i!=updatedSize-1){
                fprintf(fPtr, "\n");
            }
        }
        // reset the pointer since we want to use this pointer on other functions
        rewind(fPtr);
    }
}
