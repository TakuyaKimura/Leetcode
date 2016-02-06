/*

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

*/

#include <string>
#include <stack>
using namespace std;

// ASCII codes for ()[]{} are: 40, 41, 91, 93, 123, 125
// the difference should be 1 <= c - stk.top() <= 2 for a valid pair
class Solution2 {
public:
    bool isValid(string s) {
        stack<char> st;
        for (auto c : s)
        {
            if (c == '(' || c == '{' || c == '[')
                st.push(c);
            else if (st.empty() || c - st.top() > 2 || c - st.top() < 1)
                return false;
            else
                st.pop();
        }
        return st.empty();
    }
};

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for (auto c : s)
        {
            if (c == '(' || c == '{' || c == '[')
                stk.push(c);
            else
            {
                if (stk.empty())
                    return false;
                if (c == ')' && stk.top() != '(')
                    return false;
                else if (c == '}' && stk.top() != '{')
                    return false;
                else if (c == ']' && stk.top() != '[')
                    return false;
                stk.pop();
            }
        }
        return stk.empty();
    }
};

// without using stack
class Solution3 {
public:
    bool isValid(string s) {
        int newLen = s.length(), oldLen, i;
        if (newLen & 1)
            return false;
        do {
            oldLen = newLen;
            for (i = 0; i < oldLen - 1; ++i)  // or newLen
                if (s[i + 1] == s[i] + 1 || s[i + 1] == s[i] + 2)
                {
                    s.erase(i, 2);
                    newLen -= 2;
                    break;  // if newLen in "for", can remove this. Instead of start over, continue looking for next pair
                }
        } while (oldLen != newLen);

        return !newLen;
    }
};