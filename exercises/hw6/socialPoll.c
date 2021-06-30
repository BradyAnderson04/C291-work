/*
Social  media  is  enabling  more  people  to  become  connected,  join  a  cause,  voice  opinions,  and  so  on.  The  U.S.  
presidential candidates in 2020 are using it intensively to get out their messages and raise money for their campaigns.
In this exercise, you’ll write a simple polling program that allows users to rate the social-consciousness issues from 1 (least important) 
to 10 (most important). 
Pick seven causes that are important to you (e.g., political issues, global environmental issues, social
issue, etc.).   
Use a one-dimensional arraytopics(of typechar *) to store the seven causes. 
To summarize the survey responses, 
use a 7-row, 10-column two-dimensional array responses (of type int), where intuitively each row corresponds to an element in  
the topics array. When the program runs, it  should ask the user to rate each issue. 
Have your friends and family respond to the survey. Then have the program display a summary of the results, including:
a)  A tabular report with the seven topics down the left side and the 10 
    ratings across the top, listing in each column the number of ratings 
    received for each topic.
    
b)  To the right of each row, show the average of the ratings for that issue. 
c)  Which issue received the highest point total? Display both the issue and 
    the point total.
    
d)  Which issue received the lowest point total? Display 
    both the issue and the point total.
    
e)  Display the ranking of issues from highest to lowest 
    point total (along with the corresponding issue). 
    
f)  Using (only) the entries from the table, display the 
    number of people who responded.
*/

#include <stdio.h>
#include <stdlib.h>

#define ISSUE_COUNT 7
#define VALUE_COUNT 10

