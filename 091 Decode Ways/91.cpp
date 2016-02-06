/*

A message containing letters from A-Z is being encoded to numbers using the following mapping:

    'A' -> 1
    'B' -> 2
       ...
    'Z' -> 26

Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

*/

#include <string>
#include <vector>
using namespace std;

class Solution2 {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0')
            return 0;
        int a = 1, b = 1, c, n = s.length();
        for (int i = 1; i < n; ++i)
        {
            if (s[i] == '0')
            {
                if (s[i - 1] > '2' || s[i - 1] == '0')
                    return 0;
                c = a;
            }
            else if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] < '7')
                c = a + b;
            else
                c = b;

            a = b;
            b = c;
        }
        return b;
    }
};

class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        if (n == 0 || s[0] == '0')
            return 0;

        vector<int> A(n + 1, 1);  // A[i] = ways to decode the first i digits

        for (int i = 2; i <= n; ++i)
            if (s[i - 1] == '0')
            {
                if (s[i - 2] == '0' || s[i - 2] > '2')  // can't have "00" "30" "40" etc.
                    return 0;
                A[i] = A[i - 2];
            }
            else if (s[i - 2] > '2' || s[i - 2] == '0' || (s[i - 2] == '2' && s[i - 1] > '6'))
                A[i] = A[i - 1];               
            else
                A[i] = A[i - 1] + A[i - 2];
        
        return A[n];
    }
};