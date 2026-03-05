# MA4830 CA (The missile knows where it is because it knows where isn’t)
### Team members: Alicia, Trudy, Walter
- Latest iteration is: movavgOverflowfix.c
- Set .gitignore to ignore .exe files and personal test files

## - Latest Update
- Fixed Possibility of overflowing integers

## Current Output/Debug issues with current iteration ; Refer to bottom for terminal output
### Comments for input with data.dat(Window size,filename etc)
- Need exit upon invalid file/file not found
- Non-integer window size "Crashes"
- Still accepts decimalized window size e.g. n= 4.5

### Individual bad file output
#### Bad data(Trudy)
Comments: should we reject infinity? Fix has issue, once error reach, jumps to next line

#### Bad1(string inside)
Comments: stops at string

#### Bad2(empty)
Comments: Same as above, need to leave i.e. not prompt window size

#### Bad3(just 1 number)
Comments: Ok

#### Bad4 (Special Characters)
Comments: Same as Bad1, stops at character

#### Bad5 (Special characaters and alphabets with numbers)
Comments: Also same as Bad2 and Bad4, but recognizes 30, which is good?

## Extras
- Say it expects positive and negative floats

### Output for data.dat
(base) PS C:\Users\User\Claude projects\ma4830-minor-ca_> .\movavgOverflowfix.exe
Enter filename: data.dat
-92.730 43.762 65.31 -68.878 -7.56 -78.895 29.71 -26.198 17.023 89.191
66.07 5.36 -11.130 8.112 -71.783 -44.20 -40.28 -4.692 -65.91 -21.631  
-75.82 -39.10 49.375 -88.391 -66.77 -2.405 -73.94 55.789 70.94 -38.90 
Enter window size n: 999
Error: n must be smaller than number of datapoints.
Enter window size n: -5
First input must be a valid positive integer.
Enter window size n: 4

|--------+----------------+----------------|
| Number | Raw Data       | Moving Average |
|--------+----------------+----------------|
|      0 |      -92.73000 |              - |
|      1 |       43.76200 |              - |
|      3 |      -68.87800 |      -13.13400 |
|      4 |       -7.56000 |        8.15850 |
|      5 |      -78.89500 |      -22.50575 |
|      6 |       29.71000 |      -31.40575 |
|      7 |      -26.19800 |      -20.73575 |
|      8 |       17.02300 |      -14.59000 |
|      9 |       89.19100 |       27.43150 |
|     10 |       66.07000 |       36.52150 |
|     11 |        5.36000 |       44.41100 |
|     12 |      -11.13000 |       37.37275 |
|     14 |      -71.78300 |      -17.36025 |
|     15 |      -44.20000 |      -29.75025 |
|     16 |      -40.28000 |      -37.03775 |
|     17 |       -4.69200 |      -40.23875 |
|     18 |      -65.91000 |      -38.77050 |
|     19 |      -21.63100 |      -33.12825 |
|     20 |      -75.82000 |      -42.01325 |
|     21 |      -39.10000 |      -50.61525 |
|     22 |       49.37500 |      -21.79400 |
|     24 |      -66.77000 |      -36.22150 |
|     25 |       -2.40500 |      -27.04775 |
|     26 |      -73.94000 |      -57.87650 |
|     27 |       55.78900 |      -21.83150 |
|     28 |       70.94000 |       12.59600 |
|     29 |      -38.90000 |        3.47225 |
|--------+----------------+----------------|

(base) PS C:\Users\User\Claude projects\ma4830-minor-ca_> .\movavgOverflowfix.exe
Enter filename: abc

Enter window size n: 2
Error: n must be smaller than number of datapoints.
Enter window size n: 1
Error: n must be smaller than number of datapoints.
Enter window size n: 0
First input must be a valid positive integer.
Too many failed attempts. Exiting.

