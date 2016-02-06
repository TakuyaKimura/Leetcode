/*

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. 
Could you implement it using only constant extra space complexity?

*/

#include <vector>
#include <numeric>  // for accumulate
#include <iostream>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size(), x = 0;
        for (int i = 0; i < n; ++i)
            x = x ^ i ^ nums[i];
        return x ^ n;
    }
};

class Solution2 {
public:
    int missingNumber(vector<int>& nums) {
        int x = 0, i = 0;
        for (int num : nums)
            x ^= ++i ^ num;
        return x;
    }
};

class Solution3 {
public:
    int missingNumber(vector<int>& nums) {
        long n = nums.size();
        return n * (n + 1) / 2 - accumulate(begin(nums), end(nums), 0);  // overflow might give wrong answer - "/2" is to right shift
    }
};

class Solution4 {
public:
    int missingNumber(vector<int>& nums) {
        int miss = 0, i = 0;
        for (int num : nums)
            miss += ++i - num;  // it's OK to overflow - won't give wrong answer
        return miss;
    }
};

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int i = 0;
        return accumulate(nums.begin(), nums.end(), 0, [&](int x, int y){return (x - y + ++i); });  // OK to overflow
        // Binary operation takes an element of type T as first argument (initial value is the value of init)
        // and an element in the range as second, 
        // and returns a value that can be assigned to type T (init).
    }
};

int main()
{   
    // max_size: 1073741823
    cout << vector<int>().max_size();
}