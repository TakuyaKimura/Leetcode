/*

Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
     ...
    26 -> Z
    27 -> AA
    28 -> AB

*/

#include <string>
using namespace std;

class Solution {
public:
    string convertToTitle(int n) {
        string title;
        while (n)
        {
            title = char('A' + --n % 26) + title;  // int + string, won't cast automatically
            n /= 26;
        }
        return title;
    }
};