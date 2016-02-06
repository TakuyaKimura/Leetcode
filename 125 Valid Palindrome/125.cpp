/*

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.

*/

#include <string>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int start = 0, end = s.length() - 1;
        while (start < end)
        {
            while (start < end && !isalnum(s[start]))
                ++start;
            while (start < end && !isalnum(s[end]))
                --end;
            if (tolower(s[start++]) != tolower(s[end--]))
                return false;
            //++start;
            //--end;
        }
        return true;
    }
};