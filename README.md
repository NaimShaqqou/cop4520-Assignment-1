# COP 4520 Programming Assignment 1

This is a program that uses parallel processing concepts learned in class to find all prime numbers up to `10^8`.

## Approach

The program spawns 8 threads, as per assignment requirements. Each thread processes a disjoint set of integers between `2` and `10^8`.

The approach uses an `O(sqrt(n))` primality check. The algorithm demonstrates the power of multithreading through the efficiency we were able to achieve by using multiple threads.

The runtime for this program is around `3 seconds` using the approach outlined above.

## How to Run

Use the following commands to run the program:

```
g++ -std=c++11 -pthread assignment1.cpp
./a.out
```

Note: Windows Powershell users, the command is `.\a.exe`

## Output Format

The program will output to a file names `primes.txt`. The format of the output is as follows:

```
<execution time>  <total number of primes found>  <sum of all primes found> 
<top ten maximum primes, listed in order from lowest to highest> 
```

To see an example output, view the `primes.txt` file in this directory.
