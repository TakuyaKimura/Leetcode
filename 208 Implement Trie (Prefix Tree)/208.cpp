/*

Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

*/

#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    // Initialize your data structure here.

    TrieNode() : children(), isWord(false) {}
    //TrieNode() {
    //    memset(children, 0, sizeof(children));
    //    isWord = false;
    //}
    TrieNode* children[26];
    bool isWord;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        destroy(root);
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode *node = root;
        for (char c : word)
        {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->isWord = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *node = root;
        for (char c : word)
        {
            if (!node->children[c - 'a'])
                return false;
            node = node->children[c - 'a'];
        }
        return node->isWord;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *node = root;
        for (char c : prefix)
        {
            if (!node->children[c - 'a'])
                return false;
            node = node->children[c - 'a'];
        }
        return true;
    }

private:
    TrieNode* root;
    void destroy(TrieNode* node) {
        for (auto child : node->children)
            if (child)
                destroy(child);
        delete node;
    }
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");