/*

Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
     ...
    Z -> 26
    AA -> 27
    AB -> 28

*/

#include <string>
using namespace std;

class Solution {
public:
    int titleToNumber(string s) {
        int result = 0;
        for (auto c : s)
            result = result * 26 + (c - '@');  // or (c - 'A' + 1)
        return result;
    }
};