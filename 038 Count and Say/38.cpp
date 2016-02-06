/*

The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.

*/

#include <string>
using namespace std;

// note: there can't be 1111, 2222, or 3333
// so the count won't be larger than 3, only 1, 2, 3 are gonna be used

class Solution2 {
public:
    string countAndSay(int n) {
        if (n == 0)
            return "";
        string result = "1";
        int len, count;
        while (--n)
        {
            len = result.length();
            count = 1;
            while (len--)  // do it backwards, so the index is still correct after replacing
            {
                if (len && result[len] == result[len - 1])
                    ++count;
                else
                {
                    result.replace(len, count - 1, 1, '0' + count);  // replacing 0 character with 1 is the same as insert
                    count = 1;
                }
            }
        }
        return result;
    }
};

class Solution {
public:
    string countAndSay(int n) {
        if (n < 1)
            return "";
        string result = "1";
        int count, m, i;
        char pre;
        string temp;
        while (--n)
        {
            m = result.length(), i = 0;
            temp = result;
            result.clear();
            while (i < m)
            {
                pre = temp[i++];
                count = 1;
                while (i < m && temp[i] == pre)
                {
                    ++count;
                    ++i;
                }
                result.append(1, '0' + count);
                result += pre;
            }
        }
        return result;
    }
};