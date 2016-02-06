/*

There are a row of n houses, each house can be painted with one of the k colors. 

The cost of painting each house with a certain color is different. 

You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. 

For example, costs[0][0] is the cost of painting house 0 with color 0; 
costs[1][2] is the cost of painting house 1 with color 2, and so on... 

Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Follow up:
Could you solve it in O(nk) runtime?

*/

#include <vector>
#include <algorithm>
using namespace std;

// for min costs up to the previous house with k different colors, we only need to keep the lowest two
// then for each current house, either add min1 or min2
// but for current house, we can't just keep the lowest two colors (there may be more equals, so need to calculate all)

// O(nk) time, O(k) space
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size(), k = n ? costs[0].size() : 0, pre1 = 0, pre2 = 0, cur1, cur2, cost;
        if (k == 1)
            return n == 1 ? costs[0][0] : INT_MAX;

        vector<int> dp(k, 0);
        for (int i = 0; i < n; ++i)
        {
            cur1 = cur2 = INT_MAX;
            for (int j = 0; j < k; ++j)
            {
                cost = (dp[j] != pre1 ? pre1 : pre2) + costs[i][j];
                if (cost < cur1)
                {
                    cur2 = cur1;
                    cur1 = cost;
                }
                else if (cost < cur2)
                    cur2 = cost;
                dp[j] = cost;
            }
            pre1 = cur1;
            pre2 = cur2;
        }
        return pre1;
    }
};

// O(nk) time, O(1) space
class Solution2 {
public:
    struct myStruct {
        int idx;
        int value;
        myStruct() {}
        myStruct(int i, int cost) : idx(i), value(cost) {}
    };

    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size(), k = n ? costs[0].size() : 0, cost;
        if (k == 1)
            return n == 1 ? costs[0][0] : INT_MAX;
        
        myStruct pre1(-1, 0), pre2(-1, 0), cur1, cur2;
        for (int i = 0; i < n; ++i)
        {
            cur1.value = cur2.value = INT_MAX;
            for (int j = 0; j < k; ++j)
            {
                cost = (j != pre1.idx ? pre1.value : pre2.value) + costs[i][j];
                if (cost < cur1.value)
                {
                    cur2 = cur1;
                    cur1.value = cost;
                    cur1.idx = j;
                }
                else if (cost < cur2.value)
                {
                    cur2.value = cost;
                    cur2.idx = j;
                }
            }
            pre1 = cur1;
            pre2 = cur2;
        }
        return pre1.value;
    }
};