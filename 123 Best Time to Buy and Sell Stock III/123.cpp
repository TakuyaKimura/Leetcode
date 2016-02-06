/*

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size(), result = 0, valley = INT_MAX, peak = INT_MIN;
        vector<int> leftProfit(n + 2, 0), rightProfit(n + 2, 0);

        for (int i = 0; i < n; ++i)
        {
            valley = min(valley, prices[i]);
            leftProfit[i + 1] = max(prices[i] - valley, leftProfit[i]);
        }

        for (int i = n - 1; i >= 0; --i)
        {
            peak = max(peak, prices[i]);
            rightProfit[i + 1] = max(peak - prices[i], rightProfit[i + 1]);
            result = max(result, leftProfit[i + 1] + rightProfit[i + 1]);
        }

        return result;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0)
            return 0;
        int valley = prices[0];
        vector<int> leftProfit(n, 0);   // must sell on or before day i
        int peak = prices[n - 1];
        vector<int> rightProfit(n, 0);  // must buy on or after day i

        // first transaction
        for (int i = 1; i < n; ++i)
        {
            valley = min(valley, prices[i]);
            leftProfit[i] = max(prices[i] - valley, leftProfit[n - 1]);  // max(sell on day i, no transaction on day i)
        }

        int maxProfit = leftProfit[n - 1];

        // second transaction
        for (int i = n - 2; i >= 0; --i)
        {
            peak = max(peak, prices[i]);
            rightProfit[i] = max(peak - prices[i], rightProfit[i + 1]);  // max(buy on day i, no transaction on day i)
            maxProfit = max(maxProfit, rightProfit[i] + leftProfit[i]);
        }

        return maxProfit;
    }
};