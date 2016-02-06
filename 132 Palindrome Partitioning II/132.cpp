/*

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minCut(string s) {
        int n = s.length();
        if (n == 0)
            return 0;
        vector<int> cut(n + 1, 0);
        // cut[i] = min cut for the first i characters s[0...i-1]
        for (int i = 0; i <= n; i++)
            cut[i] = i - 1;          // cut[0] has to be -1
        for (int i = 1; i < n; i++)  // i and j are indices
        {
            for (int j = 0; i - j >= 0 && i + j < n && s[i - j] == s[i + j]; j++)         // odd length palindrome
                cut[i + j + 1] = min(cut[i + j + 1], cut[i - j] + 1);                     // j has to start from 0, "dde" 
            for (int j = 1; i - j >= 0 && i + j - 1 < n && s[i - j] == s[i + j - 1]; j++) // even length palindrome
                cut[i + j] = min(cut[i + j], cut[i - j] + 1);
        }
        return cut[n];
    }
};