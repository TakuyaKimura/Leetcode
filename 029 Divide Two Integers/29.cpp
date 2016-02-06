/*

Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

*/

#include <algorithm>
#include <iostream>
using namespace std;

// O(1), 31 or 32 loops
// think of as binary numbers
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0 || dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        if (divisor == 1)
            return dividend;
        bool negative = dividend < 0 ^ divisor < 0;
        unsigned int u_dividend = abs(dividend), u_divisor = abs(divisor);
        int result = 0;
        for (int i = 30; i >= 0; --i)  // or 31, if didn't edge case divisor==1
        {
            if ((u_dividend >> i) >= u_divisor)
            {
                result += (1 << i);
                u_dividend -= (u_divisor << i);
            }
        }
        return negative ? -result : result;
    }
};

class Solution2 {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0 || dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        if (divisor == 1)
            return dividend;
        bool neg = dividend < 0 ^ divisor < 0;
        unsigned int u_dividend = abs(dividend), u_divisor = abs(divisor);
        int result = 0;
        for (int i = 30, power = 1 << 30; i >= 0; --i, power >>= 1)  // 1 << 31 = INT_MIN, further >>=1 is not correct
        {
            if (u_dividend >> i >= u_divisor)
            {
                result += power;
                u_dividend -= u_divisor << i;
            }
        }
        return neg ? -result : result;
    }
};

class Solution3 {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0 || dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        bool negative = dividend < 0 ^ divisor < 0;
        unsigned int u_dividend = abs(dividend), u_divisor = abs(divisor), result = 0;
        for (int i = 31; i >= 0; --i)
        {
            if ((u_dividend >> i) >= u_divisor)
            {
                result += (1 << i);
                u_dividend -= (u_divisor << i);
            }
        }
        if (negative)
            if (result == (unsigned int)1 << 31)
                return INT_MIN;
            else
                return 0 - result;
        return result;
    }
};



int main()
{
    int i = abs(INT_MIN);
    unsigned int ui = abs(INT_MIN);
    cout << i << endl << ui << endl;

    Solution2 s;
    cout << s.divide(INT_MIN, 1);
}