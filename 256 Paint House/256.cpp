/*

There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. 

The cost of painting each house with a certain color is different. 

You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. 

For example, costs[0][0] is the cost of painting house 0 with color red; 
costs[1][2] is the cost of painting house 1 with color green, and so on... 

Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size(), preRed = 0, preBlue = 0, preGreen = 0, curRed, curBlue, curGreen;
        for (int i = 0; i < n; ++i)
        {
            curRed = min(preBlue, preGreen) + costs[i][0];
            curGreen = min(preBlue, preRed) + costs[i][1];
            curBlue = min(preRed, preGreen) + costs[i][2];
            preRed = curRed;
            preGreen = curGreen;
            preBlue = curBlue;
        }
        return min(min(preRed, preBlue), preGreen);
    }
};