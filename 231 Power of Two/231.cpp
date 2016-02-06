/*

Given an integer, write a function to determine if it is a power of two.

*/

// use the n&(n-1) trick
// powers of two are 100..00, n - 1 is 011..11
// except the sign bit being 1
// == has higher precedence than &
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
};