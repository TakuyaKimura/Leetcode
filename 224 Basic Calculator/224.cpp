/*

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), 
the plus + or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:
    "1 + 1" = 2
    " 2-1 + 2 " = 3
    "(1+(4+5+2)-3)+(6+8)" = 23

Note: Do not use the eval built-in library function.

*/

#include <string>
#include <stack>
using namespace std;

// actually the same idea with the recursive one
class Solution {
public:
    int calculate(string s) {
        stack <int> nums, signs;
        int num = 0, rst = 0, sign = 1;
        for (char c : s)
        {
            if (c >= '0')
                num = num * 10 + c - '0';
            else
            {
                rst += sign * num;
                num = 0;
                if (c == '+')
                    sign = 1;
                else if (c == '-')
                    sign = -1;
                else if (c == '(')
                {
                    nums.push(rst);
                    signs.push(sign);
                    rst = 0;
                    sign = 1;
                }
                else if (c == ')')  // may need to check empty is string is invalid
                {
                    rst = signs.top() * rst + nums.top();
                    signs.pop();
                    nums.pop();
                }
            }
        }
        return rst += sign * num;
    }
};

// recursion
class Solution2 {
public:
    int calculate(string s) {
        int pos = 0;
        return evaluate(s, pos, s.length());
    }
private:
    int evaluate(string& s, int& i, int n) {
        int res = 0, sign = 1;
        while (i < n && s[i] != ')')
        {
            if (s[i] == '+' || s[i] == ' ')
                ++i;
            else if (s[i] == '-')
            {
                ++i;
                sign = -1;
            }
            else if (s[i] == '(')
            {
                ++i;
                res += sign * evaluate(s, i, n);
                sign = 1;
            }
            else  // numeric chars
            {
                int num = 0;
                while (i < n && s[i] >= '0')
                    num = num * 10 + s[i++] - '0';
                res += sign * num;
                sign = 1;
            }
        }
        ++i; // skip the current ')'
        return res;
    }
};

// open up all parentheses
class Solution3 {
public:
    int calculate(string s) {
        int num = 0, ans = 0, sign = 1;
        stack<int> signs;  // the actual sign in the current scope
        signs.push(1);     // imagine the whole string is in a ()
        for (char c : s)
        {
            if (c >= '0')  // +-() are all smaller than 0, or use isdigit(c)
                num = num * 10 + c - '0';
            else if (c == '+' || c == '-')
            {
                ans += sign * signs.top() * num;
                num = 0;
                sign = c == '+' ? 1 : -1;
            }
            else if (c == '(')
            {
                signs.push(sign * signs.top());  // the overall, actual sign
                sign = 1;  // inside (), the first sign is always +
            }
            else if (c == ')')
            {
                ans += sign * signs.top() * num;
                num = 0;
                signs.pop();
            }
        }
        // there may be no char after the last number
        if (num)
            ans += sign * signs.top() * num;
        return ans;
    }
};