/*

There is a fence with n posts, each post can be painted with one of the k colors.

You have to paint all the posts such that no more than two adjacent fence posts have the same color.

Return the total number of ways you can paint the fence.

Note:
n and k are non-negative integers.

*/

class Solution {
public:
    int numWays(int n, int k) {
        if (n == 0)
            return 0;
        // where the previous two colors were the same or not
        int diff = k, same = 0, temp;
        for (int i = 1; i < n; ++i)
        {
            temp = diff;
            diff = (same + diff) * (k - 1);
            same = temp;  // can't have three same colors in a row, so only the diff ones can be used
        }
        return diff + same;
    }
};