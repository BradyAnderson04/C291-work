// Fig. 5.16: fig05_16.c
// Scoping.

//Todo: Modify the code to print memory addresses of all variables/array elements and
//explain the impact of "static" keyword. Also use an extern variable and discuss how
//it impacts the memory address. Why?

/*
Answer:
1.explain the impact of "static" keyword

The static keyword is using static memory. As you notice when the file runs the value of static keeps what happens between function calls impacting
the value at the memory address. additionally the memory for the static variable doesn't change therefore we can assume static uses the actual memory location to store changes. 
comparing this to the local var that doesn't change memory location, and doesn't have the value at the memory location changed.

2.Also use an extern variable and discuss how it impacts the memory address. Why?

Th eextern variable memory address doesn't change which is being used however when using extern, based off how the function runs, 
the value stored at the memory address is changed. IE: similar to a value that is passed by reference. The reason for this is because we 
are referencing a value outside of the file but has a connection to the value's memory address via the extern keyword

*/

#include <stdio.h>

#include "fig05_16_helper.h"

void useLocal(void); // function prototype
void useStaticLocal(void); // function prototype
void useGlobal(void); // function prototype
void useExtern(void); // function prototype

int x = 1; // global variable
extern int y; // extern var

int main(void)
{
   int x = 5; // local variable to main

   printf("local x in outer scope of main is %d\n", x);

   { // start new scope                                     
      int x = 7; // local variable to new scope               
                                                                  
      printf("local x in inner scope of main is %d\n", x);     
   } // end new scope                                          

   printf("local x in outer scope of main is %d\n", x);

   useLocal(); // useLocal has automatic local x
   useStaticLocal(); // useStaticLocal has static local x
   useGlobal(); // useGlobal uses global x
   useExtern(); // useExtern uses extern y
   useLocal(); // useLocal reinitializes automatic local x
   useStaticLocal(); // static local x retains its prior value
   useGlobal(); // global x also retains its value
   useExtern(); // useExtern uses extern y

   printf("\nlocal x in main is %d\n", x);
} 

// useLocal reinitializes local variable x during each call
void useLocal(void)
{
   int x = 25; // initialized each time useLocal is called

   printf("\nlocal x in useLocal is %d after entering useLocal\n", x);
   ++x;
   printf("local x in useLocal is %d before exiting useLocal\n", x);
   printf("The memory address of this x is %p\n", &x);
} 

// useStaticLocal initializes static local variable x only the first time 
// the function is called; value of x is saved between calls to this
// function
void useStaticLocal(void)
{
   // initialized once 
   static int x = 50;                        

   printf("\nlocal static x is %d on entering useStaticLocal\n", x);
   ++x;
   printf("local static x is %d on exiting useStaticLocal\n", x);
   printf("The memory address of this x is %p\n", &x);
}

// function useGlobal modifies global variable x during each call
void useGlobal(void)
{
   printf("\nglobal x is %d on entering useGlobal\n", x);
   x *= 10;
   printf("global x is %d on exiting useGlobal\n", x);
   printf("The memory address of this x is %p\n", &x);
}

void useExtern(void)
{
   printf("\nextern y is %d on entering useExtern\n", y);
   y *= 10;
   printf("extern y is %d on exiting useExtern\n", y);
   printf("The memory address of this x is %p\n", &y);
}
