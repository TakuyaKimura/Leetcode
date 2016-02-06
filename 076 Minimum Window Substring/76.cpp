/*

Given a string S and a string T, find the minimum window in S 
which will contain all the characters in T in complexity O(n).

For example,
    S = "ADOBECODEBANC"
    T = "ABC"
    Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.

*/

#include <string>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int remaining = 0, n = s.length(), minLen = 0, left = 0, require[128] {};
        for (char c : t)
        {
            ++require[c];
            ++remaining;
        }

        //if (remaining == 0)
        //    return "";

        for (int i = 0, start = 0; i < n; ++i)
        {
            if (require[s[i]] > 0)
                --remaining;

            --require[s[i]];  // include it, decrement even for chars that are not in t

            if (remaining == 0)
            {
                while (require[s[start]] < 0)  // must be either 0 or negative
                    ++require[s[start++]];     // exclude it

                if (i - start + 1 < minLen || minLen == 0)
                {
                    minLen = i - start + 1;
                    left = start;
                }
            }
        }

        return s.substr(left, minLen);  // this is why we don't initialize minLen to be INT_MAX
    }
};