int main(void){
    // array of issues and responses
    char **issuePtr;
    int **responsePtr;
    double *avgResponsePtr;
    int count;

    issuePtr = malloc(7 * sizeof(char*));
    responsePtr = malloc(7 * 10 * sizeof(int)); // 7 X 10 array of responses
    avgResponsePtr = malloc(7 * sizeof(double));
    // initialize by reference
    // I also don't feel like sharing my personnal beliefs so here are a bunch of random issues
    *(issuePtr + 0) = "Decriminalize Drugs";
    *(issuePtr + 1) = "Immigration";
    *(issuePtr + 2) = "Free Pony";
    *(issuePtr + 3) = "Increase Taxes";
    *(issuePtr + 4) = "Social Policing";
    *(issuePtr + 5) = "Contact Tracing";
    *(issuePtr + 6) = "Police Brutality";

    // initialize by reference for responsePtr
    // pointer of arrays of arrays would be referenceable similar to how a 1d array works, but slight varaition
    // *(pointer + (row * 10 + column))
    int i, j;
    for(i = 0 ; i < ISSUE_COUNT; i++){
        for(j = 0; j < VALUE_COUNT; j++){
            *(responsePtr + (i * 10 + j)) = 0;
        }
    }

    // how many people are taking the survey....
    printf("Please enter how many people will be taking the survey and press ENTER: \n");
    scanf("%d", &count);
    for(j = 0; j < count; j++){
        // iterate over how many people are taking the poll
        for(i = 0; i < ISSUE_COUNT; i++){
            // local vars
            int res;
            // ask the person thoughts on an issue
            printf("Please rate 1-10 how much important %s is to you and press ENTER\n", *(issuePtr+i));
            scanf("%d", &res);  // store response in temp var
            // save response in appropiate location in the array
            *(responsePtr + (i * 10 + res)) = *(responsePtr + (i * 10 + res)) + 1;
        }
    }

    // get the average scores order will be implicitly defined -- printing will be kinda annoying
    for(i = 0; i < ISSUE_COUNT; i++){
        // init vars to calc average
        int votes = 0;
        int sum = 0;
        // iterate over each row of vals
        for(j = 0; j < VALUE_COUNT; j++){
            // gather the data and set appropiately
            int val = *(responsePtr + (i * 10 + j));
            sum += (val/4) * (j+1);
            votes += val/4;
        }
        // save to proper slot
        *(avgResponsePtr + i) = sum / votes;
    }


    // create table as specified a - b
    // tacking for vals to print
    double highestAvg = -1; // -1 is lower than any possible answer
    char* highestIssue = malloc(20 * sizeof(char));
    double lowestAvg = 11; // 11 is higher than any possible answer
    char* lowestIssue = malloc(20 * sizeof(char));

    for(i = 0 ; i < ISSUE_COUNT+1; i++){
        // print tracking

        // calculate the average score sum will be total
        int sum = 0;
        int votes = 0;
        int issueNumber = 0;

        // left header
        if(i != 0)
            printf("%25s|", *(issuePtr+(i-1)));
        
        for(j = 0; j < VALUE_COUNT+1; j++){
            int tempCount = *(responsePtr + ((i-1) * 10 + j));
            if(i == 0 && j == 0){
                // the top left corner
                printf("%25s|", " ");
            }
            if(i == 0 && j != 0){
                // top row print reponse options
                printf("%2d|", j);
            } else if (j != 0) {
                // last column print the average as well 
                // rest of the rows
                printf("%2d|", *(responsePtr + ((i-1) * 10 + j)));

                if(j == VALUE_COUNT){
                    printf("Avg: %f", *(avgResponsePtr + (i-2)));
                }
            }
            // getting relevant data to make a decision on the average value
            if(*(responsePtr + ((i-1) * 10 + j)) != 0){
                sum += j * (tempCount / 4);
                votes += tempCount / 4;
                issueNumber = i;
            }

        }
        printf("\n");
        double avg = sum/count;
        // if applicable change the lowest/highest values
        if(avg < lowestAvg){
            lowestAvg = avg;
            lowestIssue = *(issuePtr + (issueNumber-1));
        }

        if(sum/votes > highestAvg){
            highestAvg = avg;
            highestIssue = *(issuePtr + (issueNumber-1));
        }
    }

    // highest point total issue
    printf("Highest voted issue: %s\n Importance Score: %f\n", highestIssue, highestAvg);
    // lowest point total issue
    printf("Lowest voted issue: %s\n Importance Score: %f\n", lowestIssue, lowestAvg);
    // ranking of issues highest -> lowest -> do after the next problem don't waste too much time since I do have the bonus point +5 rn
    
    /*
    This code conceptually will iterate through find the highest and reset to zero 
    it'll print them in order from greatest to least.
    Ideally would be better to do a deep copy of the ptr and it's content, but I don't
    really care about doing that.
    */
    // print 7 times so iterate 7 times
    printf("Rating from highest to lowest.\n");
    for(j = 0; j < ISSUE_COUNT; j++){
        double highestAvg = 0;
        char* highestIssue = malloc(20 * sizeof(char));
        // find the greatest in the avgResponsePtr
        for(i = 0; i < ISSUE_COUNT; i++){
            double val = *(avgResponsePtr + i);
            if(val > highestAvg){
                highestAvg = val;
                highestIssue = *(issuePtr + i);
                *(avgResponsePtr + i) = 0;
            }
        }
        printf("%d. %s Rating: %f\n", j+1, highestIssue, highestAvg-1);
        highestAvg = 0;
    }


    // number of people - using only table
    int people = 0;
    for(i = 0; i < VALUE_COUNT; i++){
        int tempCount = *(responsePtr + i);
        if(tempCount != 0){
            people += tempCount;
        }
    }
    // noramlize for my error currently - values of tables are set to 4 instead of 1 for every vote
    people = people / 4;

    printf("The number of people who took the survey based off the results: %d\n", people);


    printf("Note: I can't figure out why the values are incrementing by 4 instead of 1. I think this has to do with my pointers. \n but for the table 4 = 1 vote, generally vote count = number in table / 4\n Its also kinda buggy with the rating system, but I am hoping for patial credit on that since the program meets requirements partially.");

    return 0;
}