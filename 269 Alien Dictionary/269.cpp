/*

There is a new alien language which uses the latin alphabet. 

However, the order among letters are unknown to you. 

You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. 

Derive the order of letters in this language.

For example,
Given the following words in dictionary,

    [
        "wrt",
        "wrf",
        "er",
        "ett",
        "rftt"
    ]

The correct order is: "wertf".

Note:
You may assume all letters are in lowercase.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.

*/

#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

// Topological sort, silimar to Problem 210
// dfs, labelling from the sink nodes
class Solution {
public:
    string alienOrder(vector<string>& words) {
		int n = words.size(), visited[26] = { 0 }, count = 0;
		vector<int> neighbors[26];

		for (string& word : words)
			for (char c : word)
				if (visited[c - 'a'] == 0)  // never appeared
				{
					visited[c - 'a'] = 1;   // not explored
					++count;
				}

		for (int i = 1; i < n; ++i)
		{
			int m = min(words[i - 1].length(), words[i].length());
			for (int j = 0; j < m; ++j)
				if (words[i - 1][j] != words[i][j])
				{
					neighbors[words[i - 1][j] - 'a'].push_back(words[i][j] - 'a');
					break;
				}
		}

		string result(count, ' ');
		int order = count - 1;
		for (int i = 0; i < 26; ++i)
			if (visited[i] == 1 && isCycle(i, neighbors, visited, order, result))
				return "";

		return result;
	}

private:
	bool isCycle(int node, vector<int>(&neighbors)[26], int(&visited)[26], int& order, string& result) {
		visited[node] = 2;  // being explored

		for (int i : neighbors[node])
			if (visited[i] == 2 || visited[i] == 1 && isCycle(i, neighbors, visited, order, result))
				return true;

		visited[node] = 3;  // finished exploring
		result[order--] = 'a' + node;
		return false;
    }
};

// bfs, labelling from the source nodes
// start from the source nodes, because it's easier to remove all its edges (being the head of the edges)
class Solution2 {
public:
	string alienOrder(vector<string>& words) {
		int n = words.size(), used[26] = { 0 }, indegree[26] = { 0 }, count = 0, numEdges = 0, order = 0;
		vector<int> neighbors[26];

		for (string& word : words)
			for (char c : word)
				if (used[c - 'a'] == 0)
				{
					used[c - 'a'] = 1;
					++count;
				}

		for (int i = 1; i < n; ++i)
		{
			int m = min(words[i - 1].length(), words[i].length());
			for (int j = 0; j < m; ++j)
				if (words[i - 1][j] != words[i][j])
				{
					neighbors[words[i - 1][j] - 'a'].push_back(words[i][j] - 'a');
					++indegree[words[i][j] - 'a'];
					++numEdges;
					break;
				}
		}

		string result(count, ' ');
		queue<int> sources;
		for (int i = 0; i < 26; ++i)
			if (used[i] && indegree[i] == 0)
				sources.push(i);

		while (!sources.empty())
		{
			int s = sources.front();
			sources.pop();
			result[order++] = 'a' + s;
			for (int neighbor : neighbors[s])
			{
				if (--indegree[neighbor] == 0)
					sources.push(neighbor);
				--numEdges;
			}
		}

		return numEdges ? "" : result;
	}
};