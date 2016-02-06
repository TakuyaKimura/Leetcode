/*

Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. 

You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

	nums = [
				[9,9,4],
				[6,6,8],
				[2,1,1]
			]
	Return 4
	The longest increasing path is [1, 2, 6, 9].

Example 2:

	nums = [
				[3,4,5],
				[3,2,6],
				[2,2,1]
			]
	Return 4
	The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

*/

#include <vector>
#include <queue>
using namespace std;

// DFS + memoization, 84ms
class Solution {
public:
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int m = matrix.size(), n = m ? matrix[0].size() : 0, len = 0;
		vector<int> length(m * n, 0);  // could also use a 2D vector, same runtime
		int dxy[4][2]{{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				len = max(len, dfs(matrix, i, j, m, n, length, dxy));
		return len;
	}
private:
	int dfs(vector<vector<int>>& matrix, int i, int j, int m, int n, vector<int>& length, int(&dxy)[4][2]) {
		if (length[i * n + j])
			return length[i * n + j];

		int len = 0;
		for (auto& dir : dxy)
		{
			int row = i + dir[0], col = j + dir[1];
			if (row >= 0 && row < m && col >= 0 && col < n && matrix[i][j] < matrix[row][col])
				len = max(len, dfs(matrix, row, col, m, n, length, dxy));
		}
		length[i * n + j] = len + 1;
		return len + 1;
	}
};

// Topological sort, BFS, plucking off from the source nodes, 172ms
class Solution {
public:
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int m = matrix.size(), n = m ? matrix[0].size() : 0, total = m * n, len = 0;
		vector<int> indegree(total, 0);
		vector<vector<int>> neighbors(total);
		queue<int> q;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
			{
				if (i < m - 1)
				{
					if (matrix[i][j] < matrix[i + 1][j])
					{
						++indegree[(i + 1) * n + j];
						neighbors[i * n + j].push_back((i + 1) * n + j);
					}
					else if (matrix[i][j] > matrix[i + 1][j])
					{
						++indegree[i * n + j];
						neighbors[(i + 1) * n + j].push_back(i * n + j);
					}
				}

				if (j < n - 1)
				{
					if (matrix[i][j] < matrix[i][j + 1])
					{
						++indegree[i * n + j + 1];
						neighbors[i * n + j].push_back(i * n + j + 1);
					}
					else if (matrix[i][j] > matrix[i][j + 1])
					{
						++indegree[i * n + j];
						neighbors[i * n + j + 1].push_back(i * n + j);
					}
				}
			}

		for (int i = 0; i < total; ++i)
			if (!indegree[i])
				q.push(i);

		while (!q.empty())
		{
			++len;
			int size = q.size();
			while (size--)
			{
				int source = q.front();
				q.pop();
				for (int neighbor : neighbors[source])
				{
					--indegree[neighbor];
					if (!indegree[neighbor])
						q.push(neighbor);
				}
			}
		}

		return len;
	}
};