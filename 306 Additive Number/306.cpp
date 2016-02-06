/*

Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers. 
Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

For example:
"112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
    1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

"199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
    1 + 99 = 100, 99 + 100 = 199

Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.

Follow up:
How would you handle overflow for very large input integers?

*/

#include <string>
using namespace std;

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int n = num.length();
        for (int i = 1; i <= n / 2; ++i)  // i, j are length
            for (int j = 1; j <= (n - i) / 2; ++j)  // i + j won't == n, so won't return true with only two numbers
                if (isValid(num, 0, i, j))
                    return true;
        return false;
    }

private:
    bool isValid(string& num, int start, int i, int j) {
        if (start + i + j == num.length())  // but shouldn't return true the first round (with only two numbers)
            return true;

        if (i > 1 && num[start] == '0' || j > 1 && num[start + i] == '0')
            return false;

        string sum = strAdd(num.substr(start, i), num.substr(start + i, j));
        if (num.compare(start + i + j, sum.length(), sum) == 0 && isValid(num, start + i, j, sum.length()))
            return true;

        return false;
    }

    string strAdd(string num1, string num2) {
        string result;
        int i = num1.length() - 1, j = num2.length() - 1, carry = 0;
        while (i >= 0 || j >= 0)
        {
            int sum = (i >= 0 ? num1[i--] - '0' : 0) + (j >= 0 ? num2[j--] - '0' : 0) + carry;
            if (sum > 9)
            {
                sum -= 10;
                carry = 1;
            }
            else
                carry = 0;
            result = char('0' + sum) + result;
        }
        if (carry)
            result = '1' + result;

        return result;
    }
};