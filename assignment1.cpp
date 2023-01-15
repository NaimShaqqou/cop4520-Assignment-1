#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>

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

    atomic<int> counter{2};
    atomic<long int> sumOfPrimes = 0;
    atomic<int> numOfPrimes = 0;

    auto findPrimes = [&]()
    {
        while (counter <= MAX_NUM)
        {
            auto cur = counter++;

            if (cur < MAX_NUM && isPrime(cur))
            {   
                sumOfPrimes += cur;
                numOfPrimes++;
            }
        }
    };

    auto start = high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads.emplace_back(findPrimes);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "sum of the prime numbers under " << MAX_NUM << ": " << sumOfPrimes << endl
         << "number of prime numbers under " << MAX_NUM << ": " << numOfPrimes << endl
         << "duration: " << duration.count() << " ms" << endl;

    return 0;
}