/*

The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. 

A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

    00 - 0
    01 - 1
    11 - 3
    10 - 2

Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.

*/

#include <vector>
using namespace std;

// every solution should have O(2^n) time complexity
// because there are 2^n entries to fill in
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result{ 0 };
        int pow2 = 1, i, j;
        for (i = 0; i < n; ++i)
        {
            for (j = pow2 - 1; j >= 0; --j)
                result.push_back(result[j] + pow2);
            pow2 <<= 1;
        }
        return result;
    }
};

// same idea
class Solution2 {
public:
    vector<int> grayCode(int n) {
        vector<int> result(1 << n, 0);
        for (int i = 0, pow2 = 1; i < n; ++i, pow2 <<= 1)
            for (int j = pow2 - 1, k = j + 1; j >= 0; --j, ++k)
                result[k] = result[j] | pow2;
        return result;
    }
};

class Solution3 {
public:
    vector<int> grayCode(int n) {
        int size = 1 << n;
        vector<int> result(size);
        for (int i = 0; i < size; ++i)
            result[i] = i >> 1 ^ i;  // taken from Wiki
        return result;
    }
};