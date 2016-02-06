/*

Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

Hint:
Could you do it in-place with O(1) extra space?

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> copy(n);
        for (int i = 0; i < n; ++i)
            copy[i] = nums[i];
        for (int i = 0; i < n; ++i)
            nums[(i + k) % n] = copy[i];
    }
};

class Solution2 {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        nums.insert(nums.begin(), nums.end() - k, nums.end());
        nums.erase(nums.end() - k, nums.end());
    }
};

class Solution3 {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

// Every swap will put one number into its correct position, so the running time is O(n)
// For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] should be rotated to [5,6,7,1,2,3,4]
// After first round, the array is [5,6,7,1,2,3,4], the first 3 elements are in their place, n=4
// After second round, the next 3 elements are in place [5,6,7,1,2,3,4], n=1
class Solution4 {
public:
    void rotate(vector<int>& nums, int k) {
        for (int start = 0, n = nums.size(); k %= n; n -= k, start += k)
            for (int i = 0; i < k; ++i)
                swap(nums[start + i], nums[start + i + n - k]);
    }
};

// see discussion for more solutions
// gcd