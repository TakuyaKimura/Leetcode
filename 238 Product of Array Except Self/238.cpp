/*

Given an array of n integers where n > 1, nums, return an array output 
such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? 
(Note: The output array does not count as extra space for the purpose of space complexity analysis.)

*/

#include <vector>
using namespace std;

// O(n) space
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        vector<int> leftProduct(n, 1);  // ith element is the product of the left i numbers
        vector<int> rightProduct(n, 1); // ith element is the product of the right i numbers
        for (int i = 0; i < n - 1; ++i)
        {
            leftProduct[i + 1] = leftProduct[i] * nums[i];
            rightProduct[i + 1] = rightProduct[i] * nums[n - 1 - i];
        }
        for (int i = 0; i < n; ++i)
            result[i] = leftProduct[i] * rightProduct[n - 1 - i];

        return result;
    }
};

// O(1) extra space, 64ms
class Solution2 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        for (int i = 0, product = 1; i < n; product *= nums[i], ++i)
            result[i] = product;  // now result is the leftProduct
        for (int i = n - 1, product = 1; i >= 0; product *= nums[i], --i)
            result[i] *= product;

        return result;
    }
};

// same idea, 60ms
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size(), i, product;
        vector<int> result(n, 1);
        for (i = 1, product = 1; i < n; ++i)
        {
            product *= nums[i - 1];
            result[i] = product;
        }
        for (i = n - 2, product = 1; i >= 0; --i)
        {
            product *= nums[i + 1];
            result[i] *= product;
        }
        return result;
    }
};