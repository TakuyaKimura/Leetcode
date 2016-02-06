/*

Design a data structure that supports the following two operations:

    void addWord(word)
    bool search(word)

search(word) can search a literal word or a regular expression string containing only letters a-z or .. 
    
A . means it can represent any one letter.

For example:

    addWord("bad")
    addWord("dad")
    addWord("mad")
    search("pad") -> false
    search("bad") -> true
    search(".ad") -> true
    search("b..") -> true

Note:
You may assume that all words are consist of lowercase letters a-z.

Hint:
You should be familiar with how a Trie works. 
If not, please work on this problem: Implement Trie (Prefix Tree) first.

*/

#include <string>
using namespace std;

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() : children(), isWord(false) {}
    TrieNode *children[26];
    bool isWord;
};

class WordDictionary2 {
public:
    WordDictionary2() {
        root = new TrieNode();
    }

    ~WordDictionary2() {
        destroy(root);
    }

    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode *node = root;
        for (char c : word)
        {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->isWord = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return dfs(word, 0, root, word.length());
    }

private:
    TrieNode* root;

    void destroy(TrieNode* node) {
        for (auto child : node->children)
            if (child)
                destroy(child);
        delete node;
    }

    bool dfs(string const& word, int idx, TrieNode* node, int n) {
        if (idx == n)
            return node->isWord;

        char c = word[idx];
        if (c != '.')
        {
            if (!node->children[c - 'a'])
                return false;
            return dfs(word, idx + 1, node->children[c - 'a'], n);
        }
        else
        {
            for (auto child : node->children)
                if (child && dfs(word, idx + 1, child, n))
                    return true;
        }
        return false;
    }
};

class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode();
    }

    ~WordDictionary() {
        destroy(root);
    }

    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode *node = root;
        for (auto c : word)
        {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->isWord = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return dfs(word, 0, root, word.length());
    }

private:
    TrieNode* root;

    void destroy(TrieNode *node) {
        for (auto c : node->children)
            if (c)
                destroy(c);
        delete node;
    }

    bool dfs(string const& word, int idx, TrieNode* node, int n) {
        for (int i = idx; i < n; ++i)
        {
            char c = word[i];
            if (c != '.')
            {
                if (!node->children[c - 'a'])
                    return false;
                node = node->children[c - 'a'];
            }
            else
            {
                for (auto child : node->children)
                    if (child && dfs(word, i + 1, child, n))  // only those not null
                        return true;  // immediately return
                return false;  // if none of them works - easy to forget!!
            }
        }
        return node->isWord;
    }
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");