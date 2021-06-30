/*
Author: Brady Anderson
Class: C291 Spring 2021
Date: 02/01/2021

This file is code for question 1 on hw2. below is the psuedocode : )


Additional instructions for grader:


*/


/*
Psuedocode


average work week = 40 hours for salary employees

print menu with paycodes and arguments required


while true
  if data still needed
    switch employee type

      case A
        monthly salary = data / 12

        hours = 40  * 4

      case S
        if overtime is less than 10
          monthly revenue = variable / 12 + overtime * .75 
        else
           monthly revenue = variable / 12 + 10 * .75

        hours = 40  * 4 + overtime

      case R
        monthly data provided / 10

        bonus = floor(credit hours taught / 3) * 8500

        hours = 40  * 4

      case J
        salary = floor(credit hours taugh / 3) * 8500 / 5

        hours = 40  * 4

      case T
        salary = courses helping with * 2500

        bonus = hours extra * hourly salary

        hours = 40  * 4

      case H
        if hours worked < 20
          salary = hours worked * wage
        else if hours worked < 40
          salary = (hours worked - 20) * wage + hours worked remaining * 1.5 * wage
        else
          salary = (hours worked - 20) * wage + 20 * 1.5 * wage
  else
    switch employee type

      case A
        printf monthly salary of administrator
        
        printf monthly salary / 4 (weekly salary)

        printf monthly salary / hours worked 

      case S
        printf monthly salary of administrator
        
        printf monthly salary / 4 (weekly salary)

        printf monthly salary / hours worked 

      case R
        printf monthly salary of administrator
        
        printf monthly salary / 4 (weekly salary)

        printf monthly salary / hours worked 

      case J
        printf monthly salary of administrator
        
        printf monthly salary / 4 (weekly salary)

        printf monthly salary / hours worked 

      case T
        printf monthly salary of administrator
        
        printf monthly salary / 4 (weekly salary)

        printf monthly salary / hours worked 

      case H
        printf monthly salary of administrator
        
        printf monthly salary / 4 (weekly salary)

        printf monthly salary / hours worked 

  if code == Q
    print avg weekly and monthly earnings for each type of employee
    print avg earning per hour by type
    quit the loop
*/

#include <stdio.h>
#include <math.h>

