/*

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. 

You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). 

However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/

#include <vector>
using namespace std;

// same idea, less array access
class Solution2 {
public:
    int maxProfit(vector<int> &prices) {
        int pre = INT_MAX, profit = 0;
        for (auto price : prices)
        {
            if (price > pre)
                profit += price - pre;
            pre = price;
        }
        return profit;
    }
};

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size(), profit = 0;
        for (int i = 0; i < n - 1; ++i)
            if (prices[i + 1] > prices[i])
                profit += prices[i + 1] - prices[i];
        return profit;
    }
};