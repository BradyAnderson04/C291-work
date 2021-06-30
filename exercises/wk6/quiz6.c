// Quiz6.c 
// median of a sequence
/*
TODO:
The median m of a sequence of n elements is the element that would fall in the middle if the sequence was sorted. 
That is, e <= m for half the elements, and m <= e for the others. Clearly, one can obtain the median by sorting 
the sequence, but one can do quite a bit better with the following algorithm that finds the kth element of a
sequence between a (inclusive) and b (exclusive). (For the median, use k = n / 2, a = 0, and b = n.)
	select(k, a, b):
	Pick a pivot p in the subsequence between a and b.
	Partition the subsequence elements into three subsequences: the elements <p, =p, >p
	Let n1, n2, n3 be the sizes of each of these subsequences.
	if k < n1
		return select(k, 0, n1).
	else if (k > n1 + n2)
		return select(k, n1 + n2, n).
	else
		return p.

Implement this algorithm and measure how much faster it is for computing the median of a random large sequence, 
when compared to sorting the sequence and taking the middle element. Present your observations.

My run time:
Execution time:   0.000001 seconds
The Kth element is 49 for set size 99
Execution time:   0.000002 seconds
The Kth element is 499 for set size 999
Execution time:   0.000007 seconds
The Kth element is 5000 for set size 9999

every time the size of n increases by 10x while the time does not increase at a linear rate. 


If I were to implement a sorting algorithm and then get the median element, the sorting at best would be above a linear rate which means
the implementation used for this algorithm is much faster. Using Big O for my analysis, the speed of this algorithm scales sub-linear where 
as the alternative appraoch of sorting then indexing is above a linear growth rate, using merge sort it would be n * log(n) 

Merge sort method:
200 -> 3000 -> 40000 w/o units

Method implemented in this file:
.000001 -> .000002 -> 000007 in seconds

I don't know how to define a specific quantity of how much faster it is, but it is signifigantly faster with larger quantities

One way to "measure" the time or compare the performance would be to use any of the techniques mentione at 
https://fresh2refresh.com/c-programming/c-time-related-functions/
You may use any approach that you are comfortable with.

*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 21

// pick a k

int sel(int k, int a, int b);

int main(void)
{
	srand(time(NULL)); // seed the rand function 

	int i = 100;

	for(i = 100; i < 100000; i *= 10){
		// pick a k
		int k = i / 2;

		// run select
		int element_k = sel(k, 0, i);

		printf("The Kth element is %d for set size %d\n", element_k, i-1);
	}
	return 0;
}


int sel(int k, int a, int b)
{
	// adding in timing
	clock_t begin = clock();
	// create the array 
	int p = rand() % (b-a);
	int n1=0, n2=0, n3=0;
	int i;
	for(i=a; i<b-a; i++){
		// calc size of partitions
		if(i <p){
			n1++;
		} else if(i == p){
			n2++;
		} else {
			n3++;
		}
	}

	// id when kth element is found
	if(k < n1){
		return sel(k, a, n1);
	} else if(k > n1+n2){
		return sel(k, n1+n2, b);
	} else {
		// k element found
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Execution time: %10f seconds\n", time_spent);
		return p;
	}
}
