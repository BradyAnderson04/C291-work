/* 
Print a table of values for some boolean functions. 


fct1 = b1 || b2 || b3 || b4

fct2 = !(!b1 || b2) && (!b3 || b4)

fct3 = b1 && b2 && b3 && b4

fct4 = (b1 && b2) || (b3 && !b4)
*/

#include <stdio.h>

int main(void){   
    /* boolean variables */  
    int b1, b2, b3, b4; 
    int cnt = 0;
    
    /* headings */
    printf("\n%5s%5s%5s%5s%5s%5s%7s%7s%11s\n\n", "Cnt", "b1", "b2", "b3", "b4", "fct1", "fct2", "fct3", "fct4");
    
    for (b1 = 0; b1 <= 1; ++b1)      
        for (b2 = 0; b2 <= 1; ++b2)         
            for (b3 = 0; b3 <= 1; ++b3)            
                for (b4 = 0; b4 <= 1; ++b4)                               
                    printf("%5d%5d%5d%5d%5d%5d%6d%7d%11d\n", ++cnt, b1, b2, b3, b4, b1 || b2 || b3 || b4, !(!b1 || b2) && (!b3 || b4), b1 && b2 && b3 && b4, (b1 && b2) || (b3 && !b4));   
    putchar('\n');
    return 0;
}