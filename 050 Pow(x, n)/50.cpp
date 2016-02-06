/*

Implement pow(x, n).

*/

#include <iostream>
using namespace std;

// -(-2147483648) = -2147483648
// -(INT_MIN) = -(-INT_MAX - 1) = INT_MAX + 1 = INT_MIN

// -2147483648 has to be written as -2147483647 - 1 or INT_MIN
// because the expression is processed in two stages:
// 1. The number 2147483648 is evaluated. Because it is greater than the maximum integer value of 2147483647, the type of 2147483648 is not int, but unsigned int.
// 2. Unary minus is applied to the value, with an unsigned result, which also happens to be 2147483648.

// there are two things to notice in the solution below
// 1. check n is negative when calling the function vs. when return
// 2. tail recursion (pass the calculation as argument x*x) vs. delay the calculation until gets result back from another function call

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0)
            return 1;
        if (n == INT_MIN)
            return myPow(x, ++n) / x;
        if (n < 0)
            return 1 / myPow(x, -n);
        return n % 2 ? x * myPow(x * x, n / 2) : myPow(x * x, n / 2);
    }
};

int main()
{
    Solution s;
    cout << s.myPow(1.00000, -2147483647 - 1);
    //cout << -(-2147483647 - 1);  // -2147483648\

    cout << s.myPow(22.14659, -2);
    //cout << -3 / 2;
}