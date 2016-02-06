/*

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example 
to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, 
return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. 
If it is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. 
So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. 
Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. 
Another correct ordering is[0,2,1,3].


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

// DFS, 484ms
// fill from the back with the nodes that are finished being explored
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> neighbors(numCourses);  // adjacency list
        vector<int> result(numCourses);
        int order = numCourses - 1;  // label

        for (auto& p : prerequisites)
            neighbors[p.second].push_back(p.first);  // second is the prereq

        vector<char> visited(numCourses, 0);  // not explored yet

        for (int node = 0; node < numCourses; ++node)
            if (visited[node] == 0 && isCycle(neighbors, node, visited, result, order))
                return vector<int>();

        return result;
    }

private:
    bool isCycle(vector<vector<int>>& neighbors, int node, vector<char>& visited, vector<int>& result, int& order) {
        visited[node] = 1;  // exploring
        for (int neighbor : neighbors[node])
            if (visited[neighbor] == 1 || visited[neighbor] == 0 && isCycle(neighbors, neighbor, visited, result, order))
                return true;

        visited[node] = 2;       // finished
        result[order--] = node;  // put finished node from the back, decrement "order"
        return false;
    }
};

// BFS, 480ms
// start from the source nodes, because it's easier to remove all its edges (being the head of the edges)
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> neighbors(numCourses);
        vector<int> indegrees(numCourses, 0), result(numCourses);
        queue<int> sources;
        int s, numEdges = prerequisites.size(), order = 0;

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
            result[order++] = s;
            sources.pop();
            for (int neighbor : neighbors[s])
            {
                if (--indegrees[neighbor] == 0)
                    sources.push(neighbor);
                --numEdges;
            }
        }
        return numEdges == 0 ? result : vector<int>();
    }
};