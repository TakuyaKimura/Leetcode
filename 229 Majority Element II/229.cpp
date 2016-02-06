/*

Given an integer array of size n, find all elements that appear more than |_ n/3 _| times. 

The algorithm should run in linear time and in O(1) space.

Hint:
How many majority elements could it possibly have?

*/

#include <vector>
using namespace std;

// Boyer-Moore Majority Vote Algorithm
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> result;
        int onethird = nums.size() / 3;
        // at most two, don't need to initialize, even if the 2nd one may never be initialized, it won't be used anyway
        int candidate1, candidate2, count1 = 0, count2 = 0;
        for (int num : nums)
            if (!count1)
            {
                candidate1 = num;
                ++count1;
            }
            else if (num == candidate1)  // note the order of the if statements
                ++count1;
            else if (!count2)
            {
                candidate2 = num;
                ++count2;
            }
            else if (num == candidate2)
                ++count2;
            else
            {
                // decrease both, because each one third
                --count1;
                --count2;
            }

        count1 = count2 = 0;
        for (int num : nums)
            if (num == candidate1)
                ++count1;
            else if (num == candidate2)
                ++count2;
        if (count1 > onethird)
            result.push_back(candidate1);
        if (count2 > onethird)
            result.push_back(candidate2);
        return result;
    }
};