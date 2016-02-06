/*

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...)
which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

*/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// DP, 280ms
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j * j <= i; ++j)
                if (dp[i] > dp[i - j * j] + 1)
                    dp[i] = dp[i - j * j] + 1;
        return dp[n];
    }
};

// static dp, 12ms
class Solution2 {
public:
    int numSquares(int n) {
        static vector<int> dp{ 0 };
        int m = dp.size();
        dp.resize(max(m, n + 1), INT_MAX);
        for (int i = m; i <= n; ++i)
            for (int j = 1; j * j <= i; ++j)
                if (dp[i] > dp[i - j * j] + 1)
                    dp[i] = dp[i - j * j] + 1;
        return dp[n];
    }
};

// BFS, 120ms (40ms if use vector<int> instead of vector<bool>)
// Consider a graph which consists of numbers 0, 1, ..., n as its nodes
// there is edge u->v if v == u + a perfect square
class Solution3 {
public:
    int numSquares(int n) {
        queue<int> q;
        vector<bool> visited(n, false);  // max_size for vector<bool> is 4294967295 (2 * INT_MAX), 4 times of vector<int>
        q.push(0);
        int distance = 0, size, num, i, next;
        while (true)
        {
            ++distance;
            size = q.size();
            while (size--)
            {
                num = q.front();
                q.pop();
                for (i = 1; (next = i * i + num) <= n; ++i)
                {
                    if (next == n)
                        return distance;
                    if (!visited[next - 1])
                    {
                        q.push(next);
                        visited[next - 1] = true;
                    }
                }                    
            }
        }
    }
};

/**
    O(sqrt(n)), 4ms

    A natural number is...
    ... a square if and only if each prime factor occurs to an even power in the number's prime factorization.
    ... a sum of two squares if and only if each prime factor that's 3 modulo 4 occurs to an even power in the number's prime factorization.
    ... a sum of three squares if and only if it's not of the form (8b+7)*4^a with integers a and b.
    ... a sum of four squares. Period. No condition. You never need more than four.
*/
class Solution4 {
public:
    int numSquares(int n) {
        while (n % 4 == 0)
            n /= 4;
        if (n % 8 == 7)
            return 4;
        bool min2 = false;
        for (int i = 2, e; i <= n; ++i)
        {
            if (i > n / i)
                i = n;
            e = 0;
            while (n % i == 0)
            {
                n /= i;
                ++e;
            }
            if (e % 2 && i % 4 == 3)
                return 3;
            min2 |= e % 2;
        }
        return 1 + min2;
    }
};

// O(n), 4ms, with just the knowledge that you never need more than four squares
// Lagrange's four-square theorem
class Solution5 {
public:
    int numSquares(int n) {
        int root = sqrt(n), a, b, c;
        for (a = 0; a <= root; ++a)
            for (b = a; b <= root; ++b)
            {
                c = sqrt(n - a * a - b * b);
                if (a * a + b * b + c * c == n)
                    return !!a + !!b + !!c;  // 0 or 1
            }
        return 4;
    }
};