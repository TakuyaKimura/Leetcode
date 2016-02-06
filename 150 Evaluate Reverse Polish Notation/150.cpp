/*

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
    ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
    ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

*/

#include <vector>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> operands;
        int op1, op2;
        for (string token : tokens)
        {
            if (token == "+" || token == "-" || token == "*" || token == "/")
            {
                op2 = operands.top();  // note the order of the operands!!!!!!!!!!!!!!
                operands.pop();
                op1 = operands.top();
                operands.pop();
                if (token == "+")
                    operands.push(op1 + op2);
                else if (token == "-")
                    operands.push(op1 - op2);
                else if (token == "*")
                    operands.push(op1 * op2);
                else
                    operands.push(op1 / op2);
            }
            else
                operands.push(stoi(token));
        }
        return operands.top();
    }
};