(base) PS C:\Users\User\Claude projects\ma4830-minor-ca_> .\movavgOverflowfix.exe
Enter filename: data.dat
-92.730 43.762 65.31 -68.878 -7.56 -78.895 29.71 -26.198 17.023 89.191
66.07 5.36 -11.130 8.112 -71.783 -44.20 -40.28 -4.692 -65.91 -21.631
-75.82 -39.10 49.375 -88.391 -66.77 -2.405 -73.94 55.789 70.94 -38.90
Enter window size n: abc
First input must be a valid positive integer.
Enter window size n: First input must be a valid positive integer.
Enter window size n: First input must be a valid positive integer.
Too many failed attempts. Exiting.

(base) PS C:\Users\User\Claude projects\ma4830-minor-ca_> .\movavgOverflowfix.exe
Enter filename: data.dat
-92.730 43.762 65.31 -68.878 -7.56 -78.895 29.71 -26.198 17.023 89.191
66.07 5.36 -11.130 8.112 -71.783 -44.20 -40.28 -4.692 -65.91 -21.631
-75.82 -39.10 49.375 -88.391 -66.77 -2.405 -73.94 55.789 70.94 -38.90
Enter window size n: 4.5

|--------+----------------+----------------|
| Number | Raw Data       | Moving Average |
|--------+----------------+----------------|
|      0 |      -92.73000 |              - |
|      1 |       43.76200 |              - |
|      3 |      -68.87800 |      -13.13400 |
|      4 |       -7.56000 |        8.15850 |
|      5 |      -78.89500 |      -22.50575 |
|      6 |       29.71000 |      -31.40575 |
|      7 |      -26.19800 |      -20.73575 |
|      8 |       17.02300 |      -14.59000 |
|      9 |       89.19100 |       27.43150 |
|     10 |       66.07000 |       36.52150 |
|     11 |        5.36000 |       44.41100 |
|     12 |      -11.13000 |       37.37275 |
|     13 |        8.11200 |       17.10300 |
|     14 |      -71.78300 |      -17.36025 |
|     15 |      -44.20000 |      -29.75025 |
|     16 |      -40.28000 |      -37.03775 |
|     17 |       -4.69200 |      -40.23875 |
|     18 |      -65.91000 |      -38.77050 |
|     19 |      -21.63100 |      -33.12825 |
|     20 |      -75.82000 |      -42.01325 |
|     21 |      -39.10000 |      -50.61525 |
|     22 |       49.37500 |      -21.79400 |
|     23 |      -88.39100 |      -38.48400 |
|     24 |      -66.77000 |      -36.22150 |
|     25 |       -2.40500 |      -27.04775 |
|     26 |      -73.94000 |      -57.87650 |
|     27 |       55.78900 |      -21.83150 |
|     28 |       70.94000 |       12.59600 |
|     29 |      -38.90000 |        3.47225 |
|--------+----------------+----------------|
(base) PS C:\Users\User\Claude projects\ma4830-minor-ca_> .\movavgOverflowfix.exe
Enter filename: data.dat
-92.730 43.762 65.31 -68.878 -7.56 -78.895 29.71 -26.198 17.023 89.191
66.07 5.36 -11.130 8.112 -71.783 -44.20 -40.28 -4.692 -65.91 -21.631
-75.82 -39.10 49.375 -88.391 -66.77 -2.405 -73.94 55.789 70.94 -38.90
Enter window size n: 0
First input must be a valid positive integer.

### Bad_data.dat Ouput
Enter filename: Bad_data.dat             
-92.730 43.1e99999 y65.31 -68.878
Invalid number: y65.31
-7.56 -78.895 29.71 -26.198 17.023 89.191
66.07 5.36 -11.130 8.112 six-sevennnn -71.783 -44.20 -40.28
Invalid number: six-sevennnn
-4.692 -65.91 -21.631
-75,82 -39.10 49.37.5 -88.391 -66..77 -2.405 -73.94 55.789 70.94 -38.90
Enter window size n: 3

