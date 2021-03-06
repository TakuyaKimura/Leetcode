/*

You are given coins of different denominations and a total amount of money amount. 

Write a function to compute the fewest number of coins that you need to make up that amount. 

If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
	coins = [1, 2, 5], amount = 11
	return 3 (11 = 5 + 5 + 1)

Example 2:
	coins = [2], amount = 3
	return -1.

Note:
You may assume that you have an infinite number of each kind of coin.

*/

#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// DP, 132ms
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		int n = coins.size();
		vector<int> dp(amount + 1, amount + 1);
		dp[0] = 0;
		for (int i = 1; i <= amount; ++i)  // amount at outer loop
			for (int j = 0; j < n; ++j)
				if (i >= coins[j])
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
		return dp[amount] > amount ? -1 : dp[amount];
	}
};

// 92ms
class Solution2 {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount + 1, amount + 1);
		dp[0] = 0;
		for (int coin : coins)  // coin at outer loop
			for (int i = coin; i <= amount; ++i)
				dp[i] = min(dp[i], dp[i - coin] + 1);
		return dp[amount] > amount ? -1 : dp[amount];
	}
};

// BFS, 156ms
class Solution3 {
public:
	int coinChange(vector<int>& coins, int amount) {
		if (amount == 0)
			return 0;
		int numCoins = 0;
		queue<int> q;
		q.push(0);
		vector<int> visited(amount, 0);
		visited[0] = 1;
		while (!q.empty())
		{
			++numCoins;
			int size = q.size();
			while (size--)
			{
				int prev = q.front();
				q.pop();
				for (int coin : coins)
				{
					int cur = prev + coin;
					if (cur == amount)
						return numCoins;
					else if (cur < amount && !visited[cur])
					{
						q.push(cur);
						visited[cur] = 1;
					}
				}
			}
		}
		return -1;
	}
};