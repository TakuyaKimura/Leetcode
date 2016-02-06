/*

Given an array and a value, remove all instances of that value in place and return the new length.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

*/

#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size(), i = 0;
        while (i < n)
            if (nums[i] == val)
                //swap(nums[i], nums[--n]);
                nums[i] = nums[--n];
            else
                ++i;

        return n;
    }
};

// same as previous Solution, less operations
class Solution2 {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        for (int i = 0; i < n; ++i)
            if (nums[i] == val)
            {
                while (n > i && nums[--n] == val) {}
                nums[i] = nums[n];
            }
        return n;
    }
};

class Solution3 {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size(), move = 0;
        for (auto& num : nums)
            if (num != val)
                nums[move++] = num;
        return move;
    }
};

// same as Solution3, less operations
class Solution4 {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size(), move = 0;
        for (int i = 0; i < n; ++i)
            if (nums[i] != val)
            {
                if (move != i)
                    nums[move] = nums[i];
                ++move;
            }
        return move;
    }
};