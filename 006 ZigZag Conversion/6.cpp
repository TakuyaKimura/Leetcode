/*

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:
string convert(string text, int nRows);

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

*/

#include <string>
#include <vector>
using namespace std;

// faster
// finish each row before next
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows < 2)
            return s;
        int n = s.length(), row = 0, i = 0, j = 0, stride = 2 * numRows - 2, p, q;
        string t = s;
        for (; i < n; i += stride)
            t[j++] = s[i];
        for (int row = 1; row < numRows - 1; ++row)
        {
            i = row;
            q = 2 * row;
            p = stride - q;
            while (i < n)
            {
                t[j++] = s[i];
                i += p;
                if (i < n)
                {
                    t[j++] = s[i];
                    i += q;
                }
            }
        }
        for (i = numRows - 1; i < n; i += stride)
            t[j++] = s[i];

        return t;
    }
};

// slower
// put each character into different row
class Solution2 {
public:
    string convert(string s, int numRows) {
        if (numRows < 2)
            return s;
        vector<string> strs(numRows);
        // or string *strs = new string[nRows];
        int row = 0, direc = -1;
        for (auto c : s)
        {
            if (row == 0 || row == numRows - 1)
                direc = -direc;

            strs[row] += c;
            row += direc;
        }
        s.clear();
        for (auto& str : strs)
            s += str;
        return s;
    }
};