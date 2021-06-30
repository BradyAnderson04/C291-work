/*
Brady Anderson
02/12/2021

Code for HW3-part 3 payroll calculator

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "constants.h"

// constants -- externally kept
extern double fed_withholding;
extern double state_withholding;
extern double retirement_contrib;

// function prototype
double print_statement(int num_of_employees);

int main(void){

    time_t t;

    // init random number generator
    srand((unsigned) time(&t));

    printf("Net profit: $%.2f\n", print_statement(8));

    return 0;
}

// function definitions
double print_statement(int num_of_employees){

    double sales[num_of_employees];
    double years[num_of_employees];
    double sales_total = 0;

    double tc, tb, tfw, tsw, trt, tnp;

    int i;

    // generate random sales and random years
    for(i = 0; i < num_of_employees; i++){
        sales[i] = (rand() % 9000) + 1000;
        years[i] = (rand() % 30) + 1;

        sales_total += sales[i];
    }

    // print out the table
    printf("Monthly Sales: $%.2f\n", sales_total);
    printf("Monthly Profit: $%.2f\n", sales_total * .45);
    printf("==================================================================================================\n");
    printf("Name\tCommission\tBonus\t\tFed W.\t\tSt W.\t\tRT\t\tNet Pay\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    for(i =0;i<num_of_employees;i++){
        double ic, ib, ifw, isw, irt, inp;

        // calculate invidual values
        ic = .125 * sales[i];
        ib = (floor(years[i] / 10) * .05 + .1) * sales[i];
        ifw = fed_withholding * sales[i];
        isw = state_withholding * sales[i];
        irt = retirement_contrib * sales[i];
        inp = ic + ib - ifw - isw + irt;

        // update total values
        tc += ic;
        tb += ib;
        tfw += ifw;
        tsw += isw;
        trt += irt;
        tnp += inp;

        // display values inline -- use string formatting 
        printf("Emp: %d\t%10.2f\t%5.2f\t\t%6.2f\t\t%5.2f\t\t%6.2f\t\t%7.2f\n", i,ic, ib, ifw, isw, irt, inp);

    }
    double profit = ((sales_total * .45) - tb);

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("Total:  %10.2f\t%5.2f\t\t%6.2f\t\t%5.2f\t\t%6.2f\t\t%7.2f\n", tc, tb, tfw, tsw, trt, tnp);
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("Net Profit(Profit - Bonus): %.2f\n", profit);
    printf("Brady Anderson, The Best Branch Manager?\n");



    return profit;



}