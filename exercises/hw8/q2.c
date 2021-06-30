/*
Author: Brady Anderson
Date: March 26, 2021
Program: 
create a prototype health record system as specified in the assignment pdf
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// function prototypes
double calculate_bmi(double weight, double height);
int calc_age(int day, int month, int year);
int calc_max_heartrate(int age);
struct HeartrateRange *calc_target_heartrate_range(int max_heartrate, int age);

// data structures
struct HeartrateRange {
    double low;
    double high;
};

struct HealthProfile {
    char first_name[20];
    char last_name[20]; 
    char gender[2];
    struct {
        int month;
        int day;
        int year;
    } dob;
    double height;
    double weight;
    struct {
        bool heartIssue;
        bool bloodPressureIssue;
        bool cancerIssue;
    } family_history;
};

int main(void){

    // helpful constants for flow logic
    double average_age;

    // create 10 Health Profile objects
    struct HealthProfile *patients = (struct HealthProfile*)malloc(10 * sizeof(struct HealthProfile));

    // populate with data
    int i = 0;

    for(i = 0; i < 10; i++){

        struct HealthProfile *temp = (patients + i);

        printf("Please enter the patient's first name\n");
        scanf(" %s", temp->first_name);
        printf("Please enter the patient's last name\n");
        scanf(" %s", temp->last_name);
        printf("Please enter the patient's gender you must enter (m/f/o)\n");
        scanf(" %s", temp->gender);
        printf("Please enter the patient's date of birth mm/dd/yyyy format\n");
        scanf(" %d/%d/%d", &temp->dob.month, &temp->dob.day, &temp->dob.year);
        printf("Please enter the patient's height in inches\n");
        scanf(" %lf", &temp->height);
        printf("Please enter the patient's weight in pounds\n");
        scanf(" %lf", &temp->weight);
        printf("Please enter 1 if the patient has a family history of heart issues, ow. enter 0\n");
        scanf(" %d", &temp->family_history.heartIssue);
        printf("Please enter 1 if the patient has a family history of blood pressure issues, ow. enter 0\n");
        scanf(" %d", &temp->family_history.bloodPressureIssue);
        printf("Please enter 1 if the patient has a family history of cancer issues, ow. enter 0\n");
        scanf(" %d", &temp->family_history.cancerIssue);

        // calculate some constants
        average_age += calc_age(temp->dob.day, temp->dob.month, temp->dob.year);
    }

    average_age /= 10;

    // Display the order of names from BMI high -> low -- create a function for this

    char * highRiskPatients = (char*)malloc(200 * sizeof(char));
    strcpy(highRiskPatients, " ");

    for(i = 0; i < 10; i++){
        struct HealthProfile *temp = (patients + i);
        struct HeartrateRange *range = (struct HeartrateRange*)malloc(sizeof(struct HeartrateRange));
        double bmi = calculate_bmi(temp->weight, temp->height);
        int age = calc_age(temp->dob.day, temp->dob.month, temp->dob.year);
        // id all patients with 2+ Family issues
        if(temp->family_history.bloodPressureIssue + temp->family_history.heartIssue + temp->family_history.cancerIssue >= 2){
            strcat(highRiskPatients, temp->first_name);
        }
        
        // obese/underweight and 2+ issues and older than average
        if((bmi < 18.5 || bmi > 30) && temp->family_history.bloodPressureIssue + temp->family_history.heartIssue + temp->family_history.cancerIssue >= 2 && age > average_age)
        {
            /*
                1.display all the function outputs
                2.ask for current heart rate
                    - advise to see physician if out of range and have history of heart problems or blood pressure
                3.If obese/underweight and family history include cancer advise to see oncologist
            */
            // age and bmi already calculated so no need to redo since those were needed to check this condition
            range = calc_target_heartrate_range(calc_max_heartrate(age), age);
            if(temp->family_history.cancerIssue)
            {
                printf("I advise that you seek attention from an oncologist due to you being obese/underweight and having a family history of cancer.\n");
            }
            printf("BMI: %lf\nAge: %d\nHeart rate range: %lf-%lf\n", bmi, age, range->low, range->high);

            // already has heart or blood problem at the very least so this is a given and should always run 
            printf("If your current heart rate is outside of the range displayed above, please consider seeing a physician.\n");
        }
    }
    printf("All patients at high risk with 2 or more family history of issues:\n\t%s\n", highRiskPatients);
    free(highRiskPatients);
    free(patients);
    return 0;
}

// function implementation
double calculate_bmi(double weight, double height)
{
    return (weight * 703) / pow(height, 2.0);
}

int calc_age(int day, int month, int year)
{
    // since in years the precision of day is only necesary to check if it is a full year

    // get the current time from system
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    int cmonth = local->tm_mon+1, cday = local->tm_mday, cyear = local->tm_year + 1900;

    // printf("Date is : %02d/%02d/%d\n", local->tm_mday, local->tm_mon+1, local->tm_year + 1900);
    if(month == cmonth)
    {
        // birth month is the current month -- need to check days
        if(cday >= day){
            // birthday has arrived so round up
            return cyear - year;
        } else {
            // birthday hasn't arrived yet so round down
            return cyear - year - 1;
        }
    }
    else if(month > cmonth)
    {
        // birth month has not arrived yet -- rounding down here
        return cyear - year - 1;
    }
    else 
    {
        // month is before the current month
        return cyear - year;
    }
}

int calc_max_heartrate(int age)
{
    return 200 - age;
}

struct HeartrateRange *calc_target_heartrate_range(int max_heartrate, int age)
{
    struct HeartrateRange *output = (struct HeartrateRange*)malloc(sizeof(struct HeartrateRange));
    output->high = .75 * calc_max_heartrate(age);
    output->low = .55 * calc_max_heartrate(age);
    return output;
}


