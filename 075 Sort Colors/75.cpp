/*

Given an array with n objects colored red, white or blue, sort them 
so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, 
then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?

*/

#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int red = 0, blue = nums.size() - 1;  // indices to put the next red or blue
        for (int i = 0; i <= blue; ++i)
        {
            if (nums[i] == 0)
            {
                nums[i] = nums[red];
                nums[red++] = 0;
            }
            else if (nums[i] == 2)
            {
                nums[i--] = nums[blue];  // need to check A[i] again, because it's not checked before
                nums[blue--] = 2;
            }
        }
    }
};