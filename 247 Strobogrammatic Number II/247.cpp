/*

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"].

Hint:
Try to use recursion and notice that it should recurse with n - 2 instead of n - 1.

*/

#include <string>
#include <vector>
using namespace std;

// recursive
class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        return helper(n, n);
    }
private:
    vector<string> helper(int n, int total) {
        if (n == 0)
            return{ "" };
        if (n == 1)
            return{ "0", "1", "8" };
        vector<string> result;
        for (auto& str : helper(n - 2, total))
        {
            if (n != total)
                result.push_back("0" + str + "0");
            result.push_back("1" + str + "1");
            result.push_back("6" + str + "9");
            result.push_back("8" + str + "8");
            result.push_back("9" + str + "6");
        }
        return result;
    }
};

// iterative
class Solution2 {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> result, prev;
        if (n % 2)
            result = { "0", "1", "8" };
        else
            result = { "" };
        for (int i = n / 2 - 1; i >= 0; --i)
        {
            prev = result;
            result.clear();
            for (string& str : prev)
            {
                if (i)
                    result.push_back("0" + str + "0");
                result.push_back("1" + str + "1");
                result.push_back("6" + str + "9");
                result.push_back("8" + str + "8");
                result.push_back("9" + str + "6");
            }
        }
        return result;
    }
};