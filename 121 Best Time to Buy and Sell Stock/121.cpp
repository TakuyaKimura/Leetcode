/*

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), 

design an algorithm to find the maximum profit.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int valley = INT_MAX, profit = 0;
        for (auto price : prices)
        {
            if (price < valley)
                valley = price;
            else if (price - valley > profit)
                profit = price - valley;
        }
        return profit;
    }
};

// dp
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        if (n == 0)
            return 0;
        // lowest value we've seen
        int valley = prices[0];
        // profit[i] = max profit of the first i days
        vector<int> profit(n);
        
        profit[0] = 0;
        for (int i = 1; i < n; ++i)
        {
            valley = min(prices[i], valley);
            profit[i] = max(prices[i] - valley, profit[i - 1]);
        }
        return profit[n - 1];
    }
};