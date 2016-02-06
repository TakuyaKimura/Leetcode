/*

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 

For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number.

Hint:
1. The naive approach is to call isUgly for every number until you reach the nth one. 
   Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.

2. An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.

3. The key is how to maintain the order of the ugly numbers.
   Try a similar approach of merging from three sorted lists: L1, L2, and L3.

4. Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).

*/

#include <vector>
#include <algorithm>
using namespace std;

// DP, 12ms
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> ugly(n, 1);
        int next, p2 = 0, p3 = 0, p5 = 0;  // use pointers, instead of using 3 queues
        for (int i = 1; i < n; ++i)
        {
            next = min(min(ugly[p2] * 2, ugly[p3] * 3), ugly[p5] * 5);
            ugly[i] = next;
            if (next == ugly[p2] * 2)  // may increase one than one index
                ++p2;
            if (next == ugly[p3] * 3)
                ++p3;
            if (next == ugly[p5] * 5)
                ++p5;
        }
        return ugly[n - 1];
    }
};