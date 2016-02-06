/*

Given an array of integers that is already sorted in ascending order, 
find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers 
such that they add up to the target, where index1 must be less than index2. 
Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        while (true)
            if (numbers[i] + numbers[j] == target)
                return{ i + 1, j + 1 };
            else if (numbers[i] + numbers[j] < target)
                ++i;
            else
                --j;
    }
};

// binary search
class Solution2 {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size(), start, end, mid, lookFor;
        for (int i = 0; i < n - 1; ++i)
        {
            lookFor = target - numbers[i];
            start = i + 1;
            end = n - 1;
            //if (lookFor > numbers[end])
            //    continue;
            while (start <= end)
            {
                mid = (start + end) / 2;
                if (numbers[mid] == lookFor)
                    return{ i + 1, mid + 1 };
                if (numbers[mid] < lookFor)
                    start = mid + 1;
                else
                    end = mid - 1;
            }
        }
    }
};