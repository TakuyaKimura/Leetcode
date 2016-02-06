/*

Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

For example, given the range [5, 7], you should return 4.

*/

#include <cmath>

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        while (n > m)
            n &= n - 1;  // clear the least significant set bit
        return n;
    }
};

class Solution2 {
public:
    int rangeBitwiseAnd(int m, int n) {
        int count = 0;
        while (m != n)
        {
            m >>= 1;
            n >>= 1;
            ++count;
        }
        return m << count;
    }
};

class Solution3 {
public:
    int rangeBitwiseAnd(int m, int n) {
        if (m == n)
            return m;
        // The highest bit of 1 in m^n is the highest changed bit
        // to get the bit length, have to add 1 to the logarithm
        int bitlen = log2(m ^ n) + 1;  // If argument is zero, it may cause a pole error (depending on the library implementation)
        return m >> bitlen << bitlen;
    }
};

class Solution4 {
public:
    int rangeBitwiseAnd(int m, int n) {
        if (m == n)
            return m;
        int bitlen = log2(n - m) + 1;
        return m & n & (~0 << bitlen);
    }
};