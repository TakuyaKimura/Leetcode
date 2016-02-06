/*

Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100),

return 964176192 (represented in binary as 00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?

*/

#include <stdint.h>
// bitwise operator precedence:
// << >>   &    ^   |

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0;
        for (int i = 0; i < 32; ++i)
        {
            result = result << 1 ^ n & 1;  // xor is faster than or
            n >>= 1;
        }
        return result;
    }
};

class Solution2 {
public:
    uint32_t reverseBits(uint32_t n) {
        for (int i = 0; i < 16; ++i)
            if (n >> i & 1 ^ n >> 31 - i & 1)  // compare bit0 with bit31, bit1 with bit30, ...
                n ^= 1 << i ^ 1 << 31 - i;     // xor is faster than or
        return n;
    }
};

// for 8-bit binary number abcdefgh, the process is as follows:
// abcdefgh->efghabcd->ghefcdab->hgfedcba
class Solution3 {
public:
    uint32_t reverseBits(uint32_t n) {
        n = n >> 16 ^ n << 16;
        n = (n & 0xff00ff00) >> 8 ^ (n & 0x00ff00ff) << 8;  // 0xf = 1111
        n = (n & 0xf0f0f0f0) >> 4 ^ (n & 0x0f0f0f0f) << 4;
        n = (n & 0xcccccccc) >> 2 ^ (n & 0x33333333) << 2;  // 0xc = 1100  0x3 = 0011
        n = (n & 0xaaaaaaaa) >> 1 ^ (n & 0x55555555) << 1;  // 0xa = 1010  0x5 = 0101
        return n;
    }
};

// If this function is called many times, how would you optimize it?
// do it 4-bit or 8-bit at a time
// build a 2^4 or 2^8 table to store the reverse
class Solution4 {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0, mask = 0xf;
        for (int i = 0; i < 8; ++i)
        {
            result = result << 4 ^ table[mask & n];
            n = n >> 4;
        }
        return result;
    }
private:
    int table[16] { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
};