/*

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.

*/

#include <string>
using namespace std;

class Solution {
public:
    bool isStrobogrammatic(string num) {
        for (int i = 0, j = num.length() - 1; i <= j; ++i, --j)
        {
            char a = num[i], b = num[j];
            if (!(a == b && (a == '0' || a == '1' || a == '8')) && !(a == '6' && b == '9') && !(a == '9' && b == '6'))
                return false;
        }
        return true;
    }
};

// couldn't get correct answer in OJ
class Solution2 {
public:
    bool isStrobogrammatic(string num) {
        string str = "00 11 88 696";
        for (int i = 0, j = num.length() - 1; i <= j; ++i, --j)
            if (str.find("" + num[i] + num[j]) == string::npos)
                return false;
        return true;
    }
};