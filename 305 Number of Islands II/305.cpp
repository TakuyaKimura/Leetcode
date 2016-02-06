/*

A 2d grid map of m rows and n columns is initially filled with water. 

We may perform an addLand operation which turns the water at position (row, col) into a land. 

Given a list of positions to operate, count the number of islands after each addLand operation. 

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 

You may assume all four edges of the grid are all surrounded by water.

Example:

Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].

Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

        0 0 0
        0 0 0
        0 0 0

Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

        1 0 0
        0 0 0   Number of islands = 1
        0 0 0

Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

        1 1 0
        0 0 0   Number of islands = 1
        0 0 0

Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

        1 1 0
        0 0 1   Number of islands = 2
        0 0 0

Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

        1 1 0
        0 0 1   Number of islands = 3
        0 1 0

We return the result as an array: [1, 1, 2, 3]

Challenge:
Can you do it in time complexity O(k log mn), where k is the length of the positions?

*/

#include <vector>
using namespace std;

class Solution {
public:
	vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
		int num = positions.size();
		vector<int> result(num);
		UF uf(m * n);
		for (int k = 0; k < num; ++k)
		{
			int i = positions[k].first, j = positions[k].second, idx = i * n + j;
			uf.addLand(idx);
			if (j > 0 && uf.isLand(idx - 1))  // we can know this by looking at id[p]
				uf.unionP(idx, idx - 1);
			if (j < n - 1 && uf.isLand(idx + 1))
				uf.unionP(idx, idx + 1);
			if (i > 0 && uf.isLand(idx - n))
				uf.unionP(idx, idx - n);
			if (i < m - 1 && uf.isLand(idx + n))
				uf.unionP(idx, idx + n);

			result[k] = uf.getCount();
		}
		return result;
	}

	class UF {
	public:
		UF(int n) : count(0), id(n, -1), weight(n, 0) {}

		void unionP(int p, int q) {
			int i = root(p), j = root(q);
			if (i == j)
				return;
			if (weight[i] < weight[j])
				id[i] = j;
			else if (weight[i] > weight[j])
				id[j] = i;
			else
			{
				id[j] = i;
				++weight[i];
			}
			--count;
		}

		bool connected(int p, int q) {
			return root(p) == root(q);
		}

		bool isLand(int p) {
			return id[p] != -1;
		}

		int getCount() {
			return count;
		}

		void addLand(int p) {
			++count;
			id[p] = p;
		}

	private:
		int count;
		vector<int> id;
		vector<int> weight;

		int root(int p) {
			while (p != id[p])
				p = id[p] = id[id[p]];
			return p;
		}
	};
};

int main() {
	vector<pair<int, int>> positions{ { 0, 0 }, { 0, 1 }, { 1, 2 }, { 2, 1 } };
	Solution s;
	s.numIslands2(3, 3, positions);
}