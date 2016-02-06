/*

Given an integer array nums, find the sum of the elements between indices i and j (i ¡Ü j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

    sumRange(0, 2) -> 1
    sumRange(2, 5) -> -1
    sumRange(0, 5) -> -3

Note:
You may assume that the array does not change.
There are many calls to sumRange function.

*/

#include <vector>
using namespace std;

class NumArray {
public:
    NumArray(vector<int>& nums) {
        accu.push_back(0);
        for (int num : nums)
            accu.push_back(accu.back() + num);  // faster than keeping running sum
    }

    int sumRange(int i, int j) {
        return accu[j + 1] - accu[i];
    }
private:
    vector<int> accu;
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);