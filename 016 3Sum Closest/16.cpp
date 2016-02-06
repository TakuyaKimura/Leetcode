/*

Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. 
Return the sum of the three integers. You may assume that each input would have exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// 12ms
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0)
            return 0;
        else if (n == 1)
            return nums[0];
        else if (n == 2)
            return nums[0] + nums[1];
        sort(nums.begin(), nums.end());
        int i, j, k, a, b, c, sum, diff = INT_MAX, closest;
        for (i = 0; i < n - 2; ++i)
        {
            if (i == 0 || nums[i] != a)
            {
                a = nums[i];
                for (j = i + 1, k = n - 1; j < k;)
                {
                    b = nums[j];
                    c = nums[k];
                    sum = a + b + c;
                    if (sum == target)
                        return sum;
                    if (sum < target)
                        while (++j < k && nums[j] == b) {}
                    else
                        while (--k > j && nums[k] == c) {}

                    if (abs(sum - target) < diff)
                    {
                        closest = sum;
                        diff = abs(sum - target);
                    }
                }
            }
        }
        return closest;
    }
};

// 8ms, this solution was found on LeetCode discussion
// but the original solution was not correct
// try it on num = { 1, 4, 6, 10, 15 }, target = 23

// when move "left" to right, find the first element that is greater or equal to target - num[i] - num[right]
// if this is left + 1, then assign it to left
// otherwise, substract 1, and assign it to left, because we may miss one on its left
class Solution2 {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return 0;
        else if (n == 1) return nums[0];
        else if (n == 2) return nums[0] + nums[1];

        int closest, diff = INT_MAX, new_target, sum;
        //if (n == 3) return closest;

        vector<int>::iterator a, b, c, it;

        sort(nums.begin(), nums.end());

        for (a = nums.begin(); a < nums.end() - 2; ++a)
        {
            new_target = target - *a;

            for (b = a + 1, c = nums.end() - 1; b < c;)
            {
                sum = *b + *c;
                if (sum == new_target)
                    return target;

                if (abs(sum + *a - target) < diff)
                {
                    closest = sum + *a;
                    diff = abs(closest - target);
                }

                if (sum > new_target)
                {
                    it = lower_bound(b + 1, c, new_target - *b);
                    if (it == c)
                        --c;
                    else
                        c = it;
                }
                else
                {
                    it = lower_bound(b + 1, c, new_target - *c);
                    if (it == c)
                    {  //cannot find anything big enough
                        b = c - 1;
                        if (abs(*b + *c + *a - target) < abs(closest - target))
                            closest = *b + *c+ *a;
                        break;
                    }
                    else
                        if (it == b + 1)
                            ++b;
                        else
                            b = it - 1;  // substract 1, see explanation above
                }
            }
        }
        return closest;
    }
};

int main()
{
    Solution s;
    //vector<int> num{ 1, 4, 6, 10, 15 };
    //int target = 23;
    vector<int> num{ 0, 0, 0 };
    int target = 1;
    cout << s.threeSumClosest(num, target);
}