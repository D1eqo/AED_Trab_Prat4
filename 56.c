#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int** a, int** b) { //swaps intervals
    int* temp = *a;
    *a = *b;
    *b = temp;
}

int split(int** intervals, int low, int high) { //takes the array of intervals and two indexes of intervals to specify a range in the array
    int* pivot = intervals[high]; //sets the pivot
    int i = (low - 1);//partition index

    for (int j = low; j <= high - 1; j++) {//covers the range within the array of arrays
        if (intervals[j][0] < pivot[0]) { //compares the 'x's
            i++;
            swap(&intervals[i], &intervals[j]); //compared to the pivot lesser values go to the left, consequentially greater values go to the right of the pivot
        }
    }
    swap(&intervals[i + 1], &intervals[high]);//place the pivot in its correct position
    return (i + 1);//return the correct index for the pivot in the range
}

void quickSort(int** intervals, int low, int high) { //this will be used to allow a linear approach to further merge the overlapping intervals instead of brute forcing it
    if (low < high) { //runs through the intervals
        int piv = split(intervals, low, high); //gets new pivot index
        quickSort(intervals, low, piv - 1);
        quickSort(intervals, piv + 1, high);
    }
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    if(intervalsSize <= 0){
        *returnSize = 0;
        return NULL;
    }
    
    quickSort(intervals, 0, intervalsSize - 1); //-1 because the index starts at 0
    
    int** res = (int**)malloc(sizeof(int*)*intervalsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int)*intervalsSize);
    res[0] = intervals[0]; //in the example it's [1,3]
    *returnColumnSizes[0] = intervalsColSize[0]; //it's always 2
    *returnSize = 1; //starts at one because we already have at least one interval
    
    for(int i = 1; i < intervalsSize; i++){ //i=1 is [2,6]
        if(intervals[i][0] <= res[*returnSize-1][1]){ //2 <= 3, overlap;
            res[*returnSize-1][1] = fmax(res[*returnSize-1][1], intervals[i][1]); //note that res[*returnSize-1][0] is always the smallest value
            (*returnColumnSizes)[*returnSize-1] = 2; //fmax will return the highest value between the two intervals and update y. Now we have [1,6]
        }else{
            res[*returnSize] = intervals[i]; //no overlap
            (*returnColumnSizes)[*returnSize] = 2; //always 2
            (*returnSize)++;
        }
    }
    
    return res;
}

int main() {
    // Example 1 from LeetCode: [[1,3],[2,6],[8,10],[15,18]]
    int intervalsSize = 4; //how many intervals are there?
    int* intervalsColSize = (int*)malloc(sizeof(int)*intervalsSize); //invervalsColSize is always equal to 2 for [x,y];
    for (int i = 0; i < intervalsSize; i++) { //for every interval note that it has size 2
        intervalsColSize[i] = 2;
    }
    
    int** intervals = (int**)malloc(sizeof(int*)*intervalsSize); //creates an array of pointers of size equal to intervalsSize
    for (int i = 0; i < intervalsSize; i++) { //loops for every pointer
        intervals[i] = (int*)malloc(sizeof(int)*2); //makes space for each to store 2 integers [x,y]
    }
    
    // Interval [1,3]
    intervals[0][0] = 1;
    intervals[0][1] = 3;

    // Interval [2,6]
    intervals[1][0] = 2;
    intervals[1][1] = 6;

    // Interval [8,10]
    intervals[2][0] = 8;
    intervals[2][1] = 10;

    // Interval [15,18]
    intervals[3][0] = 15;
    intervals[3][1] = 18;

    
    int returnSize; //new size of the array of arrays after merging
    int* returnColumnSizes;
    
    int** mergedIntervals = merge(intervals, intervalsSize, intervalsColSize, &returnSize, &returnColumnSizes);
    
   for (int i=0; i<returnSize; i++) {
       printf("[%d,%d]\n", mergedIntervals[i][0], mergedIntervals[i][1]);
   }

   //free stuff
   for (int i=0; i<intervalsSize; i++) {
       free(mergedIntervals[i]);
   }
   free(mergedIntervals);
   free(returnColumnSizes);

   return 0;
}