|--------+----------------+----------------|
| Number | Raw Data       | Moving Average |
|--------+----------------+----------------|
|      0 |      -92.73000 |              - |
|      1 |            inf |              - |
|      2 |       -7.56000 |            inf |
|      3 |      -78.89500 |            inf |
|      4 |       29.71000 |      -18.91500 |
|      5 |      -26.19800 |      -25.12766 |
|      6 |       17.02300 |        6.84500 |
|      7 |       89.19100 |       26.67200 |
|      8 |       66.07000 |       57.42800 |
|      9 |        5.36000 |       53.54033 |
|     10 |      -11.13000 |       20.10000 |
|     11 |        8.11200 |        0.78067 |
|     12 |       -4.69200 |       -2.57000 |
|     13 |      -65.91000 |      -20.83000 |
|     14 |      -21.63100 |      -30.74433 |
|     15 |      -75.00000 |      -54.18033 |
|     16 |       82.00000 |       -4.87700 |
|     17 |      -39.10000 |      -10.70000 |
|     18 |       49.37000 |       30.75667 |
|     19 |        0.50000 |        3.59000 |
|     20 |      -88.39100 |      -12.84033 |
|     21 |      -66.00000 |      -51.29700 |
|     22 |        0.77000 |      -51.20700 |
|     23 |       -2.40500 |      -22.54500 |
|     24 |      -73.94000 |      -25.19167 |
|     25 |       55.78900 |       -6.85200 |
|     26 |       70.94000 |       17.59633 |
|     27 |      -38.90000 |       29.27633 |
|--------+----------------+----------------|

### Bad1.dat ouput
Enter filename: bad1.dat
10.5 20.3 hello 15.2 8.7Invalid number: hello

Enter window size n: 2

|--------+----------------+----------------|
| Number | Raw Data       | Moving Average |
|--------+----------------+----------------|
|      0 |       10.50000 |              - |
|      1 |       20.30000 |       15.40000 |
|--------+----------------+----------------|

### Bad2.dat ouput
Enter filename: bad2.dat 
Error: File is empty or contains no valid float data.

Enter window size n: 2
Error: n must be smaller than number of datapoints.
Enter window size n: 2
Error: n must be smaller than number of datapoints.
Enter window size n: 2
Error: n must be smaller than number of datapoints.
Too many failed attempts. Exiting.

### Bad3.dat ouput
Enter filename: bad3.dat
42.0
Enter window size n: 2
Error: n must be smaller than number of datapoints.
Enter window size n: 3
Error: n must be smaller than number of datapoints.
Enter window size n: 1

|--------+----------------+----------------|
| Number | Raw Data       | Moving Average |
|--------+----------------+----------------|
|      0 |       42.00000 |       42.00000 |
|--------+----------------+----------------|

### Bad4.dat output
Enter filename: bad4.dat
10 20 30 ! 40 50Invalid number: !

Enter window size n: 4
Error: n must be smaller than number of datapoints.
Enter window size n: 2

|--------+----------------+----------------|
| Number | Raw Data       | Moving Average |
|--------+----------------+----------------|
|      0 |       10.00000 |              - |
|      1 |       20.00000 |       15.00000 |
|      2 |       30.00000 |       25.00000 |
|--------+----------------+----------------|

### Bad5.dat output
(base) PS C:\Users\User\Claude projects\ma4830-minor-ca_> .\movavgOverflowfix.exe
Enter filename: bad5.dat
10 20 30! 40abc 50Invalid number: !

Enter window size n: 4
Error: n must be smaller than number of datapoints.
Enter window size n: 2

|--------+----------------+----------------|
| Number | Raw Data       | Moving Average |
|--------+----------------+----------------|
|      0 |       10.00000 |              - |
|      1 |       20.00000 |       15.00000 |
|      2 |       30.00000 |       25.00000 |
|--------+----------------+----------------|