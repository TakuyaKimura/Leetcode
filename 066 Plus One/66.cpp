/*

Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.

*/

#include <vector>
using namespace std;

// fast, only need to check for 9
// only need to add an entry when all digits are 9
class Solution3 {
public:
    vector<int> plusone(vector<int> &digits)
    {
        int n = digits.size();
        for (int i = n - 1; i >= 0; --i)
            if (digits[i] == 9)
                digits[i] = 0;
            else
            {
                ++digits[i];
                return digits;
            }
        digits[0] = 1;
        digits.push_back(0);
        return digits;
    }
};

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int n = digits.size(), carry = 0, sum;
        digits[n - 1] += 1;
        for (int i = n - 1; i >= 0; i--)
        {
            sum = digits[i] + carry;
            digits[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry)
        {
            digits.push_back(digits[n - 1]);  //
            for (int i = n - 1; i > 0; i--)   //
                digits[i] = digits[i - 1];    //
            digits[0] = carry;                // digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};

class Solution2 {
public:
    vector<int> plusOne(vector<int> &digits) {
        for (int i = digits.size() - 1; i >= 0; i--)
        {
            if (digits[i] != 9)
            {
                digits[i] ++;
                break;
            }
            digits[i] = 0;
        }
        if (digits[0] == 0)
            digits.insert(digits.begin(), 1);
        return digits;
    }
};