int main(void){
    
  // variable to store the salary of each type of employee
  double aSalary, sSalary, rSalary, jSalary, tSalary, hSalary;
  // total hours of each employee type
  double aHours, sHours, rHours, jHours, tHours, hHours;

  printf("Welcome to pay tracker for Indiana University:\n");
  // main loop
  while(1 == 1){
    // temp vars
    char code;
    double argOne, argTwo;

    // print menu
    if(aSalary == 0 || sSalary == 0 || rSalary == 0 || jSalary == 0 || tSalary == 0 || hSalary == 0){
      // prompt to gather data
      printf("Please enter one of the following pay codes with associated arguments provided\nPaycodes\tAdministrator: \t\tA salary(double) 0\n\t\tStaff: \t\t\tS salary(double) overtime(double)\n\t\tRegular faculty: \tR salary(double) creditHours(double)\n\t\tAdjunct: \t\tJ creditHours(double) 0\n\t\tTeaching Assistant: \tT classes(double) hoursWorkedOnBothCourses(double)\n\t\tHourly worker: \t\tH wage(double) hours(double)\n\t\tQuit menu: \t\tQ 0 0\n\n");
      printf("Please enter a paycode with appropiate arguments and press ENTER\n");
      scanf("%c %lf %lf", &code, &argOne, &argTwo);
      // need more data part -- save the data to correct place
      switch(code){
        case 'A':
          printf("Admin Yearly Salary: %lf\n", argOne);
          aSalary = argOne / 12;
          aHours = 160; // 40 hour work week * 4 weeks
          break;
        case 'S':
          printf("Staff Yearly Salary: %lf\nStaff overtime for this month: %lf", argOne, argTwo);
          if(argTwo <= 10){
            sSalary = (argOne / 12) + (argTwo * .75 * (argOne / (12 * 200)));
          } else {
            sSalary = (argOne / 12) + (10 * .75 * (argOne / (12 * 200)));
          }
          sHours = argTwo + 160; // monthly hours
          break;
        case 'R':
          printf("Regular Faculty Yearly Salary: %lf\nRegular Faculty credit hours: %lf", argOne, argTwo);
          rSalary = (argOne + (floor(argTwo / 3) * 8500))/10;
          rHours = 160; // 40 hour work week * 4 weeks 
          break;
        case 'J':
          printf("Adjunct teaching credits: %lf\n", argOne);
          // based off information provided - bonus is indistinguishable due to how they are paid
          jSalary = (floor(argOne / 3) * 8500 ) / 5;
          jHours = 160; // 40 hour work week * 4 weeks 
          break;
        case 'T':
          printf("Teaching assistant class count: %lf\nTA total hours on classes: %lf", argOne, argTwo);
          // base salary
          tSalary = argOne * 2500;
          // bonus
          if(argTwo <= 40){
            // max extra hours worked over course of 5 months is 40
            tSalary += argTwo * 12.5;
          } else {
            tSalary += 40 * 12.5;
          }
          // hours is 10 per week over 5 months + extra hours
          tHours = 40 + argTwo;
          tSalary /= 5; // get monthly value by dividing by pay cycle

          // avoid dobule running
          
          break;
        case 'H':
          printf("Hourly wage: %lf\n Hourly worker hours count: %lf", argOne, argTwo);
          if(argTwo < 20){
            hSalary = argOne * argTwo;
          } else if(argTwo <= 40){
            hSalary = (argOne * 20) + (1.5 * argOne * (argTwo - 20));
          } else {
            hSalary = (argOne * 20) + (1.5 * argOne *  20);
          }
          // total hours in the month
          hHours = argTwo * 4;
          break;
      }
    } 
    else {
      // same structure to print information on categories
      printf("Please enter one of the following pay codes to view salary information\nPaycodes\n\t\tAdministrator: \t\tA \n\t\tStaff: \t\t\tS \n\t\tRegular faculty: \tR \n\t\tAdjunct: \t\tJ \n\t\tTeaching Assistant: \tT \n\t\tHourly worker: \t\tH \n\t\tQuit menu: \t\tQ \n\n");
      printf("Please enter a paycode and press ENTER\n");
      scanf("%c", &code);
      switch(code){
        case 'A':
          printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", aSalary, aSalary/4, aSalary/(4*aHours));
          break;
        case 'S':
          printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", sSalary, sSalary/4, sSalary/(4*sHours));
          break;
        case 'R':
          printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", rSalary, rSalary/4, rSalary/(4*rHours));
          break;
        case 'J':
          printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", jSalary, jSalary/4, jSalary/(4*jHours));
          break;
        case 'T':
          printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", tSalary, tSalary/4, tSalary/(4*tHours));
          break;
        case 'H':
          printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", hSalary, hSalary/4, hSalary/(4*hHours));
          break;
      }
    }
    
    // event for when user presses Q
    if(code == 'Q'){
      if(aSalary != 0 && sSalary != 0){
        double avgSalary = (aSalary + sSalary) / 2;
        double avgHours = (aHours + sHours) / 2;
        printf("Payment data for Administrators and staff:\n");
        printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", avgSalary, avgSalary/4, avgSalary/(4*avgHours));
      } else {
        printf("Insufficient data for the Administrators and Staff group.\n\n");
      }

      if(rSalary != 0 && jSalary != 0 && tSalary != 0){
        double avgSalary = (rSalary + jSalary + tSalary) / 3;
        double avgHours = (rHours + jHours + tHours) / 3;
        printf("Payment data for Faculty:\n");
        printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", avgSalary, avgSalary/4, avgSalary/(4*avgHours));
      } else {
        printf("Insufficient data for the Faculty group.\n\n");
      }

      if(hSalary != 0){
        printf("Payment data for Hourly Workers:\n");
        printf("Monthly salary: %lf\nWeekly salary: %lf\nHourly salary: %lf\n\n", hSalary, hSalary/4, hSalary/(4*hHours));
      } else {
        printf("Insufficient data for the Hourly worker group.\n");
      }
      break;
    }

  }


  return(0);
}
