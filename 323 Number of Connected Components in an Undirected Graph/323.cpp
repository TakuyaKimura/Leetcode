/*

Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), 
write a function to find the number of connected components in an undirected graph.

Example 1:

	0          3
	|          |
	1 --- 2    4

	Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

Example 2:

	0           4
	|           |
	1 --- 2 --- 3

	Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.

Note:
You can assume that no duplicate edges will appear in edges. 
Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

*/

#include <vector>
#include <queue>
using namespace std;

// DFS
class Solution {
public:
	int countComponents(int n, vector<pair<int, int>>& edges) {
		int numComp = 0;
		vector<vector<int>> neighbors(n);
		vector<bool> visited(n, false);
		for (auto& edge : edges)
		{
			neighbors[edge.first].push_back(edge.second);
			neighbors[edge.second].push_back(edge.first);
		}

		for (int i = 0; i < n; ++i)
			if (!visited[i])
			{
				++numComp;
				dfs(i, neighbors, visited);
			}

		return numComp;
	}
private:
	void dfs(int vertex, vector<vector<int>>& neighbors, vector<bool>& visited) {
		visited[vertex] = true;
		for (int w : neighbors[vertex])
			if (!visited[w])
				dfs(w, neighbors, visited);
	}
};

// BFS
class Solution2 {
public:
	int countComponents(int n, vector<pair<int, int>>& edges) {
		int numComp = 0;
		queue<int> q;
		vector<vector<int>> neighbors(n);
		vector<bool> visited(n, false);
		for (auto& edge : edges)
		{
			neighbors[edge.first].push_back(edge.second);
			neighbors[edge.second].push_back(edge.first);
		}

		for (int i = 0; i < n; ++i)
			if (!visited[i])
			{
				++numComp;
				visited[i] = true;
				q.push(i);
				while (!q.empty())
				{
					int v = q.front();
					q.pop();
					for (int w : neighbors[v])
						if (!visited[w])
						{
							visited[w] = true;
							q.push(w);
						}
				}
			}

		return numComp;
	}
};

// Union-Find
class Solution3 {
public:
	int countComponents(int n, vector<pair<int, int>>& edges) {
		UF uf(n);
		for (auto& edge : edges)
			uf.connect(edge.first, edge.second);
		return uf.getCount();
	}

	class UF {
	public:
		UF(int N) : id(N), rank(N, 0), count(N) {
			for (int i = 0; i < N; ++i)
				id[i] = i;
		}

		int getCount() {
			return count;
		}

		bool connected(int p, int q) {
			return find(p) == find(q);
		}

		void connect(int p, int q) {
			int i = find(p), j = find(q);
			if (i == j)
				return;
			if (rank[i] < rank[j])
				id[i] = j;
			else if (rank[i] > rank[j])
				id[j] = i;
			else
			{
				id[j] = i;
				++rank[i];
			}
			--count;
		}

	private:
		vector<int> id;    // id[i] = parent of i
		vector<int> rank;
		int count;         // number of components

		int find(int p) {
			while (p != id[p])
				p = id[p] = id[id[p]];    // path compression by halving
			return p;
		}
	};
};