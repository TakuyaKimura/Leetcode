/*

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution2 {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size(), preLarge = 1, preSmall = 1, largest = INT_MIN, temp;
        for (int num : nums)
        {
            temp = max(max(preLarge * num, preSmall * num), num);
            preSmall = min(min(preLarge * num, preSmall * num), num);
            preLarge = temp;
            largest = max(largest, preLarge);
        }
        return largest;
    }
};

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size(), num, result = INT_MIN;
        // small[i] = the smalllest product ending at A[i]
        vector<int> small(n + 1, 1);
        // large[i] = the largest product ending at A[i]
        vector<int> large(n + 1, 1);

        for (int i = 0; i < n; ++i)
        {
            num = nums[i];
            large[i + 1] = max(max(large[i] * num, num), small[i] * num);
            small[i + 1] = min(min(small[i] * num, num), large[i] * num);
            result = max(result, large[i + 1]);
        }
        return result;
    }
};