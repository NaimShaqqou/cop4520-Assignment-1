#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <atomic>
#include <cstring>

#define MAX_NUM 100000000

using namespace std;
using namespace std::chrono;

// Account for the fact that 2 is a prime number
atomic<long long> sumOfPrimes{2};
atomic<int> numOfPrimes{1};
bool prime[MAX_NUM + 1];

bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

void findPrimes(int start) 
{
    long long sum = 0;
    int num = 0;
    for (int i = start; i <= 1e+8; i = i + 16)
    {
        if (isPrime(i))
        {
            sum += i;
            num++;
            prime[i] = true;
        }
    }

    sumOfPrimes += sum;
    numOfPrimes += num;
}

int main()
{
    int largestPrimes[10];

    memset(prime, false, sizeof(prime));

    ofstream out;
    out.open("primes.txt");

    // Start timer before thread spawning
    auto start = high_resolution_clock::now();

    // Hardcoding the 8 threads provides a 
    // VERY SLIGHT performance boost
    thread one = thread(findPrimes, 3);
    thread two = thread(findPrimes, 5);
    thread three = thread(findPrimes, 7);
    thread four = thread(findPrimes, 9);
    thread five = thread(findPrimes, 11);
    thread six = thread(findPrimes, 13);
    thread seven = thread(findPrimes, 15);
    thread eight = thread(findPrimes, 17);

    one.join();
    two.join();
    three.join();
    four.join();
    five.join();
    six.join();
    seven.join();
    eight.join();

    // end timer after thread execution
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    out << duration.count() / 1e+3 << "s" << " " << numOfPrimes << " " << sumOfPrimes << endl;

    int cnt = 0;
    for (int i = MAX_NUM; i > 0 && cnt <= 10; i--) {
        if (prime[i])
        {
            cnt++;
            largestPrimes[10 - cnt] = i;
        }
    }

    for (int j = 0; j < 10; j++)
        out << largestPrimes[j] << " ";

    out.close();
    return 0;
}