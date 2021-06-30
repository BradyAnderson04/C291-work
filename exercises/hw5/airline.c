/*

Author: Brady Anderson

Date Updated: February 26, 2021

Program Description:
    Create an airline boarding system for passengers to select seats
    
    The program is described by psuedocode.txt document going into algorithm specifics

*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <math.h>

// make program easy to work with using vars to define airplane size
#define AIRPLANE_ROW 7
#define AIRPLANE_COLUMNS 20

// function prototypes
void display_seating(int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS]);
void display_menu();
void init_plane_seating(int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS], char passenger_class[140][1]);
void display_manifest(char passenger_list[AIRPLANE_ROW * AIRPLANE_COLUMNS][40], char passenger_class[AIRPLANE_ROW * AIRPLANE_COLUMNS][1]);
void choose_seat(char level, char name[40], int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS], char passenger_list[AIRPLANE_ROW * AIRPLANE_COLUMNS][40], char passenger_class[AIRPLANE_ROW * AIRPLANE_COLUMNS][1]);
void display_boardingpass(int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS], char level, char name[40]);

int main(){
    // program vars
    int choice = 3;
    int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS];
    // store passenger name and class -- will be sequential and not sorted due to high dimentionality
    char passenger_list[AIRPLANE_ROW * AIRPLANE_COLUMNS][40];
    char passenger_class[AIRPLANE_ROW * AIRPLANE_COLUMNS][1];

    init_plane_seating(seat_status, passenger_class);

    while(true){
        // start flow
        display_menu();
        scanf("%d", &choice);

        if(choice == 5)
        {
            break; // quit
        }
        else if(choice == 4)
        {
            display_manifest(passenger_list, passenger_class); // print the passengers present in tabular format
        }
        else if(choice == 3)
        {
            display_seating(seat_status); // displaying the seats and where they are occupied
        }
        else 
        {
            // either 1 or 2 - intialize vars needed for both
            char name[40] = "";
            char level = 'E';

            printf("What is your name?");
            scanf(" %s", name);

            printf("What class do you want First, Business, or Economy? (enter F, B, or E)\n");
            scanf(" %c", &level);

            if(choice == 1){
                choose_seat(level, name, seat_status, passenger_list, passenger_class); // pick a seat any available seat
            }

            if(choice == 2){
                display_boardingpass(seat_status, level, name); // display the appropiate boarding pass info
            }
        }
    }
}


// function definitions
void display_seating(int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS])
{
    // print all seats in seating chart
    int i, j;
    for(i = 0; i < AIRPLANE_ROW; i++){
        for(j = 0; j < AIRPLANE_COLUMNS; j++){
            if(i == floor(AIRPLANE_ROW / 2) && j == 0){
                // create space for the walking row
                printf("\n");
            }
            printf("%3d", seat_status[i][j]);
        }
        printf("\n");
    }
}

void display_menu()
{
    printf("1.Choose a seat\n2.Print Boarding Pass\n3.Display Seating Chart\n4.Print Manifest\n5.Quit\n\n");
}

void init_plane_seating(int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS], char passenger_class[140][1])
{
    // initialize all values of seat_status
    int i, j;
    for(i = 0; i < AIRPLANE_ROW; i++){
        for(j = 0; j < AIRPLANE_COLUMNS; j++){
            int index = (i * 20) + j;
            // init value to e for empty and passenger class to n
            seat_status[i][j] = 0;
            passenger_class[index][0] = 'n';
        }
    }
}

void display_manifest(char passenger_list[AIRPLANE_ROW * AIRPLANE_COLUMNS][40], char passenger_class[AIRPLANE_ROW * AIRPLANE_COLUMNS][1])
{
    // print seats in tabular format
    int i, j;
    printf("Manifest for all plane passengers. Only occupied seats are displayed.\n");
    for(i = 0; i < AIRPLANE_ROW; i++){
        for(j = 0; j < AIRPLANE_COLUMNS; j++){
            int index = i * 20 + j;
            if(passenger_class[index][0] != 'n'){
                printf("Passenger:%s, Seat: %c%d, Level:%c\n", passenger_list[index], (char)i+65, j, passenger_class[index][0]);
            }
        }
    }
    printf("\n");
}

void choose_seat(char level, char name[40], int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS], char passenger_list[AIRPLANE_ROW * AIRPLANE_COLUMNS][40], char passenger_class[AIRPLANE_ROW * AIRPLANE_COLUMNS][1])
{
    // repeat process at max 3 times -- ask user if they would like a randomly decided seat
    int i;
    for(i = 0; i < 3; i++){
        int random_row = 0;
        int random_column = 0;
        bool available = 0;
        char chooseSeat = 0;
        char upgrade_seat = 0;
        char downgrade_seat = 0;
        char window_preference = 0;
        char aisle_preference = 0;
        
        // initial seat selection
        while(!available)
        {
            srand(time(0));
            // based off the class they want assign a row
            if(level == 'F')
            {
                int random_row = (rand() % (3 - 1));
            } 
            else if(level == 'B')
            {
                int random_row = (rand() % (AIRPLANE_ROW - 3)) + 3;
            } 
            else if(level == 'E')
            {
                int random_row = (rand() % (AIRPLANE_COLUMNS - 8 + 1)) + 7;
            }
            
            // window seat desired -- initial seat selection flow
            printf("Would you like a window seat? (y/n)\n");
            scanf(" %c", &window_preference);

            // aisle seat desired?
            if(window_preference == 'n' || window_preference == 'N')
            {
                printf("Would you like a aisle seat? (y/n)\n");
                scanf(" %c", &aisle_preference);
            } 
            else
            {
                int i = (int) 'I' - 65;
                int a = (int) 'A' - 65;
                if(seat_status[i][random_row] == 0){
                    random_column = i;
                } else if (seat_status[a][random_row] == 0){
                    random_column = a;
                }
            }

            // assign which column based off of preference for aisle/window cont.
            if(window_preference == 'n' && aisle_preference == 'y')
            {
                // assessing c or d
                int e = (int) 'E' - 65;
                int d = (int) 'D' - 65;
                if(seat_status[e][random_row] == 0)
                {
                    random_column = e;
                } 
                else if (seat_status[d][random_row] == 0)
                {
                    random_column = d;
                }
            } 
            else if(window_preference == 'n' && aisle_preference == 'n')
            {
                // assign a random column ( get a value randomly between 65 and 70)
                srand(time(0));
                random_column = (rand() % (72 - 65 + 1));
            }

            // check if available
            if(seat_status[random_row][random_column] == 0){
                // if it is avaible then note as available then break out of current loop
                available = true;
                break;
            }

        }

        // now ask user if they would like to upgrade or downgrade -- changing og selection
        printf("Do you want to upgrade your seat? (y/n)\n");
        scanf(" %c", &upgrade_seat);

        if(upgrade_seat == 'y' || upgrade_seat == 'Y'){
            // temp vars
            char temp_level;
            int temp_rr;

            // try to find a new one 3 times
            int i;
            for(i = 0; i < 3; i++){
                // genereate new row until you find an availble one and change it to that
                if(level == 'B'){
                    temp_rr = (rand() % (3 - 1 + 1)) + 1;
                    temp_level = 'F';
                } else if(level == 'E'){
                    // place in row from 8-20
                    temp_rr = (rand() % (AIRPLANE_ROW - 4 + 1)) + 4;
                    temp_level = 'B';
                }
                // notify user where the new seat is if availble or get a new row in range
                if(seat_status[random_column][random_row] == 0)
                {
                    level = temp_level;
                    random_row = temp_rr;
                    break;
                }
                if(i == 3)
                {
                    printf("Unable to upgrade your seat. You are still seated at %c%d", random_row, random_column);
                }
            }
        }

        if(upgrade_seat != 'y' || upgrade_seat != 'Y')
        {
            printf("Do you want to downgrade your seat? (y/n)\n");
            scanf(" %c", &downgrade_seat);
        }
        // same logic for downgrade
        if(downgrade_seat == 'y' || downgrade_seat == 'Y'){
            // temp vars
            char temp_level;
            int temp_rr;
            // try to find a new one 3 times
	    int i;
            for(i = 0; i < 3; i++){
                // genereate new row until you find an availble one and change it to that 
                if(level == 'F'){
                    // place in row from 3-7
                    temp_rr = (rand() % (AIRPLANE_ROW - 4 + 1)) + 4;
                    temp_level = 'B';
                } else if(level == 'B'){
                    // place in row from 8-20
                    temp_rr = (rand() % (AIRPLANE_COLUMNS - 8 + 1)) + 8;
                    temp_level = 'E';
                }
                // notify user where the new seat is if availble or get a new row in range
                if(seat_status[random_column][random_row] != 'e'){
                    level = temp_level;
                    random_row = temp_rr;
                    break;
                }
                // event 
                if(i == 3)
                {
                    printf("Unable to downgrade your seat. You are still seated at %c%d", random_column, random_row);
                }

            }
        }

        printf("Do you want the seat at %c%d? (y/n)\n", random_row+65, random_column);
        scanf(" %c", &chooseSeat);

        int count = 0, i;

        // check how many passengers already in the system
        for(i=0;i<140;i++){
            if(passenger_class[i][0] == 't'){
                count++;
            } else {
                break;
            }
        }

        if(chooseSeat == 'y' || chooseSeat == 'Y'){
            // mark as taken
            seat_status[random_row][random_column] = 1;
            // store passenger name
            strcpy(passenger_list[count], name);
            // store passenger seat
            passenger_class[count][0] = level;
            // leave the loop
            break;
        }

        if(i == 3){
            printf("Next plane leaves in 3 hours.\n");
        }

    }
}

void display_boardingpass(int seat_status[AIRPLANE_ROW][AIRPLANE_COLUMNS], char level, char name[40])
{
    // initialize data needed
    int seat = AIRPLANE_COLUMNS;
    char row = 'C';
    char verbose_level[25];
    // populate from user
    printf("What is your seat column (0-19)?\n");
    scanf(" %d", &seat);

    printf("What is your seat row(A,B,D,E,F,H,I)?\n");
    scanf(" %c", &row);

    // find the seat as asssigned
    if(seat_status[(int)row-65][seat] == 0){
        printf("Seat unassigned no boarding pass available. Try Again!\n");
    } 
    else if((row == 'A' || row == 'a') && seat_status[(int)row-64][seat] == 1 )
    {
        // seat is a so only check b value
        printf("Seat blocked due to covid-19. \n");
    }
    else if((row == 'I' || row == 'i') && seat_status[(int)row-66][seat] == 1)
    {
        // seat is I so only check prev value
        printf("Seat blocked due to covid-19. \n");
    }
    else if(seat_status[(int)row-64][seat] == 1 || seat_status[(int)row-66][seat] == 1)
    {
        // event where the value is not A or I for seating row -- will be an error when it is supposed to be c
        printf("Seat blocked due to covid-19. \n");
    }
    else 
    {
        if(level == 'F'){
            strcpy(verbose_level, "First Class");
        } else if(level == 'B'){
            strcpy(verbose_level, "Business Class");
        } else {
            strcpy(verbose_level, "Economy Class");
        }
        printf("%s , SEAT: %c%d, Level: %s \n", name, row, seat, verbose_level);
    }
}
