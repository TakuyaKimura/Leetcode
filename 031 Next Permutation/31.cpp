/*

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 ¡ú 1,3,2
3,2,1 ¡ú 1,2,3
1,1,5 ¡ú 1,5,1

*/

#include <vector>
#include <algorithm>  // next_permutation
using namespace std;

// from the back, find the first number which is not increasing, call it a
// from the back, find the first number which is bigger than a, call it b
// swap a and b, the numbers after the now b (old a's position) are decreasing (increasing from the back)
// so just reverse them
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int j = nums.size() - 1, i = j - 1;
        while (i >= 0 && nums[i] >= nums[i + 1])
            --i;
        if (i >= 0)
        {
            while (nums[j] <= nums[i])
                --j;
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};

class Solution2 {
public:
    void nextPermutation(vector<int>& nums) {
        next_permutation(begin(nums), end(nums));
    }
};

class Solution3 {
public:
    void nextPermutation(vector<int>& nums) {
        auto i = is_sorted_until(nums.rbegin(), nums.rend());
        if (i != nums.rend())
            swap(*i, *upper_bound(nums.rbegin(), i, *i));
        reverse(nums.rbegin(), i);
    }
};

class Solution4 {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 1, k = i;
        while (i > 0 && nums[i - 1] >= nums[i])
            --i;
        for (int j = i; j < k; ++j, --k)
            swap(nums[j], nums[k]);
        if (i > 0)
        {
            k = --i;
            while (nums[k] <= nums[i])
                ++k;
            swap(nums[i], nums[k]);
        }
    }
};

class Solution5 {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 1, k = i, tmp;
        while (i > 0 && nums[i - 1] >= nums[i])
            --i;
        for (int j = i; j < k; ++j, --k)
            tmp = nums[j], nums[j] = nums[k], nums[k] = tmp;
        if (i > 0)
        {
            k = --i;
            while (nums[k] <= nums[i])
                ++k;
            tmp = nums[i], nums[i] = nums[k], nums[k] = tmp;
        }
    }
};