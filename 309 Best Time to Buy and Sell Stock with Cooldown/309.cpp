/*

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. 

You may complete as many transactions as you like 
(ie, buy one and sell one share of the stock multiple times) with the following restrictions:

1. You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

2. After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)

Example:
    prices = [1, 2, 3, 0, 2]
    maxProfit = 3
    transactions = [buy, sell, cooldown, buy, sell]

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit, profit1 = 0, profit2 = 0, balance, balance1 = INT_MIN;
        for (int price : prices)
        {
            balance = max(profit2 - price, balance1);  // in the middle of a transaction
            profit = max(balance1 + price, profit1);   // after a transaction, don't consider same day transaction
            profit2 = profit1;
            profit1 = profit;
            balance1 = balance;
        }
        return profit1;
    }
};