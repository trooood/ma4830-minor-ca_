#include <stdio.h>
#include <stdlib.h>  // for ascii string to long (strtol)
#include <math.h>    // for NANs
#define MAX_DATA 1024 // Maximum number of sensor readings (For buffer changes)

int main(int argc, char *argv[]) {

    // init stuff to handle inputs
    int n;
    char filename[256];
    FILE *fp = NULL;
    const int max_attempts=3;
    int attempts=0;
    int overflow =0;

    // init stuff to save the data in
    char buffer[256];  // for storing stuff per line
    float data[MAX_DATA];  // for storing data floats
    char errors[MAX_DATA][256];  // for storing bad data, 1024 strings with max length 256
    int count = 0;  // counts no. of data

    // --- handle the inputs ---
    //while (fp == NULL || count == 0) {
    while (attempts < max_attempts) {

        printf("Enter filename: ");
        if (scanf("%255s", filename) != 1) {
            printf("Error: Invalid filename input.\n");
            attempts++;
            if (attempts >= max_attempts) {  // exit after max tries
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
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

        //else {  // can get file
        while (fgets(buffer, sizeof(buffer), fp) != NULL && !overflow) {  // read 1 line
            printf("%s", buffer);

            char *ptr = buffer;  // points to start of buffer

            while (*ptr != '\0') {
                while (*ptr == ' ' || *ptr == ',' || *ptr == '\n') ptr++;  // skip space and newline
                // handle bad data here
                if (*ptr == '\0') break;  // stop if end of string

                char *endptr;
                float val = strtof(ptr, &endptr);  // start reading at ptr and end save end at &endptr
                if (ptr == endptr) {  // there is no values in between start and end pointers
                    char *start = ptr;

                    while (*ptr != ' ' && *ptr != ',' && *ptr != '\n' && *ptr != '\0')
                        ptr++;

                    printf("Invalid number: %.*s\n", (int)(ptr - start), start);
                    break;
                }
                
                if (count<MAX_DATA){ //if not over buffer, continue
                    data[count++] = val;  // move to the next element
                    ptr = endptr;  // move pointer to where it was last buffered until
                }
                else { //else print error
                    printf("Warning: Data exceeds maximum of %d samples. Proceeding with first %d values.\n", MAX_DATA, count);  // Error message
                    overflow = 1;
                    break;                     // breaks inner while
                }
            }
            
        }

        fclose(fp);  // close file


        //printf("\n");
        // no data in file
        if (fp != NULL && count==0) {
            printf("Error: File is empty or contains no valid float data.\n");
            attempts++;
            if (attempts >= max_attempts) {  // exit after max tries
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
        }

        break;
    
    }

    // --- handling the data stuff ---
    attempts=0;
    char extra;

    printf("\n");  
    //printf("number of datapoints = %d\n", count);
    // enter n
    while (attempts < max_attempts) {
        printf("Enter window size n: ");
        if (scanf("%d%c", &n, &extra) != 2 || extra != '\n' || n <= 0) {
            printf("Input must be a valid positive integer.\n");
            attempts++;
            while (getchar() != '\n');  // clear remaining input
            if (attempts >= max_attempts) {  // exit after max tries
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
            
        }

        // check that n <= count
        else if (n > count || extra != '\n') {
            printf("Error: n must be smaller than number of datapoints.\n");
            attempts++;
            if (attempts >= max_attempts) {  // exit after max tries
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
        }

        else break;

    }

    // --- calculate moving average ---
    //int lenavg = count - n + 1;  // finds how big the array must be
    //printf("%d", lenavg);
    float averages[count];

    for (int i = 0; i < n - 1; i++) {  // shift backwards by n-1 (based on how k and n are related) and pad with NANs
        averages[i] = NAN;
    }

    for (int k=0; k <= count -n; k++) {
        float sum = 0;  // sum k values
        for (int i=0; i<n; i++) {
            sum += data[k+i];
        }
        averages[k + n-1] = sum / n;
    }

    // print averages
    //printf("\n");

    char *hline = "|--------+----------------+----------------|\n";
    printf("\n");
    printf("%s", hline);
    printf("| Number | Raw Data       | Moving Average |\n");
    printf("%s", hline);
    for (int i = 0; i < count; i++) {
        //printf("average %d = %f\n", i, averages[i]);
        //printf("| %6d | %10.5f | %14.5f |\n", i, data[i], averages[i]);
        printf("| %6d | %14.5f | ", i, data[i]);
        
        if (isnan(averages[i])) printf("%14s |\n", "-");
        else printf("%14.5f |\n", averages[i]);
    }
    printf("%s", hline);

    

    
    exit(0);
}
