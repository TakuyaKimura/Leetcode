/*

Given a string s, return all the palindromic permutations (without duplicates) of it. 

Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].

Hint:
If a palindromic permutation exists, we just need to generate the first half of the string.
To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

*/

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> result;
        if (isPalindromic(s))
            dfs(s, 0, s.length() / 2, result);
        return result;
    }
private:
    // rearrange s so that the first half of the palindrome is sorted
    bool isPalindromic(string& s) {
        int count[256] = { 0 };
        for (char c : s)
            ++count[c];

        bool oneOdd = false;
        for (int cnt : count)
            if (cnt % 2 == 1)
                if (oneOdd)
                    return false;
                else
                    oneOdd = true;

        for (int i = 0, j = 0; i < 256; ++i)
        {
            int cnt = count[i];
            if (cnt % 2 == 1)
                s[s.length() / 2] = i;
            cnt /= 2;
            while (cnt--)
                s[j++] = i;
        }
        return true;
    }

    void dfs(string s, int start, int end, vector<string>& result) {
        if (start == end)
        {
            int i = 0, j = s.length() - 1;
            while (i < j)
                s[j--] = s[i++];
            result.push_back(s);
        }
        for (int i = start; i < end; ++i)
        {
            if (i != start && s[i] == s[start])
                continue;
            swap(s[i], s[start]);
            dfs(s, start + 1, end, result);
        }
    }
};

int main() {
    Solution s;
    s.generatePalindromes("a");
}