/*

This is a follow up of Shortest Word Distance. 
The only difference is now you are given the list of words 
and your method will be called repeatedly many times with different parameters. How would you optimize it?

Design a class which receives a list of words in the constructor, 
and implements a method that takes two words word1 and word2 
and return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = ¡°coding¡±, word2 = ¡°practice¡±, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

*/

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class WordDistance {
public:
    WordDistance(vector<string>& words) {
        for (int i = 0; i < words.size(); ++i)
            indices[words[i]].push_back(i);
    }

    int shortest(string word1, string word2) {
        int dist = INT_MAX, size1 = indices[word1].size(), size2 = indices[word2].size(), i = 0, j = 0;
        // O(m + n) instead of O(mn), since each indices vector is sorted, we only move the smaller one up
        while (i < size1 && j < size2)
        {
            int idx1 = indices[word1][i], idx2 = indices[word2][j];
            if (idx1 < idx2)
            {
                dist = min(dist, idx2 - idx1);
                ++i;
            }
            else
            {
                dist = min(dist, idx1 - idx2);
                ++j;
            }
        }
        return dist;
    }
private:
    unordered_map<string, vector<int>> indices;
};


// Your WordDistance object will be instantiated and called as such:
// WordDistance wordDistance(words);
// wordDistance.shortest("word1", "word2");
// wordDistance.shortest("anotherWord1", "anotherWord2");