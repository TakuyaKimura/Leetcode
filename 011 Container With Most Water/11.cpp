/*

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int result = 0, area, left = 0, right = height.size() - 1;
        while (left < right)
        {
            area = (right - left) * min(height[left], height[right]);
            result = max(result, area);
            if (height[left] < height[right])
                ++left;  // left pairing with any other won't create larger area
            else
                --right;
        }
        return result;
    }
};