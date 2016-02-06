/*

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, 
where "adjacent" cells are those horizontally or vertically neighboring. 
The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

    [
        ['o','a','a','n'],
        ['e','t','a','e'],
        ['i','h','k','r'],
        ['i','f','l','v']
    ]

Return ["eat","oath"].

Note:
You may assume that all inputs are consist of lowercase letters a-z.

Hint:
1. You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?

2. If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. 
   What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? 
   How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.

*/

#include <vector>
#include <string>
using namespace std;

class Solution3 {
public:
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> result;
		m = board.size();
		n = m ? board[0].size() : 0;

		Trie trie;
		for (int i = 0; i < words.size(); ++i)
			trie.insert(words, i);

		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				dfs(board, words, result, i, j, trie.root);

		return result;
	}

	class TrieNode {
	public:
		TrieNode* children[26];
		int idx;

		TrieNode() : idx(-1) {
			memset(children, 0, sizeof(children));
		}
	};

	class Trie {
	public:
		TrieNode* root;

		Trie() {
			root = new TrieNode();
		}

		~Trie() {
			destroy(root);
		}

		void insert(vector<string>& words, int i) {
			TrieNode* node = root;
			for (char c : words[i])
			{
				if (!node->children[c - 'a'])
					node->children[c - 'a'] = new TrieNode();
				node = node->children[c - 'a'];
			}
			node->idx = i;
		}

	private:
		void destroy(TrieNode* node) {
			for (auto child : node->children)
				if (child)
					destroy(child);
			delete node;
		}
	};

private:
	int m, n;
	void dfs(vector<vector<char>>& board, vector<string>& words, vector<string>& result, int i, int j, TrieNode* node) {
		if (i < 0 || i == m || j < 0 || j == n || board[i][j] == '\0')
			return;

		char c = board[i][j];
		node = node->children[c - 'a'];

		if (!node)
			return;  // not prefix in all the words, early termination

		if (node->idx != -1)
		{
			result.push_back(words[node->idx]);
			node->idx = -1;  // so we won't find it again
		}

		board[i][j] = '\0';  // mark as used in the current string, note: don't change it too early before the above "return"

		dfs(board, words, result, i - 1, j, node);
		dfs(board, words, result, i + 1, j, node);
		dfs(board, words, result, i, j - 1, node);
		dfs(board, words, result, i, j + 1, node);

		board[i][j] = c;
	}
};


class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        m = board.size();
        n = m ? board[0].size() : 0;
        Trie trie;
        for (auto& word : words)
            trie.insert(word);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                dfs(board, result, trie.root, "", i, j);
        return result;
    }

    // Your Trie object will be instantiated and called as such:
    // Trie trie;
    // trie.insert("somestring");
    // trie.search("key");
    class TrieNode {
    public:
        TrieNode() {
            memset(children, 0, sizeof(children));
            isWord = false;
        }
        TrieNode *children[26];
        bool isWord;
    };

    class Trie {
    public:
        TrieNode* root;
        Trie() {
            root = new TrieNode();
        }

        ~Trie() {
            destroy(root);
        }

        // Inserts a word into the trie.
        void insert(string word) {
            TrieNode *node = root;
            for (auto c : word)
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
            for (auto c : word)
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
            for (auto c : prefix)
            {
                if (!node->children[c - 'a'])
                    return false;
                node = node->children[c - 'a'];
            }
            return true;
        }

    private:
        void destroy(TrieNode *node) {
            for (auto c : node->children)
                if (c)
                    destroy(c);
            delete node;
        }
    };


private:
    int m, n;
    void dfs(vector<vector<char>>& board, vector<string>& result, TrieNode* node, string str, int row, int col) {
        if (node->isWord)
        {
            result.push_back(str);
            node->isWord = false;  // so it won't be found again
        }  // don't return, should continue, if there's "abc" and "abcd"

        if (row == -1 || col == -1 || row == m || col == n || board[row][col] == '\0')
            return;

        char c = board[row][col];
        TrieNode* child = node->children[c - 'a'];
        if (!child)
            return;
        board[row][col] = '\0';
        str += c;
        dfs(board, result, child, str, row - 1, col);
        dfs(board, result, child, str, row + 1, col);
        dfs(board, result, child, str, row, col - 1);
        dfs(board, result, child, str, row, col + 1);

        board[row][col] = c;
    }
};


class Solution2 {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        m = board.size();
        n = m ? board[0].size() : 0;
        Trie trie;
        int wordCount = words.size(), i, j;  // reuse i and j reduce runtime from 60ms to 48ms!!
        for (i = 0; i < wordCount; ++i)
            trie.insert(words[i], i);
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                dfs(board, result, trie.root, words, i, j);
        return result;
    }

    // Your Trie object will be instantiated and called as such:
    // Trie trie;
    // trie.insert("somestring");
    // trie.search("key");
    class TrieNode {
    public:
        TrieNode() {
            memset(children, 0, sizeof(children));
            isWord = false;
            idx = -1;
        }
        TrieNode *children[26];
        bool isWord;
        int idx;
    };

    class Trie {
    public:
        TrieNode* root;
        Trie() {
            root = new TrieNode();
        }

        ~Trie() {
            destroy(root);
        }

        // Inserts a word into the trie.
        void insert(string word, int idx) {
            TrieNode *node = root;
            for (auto c : word)
            {
                if (!node->children[c - 'a'])
                    node->children[c - 'a'] = new TrieNode();
                node = node->children[c - 'a'];
            }
            node->isWord = true;
            node->idx = idx;
        }

        // Returns if the word is in the trie.
        bool search(string word) {
            TrieNode *node = root;
            for (auto c : word)
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
            for (auto c : prefix)
            {
                if (!node->children[c - 'a'])
                    return false;
                node = node->children[c - 'a'];
            }
            return true;
        }

    private:
        void destroy(TrieNode *node) {
            for (auto c : node->children)
                if (c)
                    destroy(c);
            delete node;
        }
    };


private:
    int m, n;
    void dfs(vector<vector<char>>& board, vector<string>& result, TrieNode* node, vector<string>& words, int row, int col) {
        if (board[row][col] == '\0')
            return;

        char c = board[row][col];
        TrieNode* child = node->children[c - 'a'];
        if (!child)
            return;
        // without calling next round
        if (child->isWord)
        {
            result.push_back(words[child->idx]);  // store index at leaf node, instead of passing string around
            child->isWord = false;
        }

        board[row][col] = '\0';
        // without calling next round
        if (row > 0)
            dfs(board, result, child, words, row - 1, col);
        if (row < m - 1)
            dfs(board, result, child, words, row + 1, col);
        if (col > 0)
            dfs(board, result, child, words, row, col - 1);
        if (col < n - 1)
            dfs(board, result, child, words, row, col + 1);

        board[row][col] = c;
    }
};