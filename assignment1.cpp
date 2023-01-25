#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <functional>

#include <map>

#define MAX_NUM 100000000
#define NUM_THREADS 8

using namespace std;
using namespace std::chrono;

atomic<long long> sumOfPrimes{0};
atomic<int> numOfPrimes{0};

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
    int sum = 0;
    int num = 0;
    for (int i = start; i < 1e+8; i = i + 16)
    {
        if (isPrime(i))
        {
            sum += i;
            num++;
        }
    }

    sumOfPrimes += sum;
    numOfPrimes += num;
}

int main()
{
    vector<thread> threads;
    long int largestPrimes[10];

    atomic<int> counter{MAX_NUM};

    auto start = high_resolution_clock::now();

    int startValues[] = {3, 5, 7, 9, 11, 13, 15, 17};
    // for (int i = 0; i < NUM_THREADS; i++)
    // {
    //     threads.emplace_back(findPrimes, startValues[i]);
    // }

    // for (auto &t : threads)
    // {
    //     t.join();
    // }

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Duration: " << duration.count() << " ms" << endl;
    cout << "Total number of primes found: " << numOfPrimes << endl;
    cout << "Sum of all primes found: " << sumOfPrimes << endl;
    
    // unsigned long sum = 0;
    // cout << "Number of primes found by each thread:" << endl;
    // for (int n = 0; n < NUM_THREADS; n++) {
    //     sum += arr[n];
    //     cout << "Thread " << n + 1 << ": " << arr[n] << endl;
    // }

    // cout << "SUM: " << sum << endl;

    cout << "10 Largest Prime Numbers:" << endl;
    for (int i = 0; i < 10; i++) {
        cout  << i + 1 << ") " << largestPrimes[i] << endl;
    }

    return 0;
}