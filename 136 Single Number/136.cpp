/*

Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

*/

#include <unordered_set>
using namespace std;
 
// O(1) space, bit manipulation
class Solution2 {
public:
    int singleNumber(vector<int>& nums) {
        int x = 0;
        for (auto num : nums)
            x ^= num;
        return x;
    }
};

// O(n) extra space
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int> set;
        for (auto& num : nums)
            if (set.find(num) == set.end())
                set.insert(num);
            else
                set.erase(num);
        return *set.begin();
    }
};