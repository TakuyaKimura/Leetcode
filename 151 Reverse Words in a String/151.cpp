/*

Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

For C programmers: Try to solve it in-place in O(1) space.

Clarification:
    What constitutes a word?
    A sequence of non-space characters constitutes a word.
    Could the input string contain leading or trailing spaces?
    Yes. However, your reversed string should not contain leading or trailing spaces.
    How about multiple spaces between two words?
    Reduce them to a single space in the reversed string.

*/

#include <string>
#include <sstream>
using namespace std;

// in-place
class Solution {
public:
    void reverseWords(string &s) {
        reverse(s.begin(), s.end());
        int n = s.length(), i, j, k = 0;
        for (i = 0; i < n; ++i)
        {
            if (s[i] == ' ')
                continue;
            if (k)
                s[k++] = ' ';  // since we have another word for sure, put a space before next word
            j = i;
            while (j < n && s[j] != ' ')
                s[k++] = s[j++];
            reverse(s.begin() + k - (j - i), s.begin() + k);

            i = j;  // will still increase one in for statement
        }
        s.erase(s.begin() + k, s.end());
    }
};

// O(n) space
class Solution2 {
public:
    void reverseWords(string &s) {
        istringstream is(s);
        string temp;
        s.clear();
        while (is >> temp)
            s = temp + " " + s;
        s.pop_back();
    }
};

class Solution3 {
public:
    void reverseWords(string &s) {
        int n = s.length(), stripped = 0, start, end = -1;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == ' ' && (i == 0 || s[i - 1] == ' '))
                ++stripped;
            else if (stripped)
                s[i - stripped] = s[i];
        }
        // may have one more trailing space
        if (s[n - stripped - 1] == ' ')
            ++stripped;

        if (stripped)
        {
            n -= stripped;
            s = s.substr(0, n);
        }

        // reverse the whole string
        reverse(s.begin(), s.end());
        // reverse each word
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == ' ')
            {
                start = end + 1;
                end = i;
                reverse(s.begin() + start, s.begin() + end);
            }
        }
        reverse(s.begin() + end + 1, s.end());  // last word
    }
};

void ownReverse(string &s, int start, int end)
{
    int n = (end - start) / 2;
    char temp;
    for (int i = 0; i < n; ++i)
    {
        temp = s[start + i];
        s[start + i] = s[end - i - 1];
        s[end - i - 1] = temp;
    }
}