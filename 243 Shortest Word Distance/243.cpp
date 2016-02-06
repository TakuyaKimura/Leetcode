/*

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = ��coding��, word2 = ��practice��, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int n = words.size(), idx1 = -1, idx2 = -1, dist = INT_MAX;
        for (int i = 0; i < n; ++i)
        {
            if (words[i] == word1)
                idx1 = i;
            else if (words[i] == word2)
                idx2 = i;
            else
                continue;  // don't need to update dist
            if (idx1 != -1 && idx2 != -1)
                dist = min(dist, abs(idx1 - idx2));
        }
        return dist;
    }
};