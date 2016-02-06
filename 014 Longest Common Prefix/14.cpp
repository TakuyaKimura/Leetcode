/*

Write a function to find the longest common prefix string amongst an array of strings.

*/

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        if (n == 0)
            return "";
        string prefix = strs[0];
        int m = prefix.length(), i, j;
        for (i = 0; i < m; ++i)
            for (j = 1; j < n; ++j)
                if (i == strs[j].length() || strs[j][i] != prefix[i])
                    return prefix.substr(0, i);
        return prefix;
    }
};