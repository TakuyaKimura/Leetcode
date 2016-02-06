/*

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

*/

#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> charToInt{ { 'I', 1 }, { 'V', 5 }, { 'X', 10 }, { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };
        int pre = 0, cur, result = 0;

        // roman numerals are written from large to small
        // except for IV, IX, XL, XC, CD, CM
        // so we can start from the end
        // or start from the beginning, but substract 2*pre
        for (int i = s.length() - 1; i >= 0; --i)
        {
            cur = charToInt[s[i]];
            if (cur >= pre)
                result += cur;
            else
                result -= cur;

            pre = cur;
        }
        return result;
    }
};