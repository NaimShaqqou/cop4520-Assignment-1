#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <iomanip>

#include <map>

#define MAX_NUM 100000000
#define NUM_THREADS 8

using namespace std;
using namespace std::chrono;

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

int main()
{
    vector<thread> threads;
    vector<int> largestPrimes;
    // long int array[NUM_THREADS];
    // map<thread::id, int> m;

    atomic<int> counter{MAX_NUM};
    atomic<long int> sumOfPrimes{0};
    atomic<int> numOfPrimes{0};

    auto findPrimes = [&]()
    {
        // while (counter <= MAX_NUM)
        while (counter >= 2)
        {
            auto cur = counter--;

            if (cur < MAX_NUM && isPrime(cur))
            {   
                sumOfPrimes += cur;
                numOfPrimes++;

                if (numOfPrimes <= 10)
                    largestPrimes.emplace_back(cur);
                // if (m.find(this_thread::get_id()) != m.end())
                //     array[m[this_thread::get_id()]]++;
            }
        }
    };

    auto start = high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads.emplace_back(findPrimes);
        // m[threads[i].get_id()] = i;
        // cout << threads[i].get_id() << endl;
    }

    for (auto &t : threads)
    {
        t.join();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Duration: " << duration.count() << " ms" << endl;
    cout << "Total number of primes found: " << numOfPrimes << endl;
    cout << "Sum of all primes found: " << sumOfPrimes << endl;
    
    // for (int n = 0; n < NUM_THREADS; n++) {
    //     cout << "Thread " << n + 1 << ": " << array[n] << endl;
    // }

    cout << "10 Largest Prime Numbers:" << endl;
    for (int i = 0; i < 10; i++) {
        cout  << i + 1 << ") " << largestPrimes[i] << endl;
    }
    return 0;
}