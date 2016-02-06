/*

Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

    Given numerator = 1, denominator = 2, return "0.5".
    Given numerator = 2, denominator = 1, return "2".
    Given numerator = 2, denominator = 3, return "0.(6)".

*/

#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

// If the quotient a/b is representable, the expression (a/b)*b + a%b shall equal a; otherwise, the behavior of both a/b and a%b is undefined.

// abs(INT_MIN) == INT_MIN

class Solution2 {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (denominator == 0)
            return "NaN";
        string integer, decimal;
        if (numerator < 0 ^ denominator < 0)
            integer = "-";
        long long l_numerator = abs((long long)numerator), l_denominator = abs((long long)denominator), mod;
        unordered_map<int, int> map;
        int i = 0;
        integer += to_string(l_numerator / l_denominator);
        mod = l_numerator % l_denominator;
        if (mod)
            integer += '.';
        while (mod)
        {
            if (map.find(mod) != map.end())
            {
                decimal.insert(map[mod], "(");
                decimal.push_back(')');
                break;
            }
            map[mod] = i++;
            mod *= 10;
            decimal += '0' + mod / l_denominator;
            mod %= l_denominator;
        }
        return integer + decimal;
    }
};

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (denominator == 0)
            return "NaN";
        if (numerator == 0)
            return "0";  // so we won't have "-0"
        string integer, decimal;
        long long numeratorL = numerator;
        long long denominatorL = denominator;
        // mod can only be -2147483647 to 2147483646, use int
        unordered_map<int, int> divisor;  // mod paired with the pos where its result will be at
        numeratorL = abs(numeratorL);
        denominatorL = abs(denominatorL);
        // mod needs to *10, so also long long
        long long mod = numeratorL % denominatorL, i = 0, j;
        if (numerator < 0 ^ denominator < 0)
            integer = "-";
        integer += to_string(numeratorL / denominatorL);
        if (mod)
            decimal = ".";

        while (mod)
        {
            if (divisor.find(mod) != divisor.end())
            {
                j = divisor[mod];
                decimal = decimal.substr(0, j) + "(" + decimal.substr(j) + ")";
                break;
            }
            divisor[mod] = ++i;
            mod *= 10;
            decimal += to_string(mod / denominatorL);
            mod %= denominatorL;
        }

        return integer + decimal;
    }
};

int main()
{
    Solution2 s;
    s.fractionToDecimal(-1, INT_MIN);
}