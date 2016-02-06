/*

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', 
return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5.

*/

#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.length(), i = n - 1, count = 0;
        while (i >= 0 && s[i] == ' ')
            --i;
        while (i >= 0 && s[i] != ' ')
        {
            --i;
            ++count;
        }
        return count;
    }
};