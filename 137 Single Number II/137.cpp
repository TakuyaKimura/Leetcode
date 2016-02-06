/*

Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

*/

#include <vector>
#include <iostream>
using namespace std;

// general case: every element appears k times except for one, which appears p times
// we need some "cutting" mechanism to reinitialize the counter to 0 when the count reaches k
// https://leetcode.com/discuss/31595/detailed-explanation-generalization-bitwise-operation-numbers

// k = 2, p = 1.
// k is 2, then m = 1, we need only one 32-bit integer(x1) as the counter.
// And 2^m == k so we do not even need a mask!
int singleNumber(vector<int>& nums) {
    int x1 = 0;
    for (int i : nums)
        x1 ^= i;
    return x1;
}

// k = 3, p = 1.
// k is 3, then m = 2, we need two 32-bit integers(x2, x1) as the counter.
// And 2^m > k so we do need a mask.
// Write k in its binary form: k = '11', then k1 = 1, k2 = 1, so we have mask = ~(x1 & x2).
int singleNumber(vector<int>& nums) {
    int x1 = 0, x2 = 0, mask = 0;
    for (int i : nums)
    {
        x2 ^= x1 & i;
        x1 ^= i;
        mask = ~(x1 & x2);
        x2 &= mask;
        x1 &= mask;
    }
    return x1;  // p = 1, in binary form p = '01', then p1 = 1, so we should return x1; 
                // if p = 2, in binary form p = '10', then p2 = 1, so we should return x2.
}

// k = 5, p = 3.
// k is 5, then m = 3, we need three 32-bit integers(x3, x2, x1) as the counter.
// And 2^m > k so we need a mask.
// Write k in its binary form: k = '101', then k1 = 1, k2 = 0, k3 = 1, so we have mask = ~(x1 & ~x2 & x3).
int singleNumber(vector<int>& nums) {
    int x1 = 0, x2 = 0, x3 = 0, mask = 0;
    for (int i : nums) 
    {
        x3 ^= x2 & x1 & i;
        x2 ^= x1 & i;
        x1 ^= i;
        mask = ~(x1 & ~x2 & x3);
        x3 &= mask;
        x2 &= mask;
        x1 &= mask;
    }
    return x1;  // p = 3, in binary form p = '011', then p1 = p2 = 1, so we can return either x1 or x2; 
                // But if p = 4, in binary form p = '100', then only p3 = 1, which implies we can only return x3.
}

// ========================================================================================================================

// every element except one appears three times
// 00 -> 01 -> 10 -> 00 -> ....
// so we need two digits to represent these 3 statuses
// when a number appears for the first time, we set its bits in bit1, and clear those bits in bit2
// when a number appears for the second time, we set its bits in bit2, and clear those bits in bit1
// when a number appears for the third time, we clear both bit1 and bit2

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;
        for (auto num : nums)             // self + other = result: off + off = on, off + on = off, on + off = off
        {                                 // first time       second time      thrid time
            ones = (ones ^ num) & ~twos;  // bit1 turns on    bit1 turns off   bit1 stays off
            twos = (twos ^ num) & ~ones;  // bit2 stays off   bit2 turns on    bit2 turns off
        }
        return ones ^ twos;  // if appears once it's set in bit1, if twice bit2
    }
};

class Solution2 {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0, threes = 0;
        for (auto num : nums) {
            twos |= ones & num;
            ones ^= num;
            threes = ones & twos;
            ones &= ~threes;
            twos &= ~threes;
        }
        return ones ^ twos;
    }
};

// let (tempNum,num[0]) be a state. This state can only be (0,0) (0,1) (1,1)
// it's the same idea as the first solution
class Solution3 {
public:
    int singleNumber(vector<int> nums) {
        int tempNum = 0;
        for (auto num : nums)
        {
            tempNum = (tempNum ^ num) & nums[0];
            nums[0] = (nums[0] ^ num) | tempNum;
        }
        return nums[0];
    }
};

// count for each bit
class Solution4 {
public:
    int singleNumber(vector<int>& nums) {
        int count[32] { 0 };
        int i, result = 0;
        for (auto num : nums)
            for (i = 0; num && i < 32; ++i, num >>= 1)
                count[i] += num & 1;
        for (i = 0; i < 32; ++i)
            if (count[i] % 3)  // k times
                result += 1 << i;
        return result;
    }
};

class Solution5 {
public:
    int singleNumber(vector<int>& nums) {
        int count[32] { 0 };
        int result = 0;
        for (int i = 0; i < 32; ++i)
        {
            for (auto num : nums)
                if ((num >> i) & 1)
                    ++count[i];
            result |= ((count[i] % 3) << i);
        }
        return result;
    }
};

int main()
{
    Solution2 s;
    vector<int> nums { 1, 1, 1, 2, 2 };
    cout << s.singleNumber(nums);
}