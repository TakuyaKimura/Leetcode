/*

Given n non-negative integers representing an elevation map where the width of each bar is 1, 
compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

*/

#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Solution2 may be easier to read
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1, result = 0, fillUpTo = 0;  // the level we can safely fill water up to
        while (left < right)
        {
            // there's a higher right wall, it's safe to fill water up to left wall
            if (height[left] < height[right])
            {
                if (height[left] > fillUpTo)
                    fillUpTo = height[left];
                else
                    result += fillUpTo - height[left];
                ++left;
            }
            else
            {
                if (height[right] > fillUpTo)
                    fillUpTo = height[right];
                else
                    result += fillUpTo - height[right];
                --right;
            }
        }
        return result;
    }
};

class Solution2 {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1, result = 0, fillUpTo = 0;
        while (left < right)
        {
            if (height[left] < height[right])
            {
                fillUpTo = max(fillUpTo, height[left]);
                result += fillUpTo - height[left];
                ++left;
            }
            else
            {
                fillUpTo = max(fillUpTo, height[right]);
                result += fillUpTo - height[right];
                --right;
            }
        }
        return result;
    }
};

class Solution3 {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1, solid = 0, total = 0, fillUpTo = 0;
        while (left < right)
        {
            if (height[left] < height[right])
            {
                fillUpTo = max(fillUpTo, height[left]);
                total += fillUpTo;
                solid += height[left];
                ++left;
            }
            else
            {
                fillUpTo = max(fillUpTo, height[right]);
                total += fillUpTo;
                solid += height[right];
                --right;
            }
        }
        return total - solid;
    }
};

// use stack
class Solution4 {
public:
    int trap(vector<int>& height) {
        stack<int> s;
        int n = height.size(), sum = 0, bottom;
        for (int i = 0; i < n; ++i)
        {
            while (!s.empty() && height[s.top()] <= height[i])
            {
                bottom = height[s.top()];
                s.pop();
                if (!s.empty())
                    sum += (i - s.top() - 1) * (min(height[s.top()], height[i]) - bottom);
            }
            s.push(i);
        }
        return sum;
    }
};

// similar to Problem 238 Product of Array Except Self
class Solution5 {
public:
    int trap(vector<int>& height) {
        int n = height.size(), sum = 0;
        // leftMax[i] - the max height we've on height[i - 1]'s left (including itself)
        // rightMax[i] - the max height we've on height[i - 1]'s right (including itself)
        vector<int> leftMax(n + 2, INT_MIN), rightMax(n + 2, INT_MIN);
        for (int i = 1; i <= n; ++i)
            leftMax[i] = max(leftMax[i - 1], height[i - 1]);
        for (int i = n; i > 0; --i)
            rightMax[i] = max(rightMax[i + 1], height[i - 1]);
        for (int i = 1; i <= n; ++i)
            sum += min(leftMax[i], rightMax[i]) - height[i - 1];  // take the min 
        return sum;
    }
};