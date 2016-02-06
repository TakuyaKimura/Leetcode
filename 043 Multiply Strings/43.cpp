/*

Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.

*/

#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = num1.length(), n2 = num2.length(), n3 = n1 + n2, carry, i, j;
        if (!n1 || !n2)
            return "";
        if (num1 == "0" || num2 == "0")
            return "0";
        string result(n3, '0');

        for (j = n2 - 1; j >= 0; --j)
        {
            carry = 0;
            for (i = n1 - 1; i >= 0; --i)
            {
                carry = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry;
                result[i + j + 1] = '0' + carry % 10;
                carry /= 10;
            }
            if (carry)
                result[j] += carry;
        }

        for (i = 0; i < n3 && result[i] == '0'; ++i) {}
        return result.substr(i);
    }
};

// base10 arithmetic is suboptimal. We could use a different base.
// 10^9 is the max 10^n number which fits into 32-bit integer.
// We apply the same logic, but on digits which range from 0 to 10^9-1.
// we have to use 64-bit multiplication here

class Solution2 {
public:
    string multiply(string num1, string num2) {
        if (num1.empty() || num2.empty())
            return "";
        vector<uint32_t> a = toBase1e9(num1);
        vector<uint32_t> b = toBase1e9(num2);
        int n1 = a.size(), n2 = b.size();
        vector<uint32_t> result(n1 + n2, 0);
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                uint64_t t = uint64_t(a[i]) * uint64_t(b[j]) + result[i + j];  // without convert to 64bit is not correct
                result[i + j] = t % 1000000000;  // mod 1e9
                result[i + j + 1] += t / 1000000000;  // div 1e9
            }
        }
        return fromBase1e9(result);
    }

    vector<uint32_t> toBase1e9(string s) {
        vector<uint32_t> v;
        uint32_t value = 0;
        uint32_t factor = 1;
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            value += (*it - '0') * factor;
            if (factor != 100000000)  // != 1e8
                factor *= 10;
            else {
                v.push_back(value);
                value = 0;
                factor = 1;
            }
        }
        if (factor != 1) 
            v.push_back(value);
        return v;
    }

    string fromBase1e9(vector<uint32_t> v) {
        stringstream ss;
        while (v.size() > 1 && v.back() == 0)
            v.pop_back();
        for (auto it = v.rbegin(); it != v.rend(); ++it) {
            ss << *it;
            ss << setw(9) << setfill('0');  // only fill when there's next
        }
        return ss.str();
    }
};

int main()
{
    Solution2 s;
    //cout << s.multiply("0", "0");
    std::cout << "default fill: " << std::setw(10) << std::setfill('*') << 42 << '\n'

    << "setfill('*'): " 
    << 42 << '\n';
}