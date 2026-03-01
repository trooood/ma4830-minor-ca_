#include <stdio.h>
#include <stdlib.h>  // for ascii string to long (strtol)
#include <math.h>    // for NANs

int main(int argc, char *argv[]) {

    // --- handle the inputs ---

    char *endptr;

    // handle exceptions: arg count is not 2
    if (argc != 3) {
        printf("Invalid arguments. Usage: %s <integer> <string>\n", argv[0]);
        return 1;
    }

    // check the integer and assign n
    // convert 1st arg to long, base 10, endptr points to where it was converted
    int n = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        printf("First argument must be a valid integer.\n");
        return 1;
    }

    // assign filename string
    char *filename = argv[2];  // points to the data
    FILE *fp = fopen(filename, "r");  // open buffered file! read only

    printf("n = %d\n", n);
    printf("data file = %s\n", filename);

    // --- handling the data stuff ---

    // init stuff to save the data in
    char buffer[256];  // for storing stuff per line
    float data[1024];  // for storing data floats
    int count = 0;  // counts no. of data

    // cannot open file
    if (fp == NULL) {
        perror("cannot open");
        exit(1);
    }

    else {  // can get file
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
    }

    fclose(fp);  // close file

    printf("\n");
    printf("number of datapoints = %d\n", count);

    // --- calculate moving average ---
    //int lenavg = count - n + 1;  // finds how big the array must be
    //printf("%d", lenavg);
    float averages[count];

    for (int i = 0; i < n - 1; i++) {  // shift backwards by n-1 (based on how k and n are related)
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
    printf("\n");

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