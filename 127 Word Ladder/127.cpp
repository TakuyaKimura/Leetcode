/*

Given two words (beginWord and endWord), and a dictionary's word list, 

find the length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the word list

For example,

Given:
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot","dot","dog","lot","log"]

As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.

*/

#include <string>
#include <unordered_set>
#include <deque>
#include <iostream>
using namespace std;

// double BFS
// search from both ends, until meet each other
// so the frontier wouldn't grow too broad

class Solution4 {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        string word;
        char orig;
        int len = 1;
        unordered_set<string> s1, s2;
        s1.insert(beginWord);
        s2.insert(endWord);
        wordList.erase(beginWord);
        wordList.erase(endWord);
        while (!s1.empty())  // s1 is the smaller (or equal) one
        {
            ++len;
            unordered_set<string> s3;

			//for (string word : s1)  // can't use reference type, "qualifiers dropped in binding reference of type string& to initializer of type const string"
            for (auto it = s1.begin(); it != s1.end(); ++it)
            {
                word = *it;
                for (auto ch = word.begin(); ch != word.end(); ++ch)
                {
                    orig = *ch;
                    for (*ch = 'a'; *ch <= 'z'; ++(*ch))
                    {
                        if (*ch == orig)
                            continue;
                        if (s2.find(word) != s2.end())
                            return len;
                        if (wordList.find(word) != wordList.end())
                        {
                            s3.insert(word);
                            wordList.erase(word);
                        }
                    }
                    *ch = orig;
                }
            }
            swap(s1, s3);  // constant time
            if (s1.size() > s2.size())
                swap(s1, s2);
        }
        return 0;
    }
};

class Solution3 {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        unordered_set<string> words1, words2;
        words1.insert(beginWord);
        words2.insert(endWord);
        wordList.erase(beginWord);
        wordList.erase(endWord);
        return ladderLengthHelper(words1, words2, wordList, 1);
    }
private:
    int ladderLengthHelper(unordered_set<string>& words1, unordered_set<string>& words2, unordered_set<string>& wordList, int level) {
        if (words1.empty())
            return 0;
        if (words1.size() > words2.size())
            return ladderLengthHelper(words2, words1, wordList, level);
        unordered_set<string> words3;  // the new layer
        for (auto it = words1.begin(); it != words1.end(); ++it)
        {
            string word = *it;
            for (auto ch = word.begin(); ch != word.end(); ++ch)
            {
                char tmp = *ch;
                for (*ch = 'a'; *ch <= 'z'; ++(*ch))
                {
                    if (*ch == tmp)
                        continue;
                    if (words2.find(word) != words2.end())
                        return level + 1;
                    if (wordList.find(word) != wordList.end())
                    {
                        wordList.erase(word);
                        words3.insert(word);
                    }
                }
                *ch = tmp;
            }
        }
        return ladderLengthHelper(words2, words3, wordList, level + 1);  // put words2 first
    }
};



// use queue (deque) for iterating
// use unordered_set for lookups

class Solution2 {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        int len = beginWord.length(), level = 1, nodesATLevel;  // return the length of the ladder, not # transformation
        string str;
        char orig;
        deque<string> qStart, qEnd, *q1, *q2;
        unordered_set<string> startFrontier, endFrontier, *f1, *f2;

        qStart.push_back(beginWord);
        qEnd.push_back(endWord);
        startFrontier.insert(beginWord);
        endFrontier.insert(endWord);
        wordList.erase(beginWord);  // mark every visited node by removing it from the dict
        wordList.erase(endWord);
        while (!qStart.empty() && !qEnd.empty())
        {
            ++level;
            if (qStart.size() < qEnd.size())
            {
                q1 = &qStart;  // iterate through q1, to match strings in q2
                q2 = &qEnd;
                f1 = &startFrontier;
                f2 = &endFrontier;
            }
            else
            {
                q1 = &qEnd;
                q2 = &qStart;
                f1 = &endFrontier;
                f2 = &startFrontier;
            }
            f1->clear();  // pointer notation
            nodesATLevel = q1->size();
            for (int i = 0; i < nodesATLevel; ++i)
            {
                str = q1->front();
                q1->pop_front();
                for (int j = 0; j < len; ++j)
                {
                    orig = str[j];
                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        //if (c == orig)  // if start == end, length should be 1 or 2??
                        //    continue;
                        str[j] = c;
                        if (f2->find(str) != f2->end())
                            return level;
                        if (wordList.find(str) != wordList.end())
                        {
                            q1->push_back(str);
                            f1->insert(str);
                            wordList.erase(str);  // mark as visited
                        }
                    }
                    str[j] = orig;
                }
            }
        }
        return 0;
    }
};

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        int len = beginWord.length(), level = 1, nodesATLevel;  // return the length of the ladder, not # transformation
        string str;
        char orig;
        deque<string> q;

        q.push_back(beginWord);
        wordList.erase(beginWord);  // mark every visited node by removing it from the dict
        while (!q.empty())
        {
            ++level;
            nodesATLevel = q.size();
            for (int i = 0; i < nodesATLevel; ++i)
            {
                str = q.front();
                q.pop_front();
                for (int j = 0; j < len; ++j)
                {
                    orig = str[j];
                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        //if (c == orig)  // if start == end, length should be 1 or 2??
                        //    continue;
                        str[j] = c;
                        if (str == endWord)
                            return level;
                        if (wordList.find(str) != wordList.end())
                        {
                            q.push_back(str);
                            wordList.erase(str);
                        }
                    }
                    str[j] = orig;
                }
            }
        }
        return 0;
    }
};