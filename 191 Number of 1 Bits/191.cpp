/*

Write a function that takes an unsigned integer and returns the number of '1' bits it has 
(also known as the Hamming weight).

For example, the 32-bit integer '11' has binary representation 00000000000000000000000000001011, 
so the function should return 3.

*/

#include <stdint.h>

// faster, every iteration delete a 1
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ones = 0;
        while (n)
        {
			n &= n - 1;
            ++ones;
        }
        return ones;
    }
};

// slower, right shift one bit at a time, check if it is 1
class Solution2 {
public:
    int hammingWeight(uint32_t n) {
        int ones = 0;
        while (n)
        {
            if (n & 1)
                ++ones;
            n = n >> 1;  
        }
        return ones;
    }
};