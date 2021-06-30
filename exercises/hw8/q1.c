/*
Author: Brady Anderson
Date: March 26, 2021

Program:
Given a particular structure answer specific prompts

*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    struct patientinformation { 
    char patient_name[ 20]; 
    char*abbreviated_name; 
    unsigned int age; 
    struct { 
        char phone_number[ 11 ]; 
        char address[ 60 ]; 
        char city[ 20]; 
        char state[ 3 ]; 
        int zipCode;
        } physical_address; 
    bool istested; 
    struct { 
        char*test_date; 
        bool istested_positive; 
        } covid_results; 
    } healthrecord, *healthrecord_ptr;
    healthrecord_ptr = &healthrecord;

    // Questions to answer - write expression to access and print specified data

    // a)Member patient_name of structure healthecord. 
    strcpy(healthrecord.patient_name, "Brady");
    printf("%s\n", healthrecord.patient_name);

    // b)Member patient_name of the structure pointed to by healthrecord_ptr. 
    strcpy(healthrecord_ptr->patient_name, "Alec");
    printf("%s\n", healthrecord_ptr->patient_name);

    // c)Member abbreviated_name number of structure healthrecord. 
    healthrecord.abbreviated_name = (char*)malloc(15 * sizeof(char));
    strcpy(healthrecord.abbreviated_name, "B");
    printf("%s\n", healthrecord.abbreviated_name);

    // d)Member abbreviated_name of the structure pointed to by healthrecord_ptr. 
    strcpy(healthrecord_ptr->abbreviated_name, "A");
    printf("%s\n", healthrecord_ptr->abbreviated_name);

    // e)Create a new character array of appropriate size and assign abbreviated_name pointer to it 
    // for healthrecord and use it to print abbreviated_name of the structure pointed to by healthrecord_ptr. 
    char* newCharacter = (char*)malloc(10 * sizeof(char));
    strcpy(newCharacter, "TEST");
    healthrecord_ptr->abbreviated_name = newCharacter;
    printf("%s\n", healthrecord_ptr->abbreviated_name);
    
    // f)Member zipcode of structure member physical_address of structure healthrecord. 
    healthrecord.physical_address.zipCode = 47404;
    printf("%d\n", healthrecord.physical_address.zipCode);

    // g)Member address of structure member physical_address of the structure pointed to by healthrecord_ptr. 
    healthrecord_ptr->physical_address.zipCode = 47404;
    printf("%d\n", healthrecord_ptr->physical_address.zipCode);

    // h)Member istested of structure healthrecord.
    healthrecord.istested = true;
    printf("%d\n", healthrecord.istested);

    // i)Member istest_positive of structure member covid_results of structure healthrecord. 
    printf("%d\n", healthrecord_ptr->istested);

    // j)Member test_date   of structure member covid_results of structure  pointed  to  by  healthrecord_ptr. 
    healthrecord_ptr->covid_results.test_date = (char*)malloc(50 * sizeof(char));
    strcpy(healthrecord_ptr->covid_results.test_date, "March 26, 2021");
    printf("%s\n", healthrecord_ptr->covid_results.test_date);

    // k)Create an array 3 healthrecord and initialize each member to appropriate values and then print zip codes 
    // for all five patientinformation records using array.
    
    struct patientinformation *patients = (struct patientinformation*)malloc(5 * sizeof(struct patientinformation));
    // adding the data just doing a name and zip code for now -- could add more and take user input but that is out of scope
    int i = 0;

    for(i = 0; i < 5; i++){
        strcpy(patients[i].patient_name, "Default");
        patients[i].physical_address.zipCode = i;
    }

    // l)Create a new pointer to point to these 3 healthrecord and use it to initialize istested flag for all five records to true
    struct patientinformation *patients_ptr;
    patients_ptr = &patients;

    for(i = 0; i < 5; i++){
        (patients_ptr + i)->istested = true;
        printf("%d\n", (patients_ptr + i)->istested);
    }


    return 0;
}

