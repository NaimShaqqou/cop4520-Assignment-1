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

map<string, int> m;
// atomic<unsigned long> arr[NUM_THREADS];

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
    cout << "start at: " << start << endl;
    int sum = 0;
    int num = 0;
    for (int i = start; i < 1e+8; i = i + 16)
    {
        if (isPrime(i))
        {
            sum += i;
            num++;

            // stringstream ss;
            // ss << this_thread::get_id();
            // string id = ss.str();
            // // if (m.find(id) != m.end())
            // arr[m[id]]++;
        }
    }

    sumOfPrimes += sum;
    numOfPrimes += num;
}

int main()
{
    vector<thread> threads;
    long int largestPrimes[10];

    // atomic<unsigned long> arr[NUM_THREADS];
    // arr[0] = 0;
    // arr[1] = 0;
    // arr[2] = 0;
    // arr[3] = 0;
    // arr[4] = 0;
    // arr[5] = 0;
    // arr[6] = 0;
    // arr[7] = 0;
    // map<thread::id, int> m;
    // map<string, int> m;

    atomic<int> counter{MAX_NUM};
    // atomic<long long> sumOfPrimes{0};
    // atomic<int> numOfPrimes{0};

    // auto findPrimes = [&]()
    // {
    //     // while (counter <= MAX_NUM)
    //     while (counter >= 2)
    //     {
    //         auto cur = atomic_fetch_sub(&counter, 2);

    //         if (cur >= 2 && isPrime(cur))
    //         {   
    //             // if (numOfPrimes <= 10)
    //             //     largestPrimes.push_back(cur);

    //             if (numOfPrimes < 10)
    //                 largestPrimes[numOfPrimes] = cur;

    //             sumOfPrimes += cur;
    //             numOfPrimes++;

    //             stringstream ss;
    //             ss << this_thread::get_id();
    //             string id = ss.str();
    //             // if (m.find(id) != m.end())
    //                 array[m[id]]++;
    //         }
    //     }
    // };

    auto start = high_resolution_clock::now();

    int startValues[] = {3, 5, 7, 9, 11, 13, 15, 17};
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads.push_back(thread(findPrimes, startValues[i]));
        // stringstream ss;
        // ss << threads[i].get_id();
        // string id = ss.str();
        // m[id] = i;
        // cout << id << " " << i << endl;
    }

    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

    // for (auto &t : threads)
    // {
    //     t.join();
    // }

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