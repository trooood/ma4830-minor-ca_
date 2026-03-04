#include <stdio.h>
#include <stdlib.h>  // for ascii string to long (strtol)
#include <math.h>    // for NANs

int main(int argc, char *argv[]) {

    // --- handle the inputs ---
    int n;
    char filename[256];
    FILE *fp = NULL;
    const int max_attempts=3;
    int attempts=0;

    while (fp == NULL) {
        printf("Enter filename: ");
        if (scanf("%255s", filename) != 1) {
            printf("Error: Invalid filename input.\n");
            return 1;
        }

        fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Cannot open file: No such file or directory.\n");
            attempts++;
            if (attempts >= max_attempts) {  // exit after max tries
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
        }

        
    }

    // --- handling the data stuff ---

    // init stuff to save the data in
    char buffer[256];  // for storing stuff per line
    float data[1024];  // for storing data floats
    int count = 0;  // counts no. of data

    /*
    // cannot open file
    fp = fopen(filename, "r");
    if (fp == NULL) {  // file does not exist
        printf("Cannot open file: No such file or directory.\n");
        exit(1);
    }
    */

    //else {  // can get file
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {  // read 1 line
        printf("%s", buffer);

        char *ptr = buffer;  // points to start of buffer

        while (*ptr != '\0') {
            while (*ptr == ' ' || *ptr == '\n') ptr++;  // skip space and newline
            // handle bad data here
            if (*ptr == '\0') break;  // stop if end of string

            char *endptr;
            float val = strtof(ptr, &endptr);  // start reading at ptr and end save end at &endptr
            if (ptr == endptr) break;  // there is no values in between start and end pointers
            
            data[count++] = val;  // move to the next element
            ptr = endptr;  // move pointer to where it was last buffered until

        }
    }
    
    fclose(fp);  // close file

    printf("\n");
    // no data in file
    if (count==0) {
        printf("Error: File is empty or contains no valid float data.\n");
        exit(1);
    }

    //printf("\n");
    //printf("number of datapoints = %d\n", count);
    // enter n
    printf("Enter window size n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("First input must be a valid positive integer.\n");
        return 1;
    }

    // check that n <= count
    if (n > count) {
        printf("Error: n must be smaller than number of datapoints.\n");
        exit(1);
    }

    // --- calculate moving average ---
    //int lenavg = count - n + 1;  // finds how big the array must be
    //printf("%d", lenavg);
    float averages[count];

    for (int i = 0; i < n - 1; i++) {  // shift backwards by n-1 (based on how k and n are related) and pad with NANs
        averages[i] = NAN;
    }

    //for (int k=0; k <= (count-n); k++) {
    for (int k=0; k <= count -n; k++) {
        float sum = 0;  // sum k values
        for (int i=0; i<n; i++) {
            sum += data[k+i];
        }
        averages[k + n-1] = sum / n;
    }

    // print averages
    //printf("\n");

    char *hline = "|--------+------------+----------------|\n";
    printf("\n");
    printf("%s", hline);
    printf("| Number | Raw Data   | Moving Average |\n");
    printf("%s", hline);
    for (int i = 0; i < count; i++) {
        //printf("average %d = %f\n", i, averages[i]);
        //printf("| %6d | %10.5f | %14.5f |\n", i, data[i], averages[i]);
        printf("| %6d | %10.5f | ", i, data[i]);
        
        if (isnan(averages[i])) printf("%14s |\n", "-");
        else printf("%14.5f |\n", averages[i]);
    }
    printf("%s", hline);

    

    
    exit(0);
}
