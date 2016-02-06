/*

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

*/

#include <vector>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        vector<int> A(n + 1, 1);  // A[i] = how may distinct ways to climb the first i steps
        for (int i = 2; i <= n; ++i)
            A[i] = A[i - 1] + A[i - 2];
        return A[n];
    }
};

class Solution2 {
public:
    int climbStairs(int n) {
        int a = 1, b = 1, temp;
        for (int i = 2; i <= n; ++i)
        {
            temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }
};