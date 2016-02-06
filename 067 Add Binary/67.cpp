/*

Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".

*/

#include <string>
using namespace std;

// write the sum into the longer one of the inputs
class Solution2 {
public:
    string addBinary(string a, string b) {
        if (a.length() < b.length())
            swap(a, b);
        int i = a.length(), j = b.length();
        while (i--)
        {
            if (j)
                a[i] += b[--j] & 1;  // '0' is 48, '1' is 49
            if (a[i] > '1')
            {
                a[i] -= 2;
                if (i)
                    ++a[i - 1];
                else
                    a = '1' + a;
            }
        }
        return a;
    }
};

class Solution {
public:
    string addBinary(string a, string b) {
        int carry = 0, i = a.length() - 1, j = b.length() - 1;
        string result;
        while (i >= 0 || j >= 0 || carry)
        {
            carry += (i >= 0 ? a[i--] - '0' : 0);
            carry += (j >= 0 ? b[j--] - '0' : 0);
            result = char('0' + carry % 2) + result;
            carry /= 2;
        }
        return result;
    }
};