/*

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . 
The integer division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:
    "3+2*2" = 7
    " 3/2 " = 1
    " 3+5 / 2 " = 5

Note: Do not use the eval built-in library function.

*/

#include <sstream>
using namespace std;

// without use of stack
// add the previous term to the result only when encountering +/-
class Solution {
public:
    int calculate(string s) {
        istringstream in('+' + s + '+');
        long long result = 0, term = 0, multiplier;
        char op;
        while (in >> op)
        {
            if (op == '+' || op == '-')
            {
                result += term;
                in >> term;
                term *= 44 - op;  // + is 43, - is 45
            }
            else
            {
                in >> multiplier;
                if (op == '*')
                    term *= multiplier;
                else
                    term /= multiplier;
            }
        }
        return result;
    }
};