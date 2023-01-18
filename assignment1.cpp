#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <sstream>

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
    long int largestPrimes[10];

    atomic<unsigned long> array[NUM_THREADS];
    array[0] = 0;
    array[1] = 0;
    array[2] = 0;
    array[3] = 0;
    array[4] = 0;
    array[5] = 0;
    array[6] = 0;
    array[7] = 0;
    // map<thread::id, int> m;
    map<string, int> m;

    atomic<int> counter{MAX_NUM};
    atomic<long long> sumOfPrimes{0};
    atomic<int> numOfPrimes{0};

    auto findPrimes = [&]()
    {
        // while (counter <= MAX_NUM)
        while (counter >= 2)
        {
            auto cur = counter--;

            if (cur >= 2 && isPrime(cur))
            {   
                // if (numOfPrimes <= 10)
                //     largestPrimes.push_back(cur);

                if (numOfPrimes < 10)
                    largestPrimes[numOfPrimes] = cur;

                sumOfPrimes += cur;
                numOfPrimes++;

                stringstream ss;
                ss << this_thread::get_id();
                string id = ss.str();
                // if (m.find(id) != m.end())
                    array[m[id]]++;
            }
        }
    };

    auto start = high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads.emplace_back(findPrimes);
        stringstream ss;
        ss << threads[i].get_id();
        string id = ss.str();
        m[id] = i;
        cout << id << " " << i << endl;
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
    
    unsigned long sum = 0;
    cout << "Number of primes found by each thread:" << endl;
    for (int n = 0; n < NUM_THREADS; n++) {
        sum += array[n];
        cout << "Thread " << n + 1 << ": " << array[n] << endl;
    }

    cout << "SUM: " << sum << endl;

    cout << "10 Largest Prime Numbers:" << endl;
    for (int i = 0; i < 10; i++) {
        cout  << i + 1 << ") " << largestPrimes[i] << endl;
    }

    return 0;
}