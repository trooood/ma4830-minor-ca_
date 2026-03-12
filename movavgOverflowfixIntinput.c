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
    int i, k;
    char extra;
    char *hline;
    float averages[MAX_DATA];
    char input[256];
    float sum;

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
            continue;
        }

        fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Cannot open file: No such file or directory.\n");
            attempts++;
            if (attempts >= max_attempts) {  // exit after max tries
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
            continue;
        }

        //else {  // can get file
        while (fgets(buffer, sizeof(buffer), fp) != NULL && !overflow) {  // read 1 line
            char *ptr = buffer;  // points to start of buffer
             
            char *endptr;
            float val;

            printf("%s", buffer);

            while (*ptr != '\0') {
                while (*ptr == ' ' || *ptr == ',' || *ptr == '\n') ptr++;  // skip space and newline
                // handle bad data here
                if (*ptr == '\0') break;  // stop if end of string

                val = strtof(ptr, &endptr);  // start reading at ptr and end save end at &endptr
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
    while (getchar() != '\n');   /* flush leftover from filename scanf */

        printf("\n");  
    //printf("number of datapoints = %d\n", count);
    // enter n
    while (attempts < max_attempts) {
        printf("Enter window size n: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input must be a valid positive integer.\n");
            attempts++;
            if (attempts >= max_attempts) {
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
            continue;
        }
        if (sscanf(input, "%d%c", &n, &extra) == 2 && extra == '\n' && n > 0) {
            if (n > count) {
                printf("Error: n must be smaller than number of datapoints.\n");
                attempts++;
                if (attempts >= max_attempts) {
                    printf("Too many failed attempts. Exiting.\n");
                    return 1;
                }
                continue;
            }
            break;
        }
        printf("Input must be a valid positive integer.\n");
        attempts++;
        if (attempts >= max_attempts) {
            printf("Too many failed attempts. Exiting.\n");
            return 1;
        }
    }

    // --- calculate moving average ---
    //int lenavg = count - n + 1;  // finds how big the array must be
    //printf("%d", lenavg);

    for (i = 0; i < n - 1; i++) {  // shift backwards by n-1 (based on how k and n are related) and pad with NANs
        averages[i] = NAN;
    }

    for (k=0; k <= count -n; k++) {
        float sum = 0;  // sum k values
        for (i=0; i<n; i++) {
            sum += data[k+i];
        }
        averages[k + n-1] = sum / n;
    }

    // print averages
    //printf("\n");

    hline = "|--------+----------------+----------------|\n";
    printf("\n");
    printf("%s", hline);
    printf("| Number | Raw Data       | Moving Average |\n");
    printf("%s", hline);
    for (i = 0; i < count; i++) {
        //printf("average %d = %f\n", i, averages[i]);
        //printf("| %6d | %10.5f | %14.5f |\n", i, data[i], averages[i]);
        printf("| %6d | %14.5f | ", i, data[i]);
        
        if (isnan(averages[i])) printf("%14s |\n", "-");
        else printf("%14.5f |\n", averages[i]);
    }
    printf("%s", hline);

        // fluctuation analysis
    printf("\n");
    printf("=== Fluctuation Analysis ===\n");

    // init for calculations
    float raw_sum = 0, raw_mean = 0, raw_variance = 0, raw_stddev = 0;
    float filt_sum = 0, filt_mean = 0, filt_variance = 0, filt_stddev = 0;
    int valid_filtered_count = 0;

    // raw data sum
    for (int i = 0; i < count; i++) {
        raw_sum += data[i];
    }
    
    // raw data mean
    raw_mean = raw_sum / count;

    // filtered data sum
    for (int i = 0; i < count; i++) {
        if (!isnan(averages[i])) {
            filt_sum += averages[i];
            valid_filtered_count++;
        }
    }
    
    //filtered data mean
    filt_mean = filt_sum / valid_filtered_count;

    // raw data std and variance
    for (int i = 0; i < count; i++) {
        raw_variance += pow(data[i] - raw_mean, 2);
    }
    raw_variance = raw_variance / count;
    raw_stddev = sqrt(raw_variance);

    // filtered data std and variance
    for (int i = 0; i < count; i++) {
        if (!isnan(averages[i])) {
            filt_variance += pow(averages[i] - filt_mean, 2);
        }
    }
    filt_variance = filt_variance / valid_filtered_count;
    filt_stddev = sqrt(filt_variance);

    // results
    printf("\n");
    printf("|-------------------------+-------------------------|\n");
    printf("|         Raw Data        |      Filtered Data      |\n");
    printf("|-------------------------+-------------------------|\n");
    printf("| Mean: %14.5f    | Mean: %14.5f    |\n", raw_mean, filt_mean);
    printf("| Variance: %11.5f   | Variance: %11.5f   |\n", raw_variance, filt_variance);
    printf("| Std Dev: %12.5f   | Std Dev: %12.5f   |\n", raw_stddev, filt_stddev);
    printf("|-------------------------+-------------------------|\n");

    // comparison
    printf("\n");
    printf("=== Comparison ===\n");
    printf("\n");

    //calculate percentage difference in variance and std
    float variance_reduction = ((raw_variance - filt_variance) / raw_variance) * 100;
    float stddev_reduction = ((raw_stddev - filt_stddev) / raw_stddev) * 100;

    printf("Reduction in Variance: %.2f%%\n", variance_reduction);
    printf("Reduction in Std Devation: %.2f%%\n", stddev_reduction);

    //comments on fluctuation reduction
    if (filt_variance < raw_variance) {
        printf("\nFiltered values have reduced fluctuation.\n");
        if (variance_reduction > 50) {
            printf("Extremely effective fluctuation reduction.\n");
        }
        else if (variance_reduction > 25) {
            printf("Very effective fluctuation reduction.\n");
        }
        else if (variance_reduction > 10) {
            printf("Effective fluctuation reduction.\n");
        }
        else {
            printf("Slightly effective fluctuation reduction. Try larger window size.\n");
        }
    }
    else {
        printf("\nFiltered values do not have reduced fluctuation.\n");
    }

    return 0;
}
