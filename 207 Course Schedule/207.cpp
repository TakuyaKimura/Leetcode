/*

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example 
to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, 
and to take course 0 you should also have finished course 1. So it is impossible.


Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices.

Hints:
1. This problem is equivalent to finding if a cycle exists in a directed graph. 
    If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    
2. Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera https://class.coursera.org/algo-003/lecture/52
    explaining the basic concepts of Topological Sort.
    
3. Topological sort could also be done via BFS. https://en.wikipedia.org/wiki/Topological_sorting#Algorithms

*/

#include <vector>
#include <queue>
using namespace std;

// DFS, O(E + V), 248ms
// O(E) to construct the adjacency list, O(V) to change from 0 to 1, 1 to 2
// could also use unordered_set, but it turns out that it's slower than vector
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> neighbors(numCourses);  // adjacency list

        for (auto& p : prerequisites)
            neighbors[p.second].push_back(p.first);  // second is the prereq

        vector<int> visited(numCourses, 0);  // not explored yet

        for (int node = 0; node < numCourses; ++node)
            if (visited[node] == 0 && isCycle(neighbors, node, visited))
                return false;

        return true;
    }
private:
    bool isCycle(vector<vector<int>>& neighbors, int node, vector<int>& visited) {
        visited[node] = 1;  // exploring
        for (int neighbor : neighbors[node])
            if (visited[neighbor] == 0 && isCycle(neighbors, neighbor, visited) || visited[neighbor] == 1)
                return true;
        visited[node] = 2;  // finished
        return false;
    }
};

// BFS, 248ms
// remove the source node, and all the edges coming from it, repeat until there's no source node
// if there are edges left, then there's a cycle
class Solution2 {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> neighbors(numCourses);
        vector<int> indegrees(numCourses, 0);
        queue<int> sources;
        int s, numEdges = prerequisites.size();

        for (auto& p : prerequisites)
        {
            neighbors[p.second].push_back(p.first);
            ++indegrees[p.first];
        }

        for (int i = 0; i < numCourses; ++i)
            if (indegrees[i] == 0)
                sources.push(i);

        while (!sources.empty())
        {
            s = sources.front();
            sources.pop();
            for (auto& neighbor : neighbors[s])
            {
                --indegrees[neighbor];
                if (indegrees[neighbor] == 0)
                    sources.push(neighbor);
                --numEdges;
            }
        }
        return !numEdges;           
    }
};