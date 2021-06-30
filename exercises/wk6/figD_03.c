// Fig. E.3: figE_03.c
// The merge sort algorithm using recursion.

// TODO: sortSubArray function uses recursion. Write a new function called sortSubArrayIter which doesn't use recursion
// To implement the new sort function without recursion, where the length of the array is an arbitrary number, 
// Keep merging adjacent regions whose size is a power of 2, and pay special attention to the last area whose size is less.
// Test to make sure that your results are correct.
 
#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function prototypes 
void mergeSort(int array[], size_t length);
void mergeSortIter(int arr[], int n);

void sortSubArray(int array[], size_t low, size_t high);

void merge(int array[], size_t left, size_t middle1, size_t middle2, size_t right);
void mergeIter(int array[], int low, int mid, int end);

void displayElements(int array[], size_t length);
void displaySubArray(int array[], size_t left, size_t right);

int min(int x, int y);

int main(void)
{
   int array[SIZE], temp[SIZE]; // declare the array of ints to be sorted 
    
   srand(time(NULL)); // seed the rand function 
    
   size_t i;
   for (i = 0; i < SIZE; i++) {
      array[i] = rand() % 90 + 10; // give each element a value 
   }
        
   puts("Unsorted array:");
   displayElements(array, SIZE); // print the array 
   puts("\n");
   // mergeSort(array, SIZE); // merge sort the array 
   mergeSortIter(array, SIZE);
   puts("Sorted array:");
   displayElements(array, SIZE); // print the array 
} 

// function that merge sorts the array 
void mergeSort(int array[], size_t length)
{
   sortSubArray(array, 0, length - 1);
} 

void mergeSortIter(int arr[], int length)
{
   int sub;
   int start;
 
   // create subarrays of various sizes
   for (sub=1; sub<=length-1; sub = 2*sub)
   {
       // start at index 0 and move on 
       for (start=0; start<length-1; start += 2*sub)
       {
           // Find ending point of left subarray. mid+1 is starting 
           // point of right
           int mid = min(start + sub - 1, length-1);
 
           int end = min(start + 2*sub - 1, length-1);
 
           // merge subarray created
           mergeIter(arr, start, mid, end);
       }
   }
}

// function that sorts a piece of the array 
void sortSubArray(int array[], size_t low, size_t high)
{
   // test base case: size of array is 1 
   if ((high - low) >= 1) { // if not base case... 
      size_t middle1 = (low + high) / 2;
      size_t middle2 = middle1 + 1;
        
      // output split step 
      printf("%s", "split:   ");
      displaySubArray(array, low, high);
      printf("%s", "\n         ");
      displaySubArray(array, low, middle1);
      printf("%s", "\n         ");
      displaySubArray(array, middle2, high);
      puts("\n");
        
      // split array in half and sort each half recursively 
      sortSubArray(array, low, middle1); // first half 
      sortSubArray(array, middle2, high); // second half 
        
      // merge the two sorted arrays 
      merge(array, low, middle1, middle2, high);
   } 
}

// function that sorts sub arrays iteratively
void mergeIter(int array[], int low, int mid, int end)
{
    int i, j, k;
    int l_size = mid - low + 1;
    int r_size =  end - mid;
 
    /* create temp arrays */
    int left[l_size], right[r_size];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < l_size; i++)
        left[i] = array[low + i];
    for (j = 0; j < r_size; j++)
        right[j] = array[mid + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = low;
    while (i < l_size && j < r_size)
    {
        if (left[i] <= right[j])
        {
            array[k] = left[i];
            i++;
        }
        else
        {
            array[k] = right[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < l_size)
    {
        array[k] = left[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < r_size)
    {
        array[k] = right[j];
        j++;
        k++;
    }
}

// merge two sorted subarrays into one sorted subarray 
void merge(int array[], size_t left, size_t middle1, size_t middle2, size_t right)
{
   size_t leftIndex = left; // index into left subarray 
   size_t rightIndex = middle2; // index into right subarray 
   size_t combinedIndex = left; // index into temporary array 
   int tempArray[SIZE]; // temporary array 
    
   // output two subarrays before merging 
   printf("%s", "merge:   ");
   displaySubArray(array, left, middle1);
   printf("%s", "\n         ");
   displaySubArray(array, middle2, right);
   puts("");
    
   // merge the subarrays until the end of one is reached 
   while (leftIndex <= middle1 && rightIndex <= right) {
      // place the smaller of the two current elements in result 
      // and move to the next space in the subarray 
      if (array[leftIndex] <= array[rightIndex]) {
         tempArray[combinedIndex++] = array[leftIndex++];
      } 
      else {
         tempArray[combinedIndex++] = array[rightIndex++];
      } 
   }
    
   if (leftIndex == middle2) { // if at end of left subarray ... 
      while (rightIndex <= right) { // copy the right subarray 
         tempArray[combinedIndex++] = array[rightIndex++];
      } 
   } 
   else { // if at end of right subarray... 
      while (leftIndex <= middle1) { // copy the left subarray 
         tempArray[combinedIndex++] = array[leftIndex++];
      } 
   } 
    
   // copy values back into original array 
   size_t i;
   for (i = left; i <= right; i++) {
      array[i] = tempArray[i];
   } 
    
   // output merged subarray 
   printf("%s", "         ");
   displaySubArray(array, left, right);
   puts("\n");
} 

// display elements in array 
void displayElements(int array[], size_t length)
{
   displaySubArray(array, 0, length - 1);
} 

// display certain elements in array 
void displaySubArray(int array[], size_t left, size_t right)
{
   size_t i;
   // output spaces for alignment 
   for (i = 0; i < left; i++) {
      printf("%s", "   ");
   } 
    
   // output elements left in array 
   for (i = left; i <= right; i++) {
      printf(" %d", array[i]);
   } 
} 

int min(int x, int y){
   return x<y ?x:y;
}
