/*
    Author: Brady Anderson
    Date: 02/19/2021

    Program: 

    Create a program that plays the birthday game and perform many iterations of the program 
    to analyze the results of the experiment.

    The birthday game is a game where where you find the probability that at least 2 people in a room with n 
    people have birthdays that fall on the same day of the year. Assume that there is 365 days
    and assume that prob of being born on a day is the same for every day. rand from 1-365

    

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// experimental design vars
#define n 101
#define sample_size 10000

// function prototypes
double create_birthday_simulation(int people, int trials);
double test(int people, int trials);


int main(void){

    // useful constants
    time_t t;
    int i;
    double n_stats[98];

    // init random number generator
    srand((unsigned) time(&t));

    // full test case
    for(i=2; i<n;i++){
        // announce experiment
        printf("Performing birthday game on %d people for %d trials\n", i, sample_size);

        // conduct experiment
        double result = create_birthday_simulation(i, sample_size);

        // announce results and save data
        printf("%d people for %d trials\n", i, sample_size);
        printf("%.4f percent of trials resulted in a case where at least 2 people shared a birthday.\n\n",(double) (100 *result));
        n_stats[i-2] = result;
    }

    /*
    Answers to questions:
    1.What value of n yields the break even point?

    for my testing, the value of n that yields the break even point is typically 23 or 24 depending on some the time I run the code. This is 
    due to me using srand which is implemented with t as a random hashing input allowing for "psuedo-random" values to be created.

    Additionally, I quite like the structure of my program, but would love feedback in the comments for the assignment on parts that are confusing or hard to read.
    */
}

double create_birthday_simulation(int people, int trials)
{
    /*
    Given number of people and a number of trials perform n trials on x people

    this would be the birthday simulation described in the file program description

    due to many trials I believe this defines a montecarlo simulation
    */

    int result = 0;
    int z;
    // perform all the trials
    for(z=0; z<trials; z++){
        // trial local vars
        bool isTrialOver=false;
        int i, j;
        int birthdays[people];

        // generate data to perform the simulation
        for(i=0; i<people; i++){
            birthdays[i] = rand()%365+1;
        }

        // analyze results of the simulation to determin if true or not -- this is the trial logic
        for(i=0;i<people;i++){
            // no need to check previous values since those have already been checked -- only need to do work that is not computed yet
            for(j=i+1; j<people; j++){

                // different person same birthday -- true result
                if(birthdays[i] == birthdays[j]){
                    result+=1;
                    // test over
                    isTrialOver = true;
                    break;
                }

            }
            if(isTrialOver){
                // printf("Trial is over\n");
                break;
            }
        }
    }
    // return simulated probability
    // printf("true results: %d\n", result);
    // printf("simulated prob: %f\n", output);
    double output = (double)result/trials;
    return output;
}

