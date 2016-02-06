/*

Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. 

For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super ugly numbers 
given primes = [2, 7, 13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ¡Ü 100, 0 < n ¡Ü 106, 0 < primes[i] < 1000.

*/

#include <vector>
#include <queue>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <map>
using namespace std;

// use map, since it's ordered, O(nlogk)
class Solution2 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size(), idx, prime, product;
        vector<int> uglies(n, 1);
        vector<int> indexOfMultiplier(k, 0);  // for prime i, * uglies[indexOfMultiplier[i]] is already added to heap
        map<int, int> heap;
        for (int i = 0; i < k; ++i)
            heap.insert(make_pair(primes[i], i));
        for (int i = 1; i < n; ++i)
        {
            uglies[i] = heap.begin()->first;
            idx = heap.begin()->second;
            prime = primes[idx];
            heap.erase(heap.begin());
            while (heap.find(product = prime * uglies[++indexOfMultiplier[idx]]) != heap.end()) {}
            heap.insert(make_pair(product, idx));
        }
        return uglies[n - 1];
    }
};

// use priority_queue, O(nlogk)
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size(), idx, prime, product;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;  // num and which prime it comes from
        unordered_set<int> hash;
        vector<int> uglies(n, 1);
        vector<int> indexOfMultiplier(k, 0);  // for prime i, * uglies[indexOfMultiplier[i]] is already added to heap
        for (int i = 0; i < k; ++i)
            minHeap.push(make_pair(primes[i], i));

        for (int i = 1; i < n; ++i)
        {
            uglies[i] = minHeap.top().first;
            idx = minHeap.top().second;  // which prime
            prime = primes[idx];
            minHeap.pop();
            while (hash.find(product = prime * uglies[++indexOfMultiplier[idx]]) != hash.end()) {}
            minHeap.push(make_pair(product, idx));
            hash.insert(product);     
        }
        return uglies[n - 1];
    }
};

// O(nk)
class Solution3 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size(), idx, next;
        vector<int> uglies(n, 1);
        vector<int> indexOfMultiplier(k, 0);
        for (int i = 1; i < n; ++i)
        {
            next = INT_MAX;
            for (int j = 0; j < k; ++j)
                next = min(next, primes[j] * uglies[indexOfMultiplier[j]]);
            uglies[i] = next;

            for (int j = 0; j < k; ++j)
                if (primes[j] * uglies[indexOfMultiplier[j]] == next)
                    ++indexOfMultiplier[j];
        }
        return uglies[n - 1];
    }
};