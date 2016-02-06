/*

Given an array of size n, find the majority element. 

The majority element is the element that appears more than |_ n/2 _| times.

You may assume that the array is non-empty and the majority element always exist in the array.

*/

#include <vector>
using namespace std;

// assume the array is non-empty and the majority element always exist
class Solution {
public:
    int majorityElement(vector<int> &nums) {
        // Boyer-Moore Majority Vote Algorithm
        int count = 0, candidate;
        for (auto& num : nums)
        {
            if (count == 0)
            {
                candidate = num;
                ++count;
            }
            else if (candidate == num)
                ++count;
            else
                --count;
        }
        return candidate;

        //count = 0;
        //for (auto& num : nums)
        //    if (candidate == num)
        //        ++count;
        //if (count > nums.size() / 2)
        //    return candidate;
        //else
        //    return -1;
    }
};