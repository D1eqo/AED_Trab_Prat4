/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    // Get the values of the first interval
    int *s[][]=0, *g[][]=0; 
    int *r[][] = (int*)malloc(sizeof(returnSize));
    for(int i=0; i<intervalsSize; i++){
    // Gets the first interval and stores it, then compares it until one of the conditions below are met
        for(int j=0; j<2; j++){ //it will go interval by interval            
            // [xi,yi]; if x1<x2 && x2<y1 set x1 as new smallest. if y2>y1 && x2<y1 set y2 as new greatest.
            // The new intervals will be stored in a new array r.
        }
    }
    //r[returnSize][returnColumnSizes];
}
