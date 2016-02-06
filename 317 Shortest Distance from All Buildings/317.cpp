/*

You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. 

You are given a 2D grid of values 0, 1 or 2, where:

    Each 0 marks an empty land which you can pass by freely.
    Each 1 marks a building which you cannot pass through.
    Each 2 marks an obstacle which you cannot pass through.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):

    1 - 0 - 2 - 0 - 1
    |   |   |   |   |
    0 - 0 - 0 - 0 - 0
    |   |   |   |   |
    0 - 0 - 1 - 0 - 0

The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal. So return 7.

Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.

*/

#include <vector>
#include <queue>
using namespace std;

// BFS
// when looking at the first building, we only check the place with label 0, and mark them as -1 (reachable from 1st builidng)
// when looking at the second building, we only check the place with label -1, and mark them as -2
// so that the same building won't be visited twice
// and in the last round we only check the places reachable from every building
// and only take the min distance from these places
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
		int m = grid.size(), n = m ? grid[0].size() : 0, minDist = -1, order = 0;
		vector<vector<int>> dist(m, vector<int>(n, 0));
		int dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (grid[i][j] == 1)
				{
					minDist = -1;   // actually only in the last round (for the last building) is effective
					int level = 1;  // this is the distance to the current building
					queue<pair<int, int>> q;
					q.push(make_pair(i, j));
					while (!q.empty())
					{
						int size = q.size();
						while (size--)
						{
							auto ij = q.front();
							q.pop();
							for (int k = 0; k < 4; ++k)
							{
								int ni = ij.first + dx[k], nj = ij.second + dy[k];
								if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == order)  // only those are reachable from every building
								{
									q.push(make_pair(ni, nj));
									grid[ni][nj] = order - 1;  // so it won't be visited again for this building, but will be visited for the next building
									dist[ni][nj] += level;
									if (minDist > dist[ni][nj] || minDist == -1)
										minDist = dist[ni][nj];
								}
							}
						}
						++level;
					}
					--order;
				}

		return minDist;
    }
};