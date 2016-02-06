/*

You are playing the following Flip Game with your friend: 

Given a string that contains only these two characters: + and -, 

you and your friend take turns to flip two consecutive "++" into "--". 

The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

For example, given s = "++++", return true. 

The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Follow up:
Derive your algorithm's runtime complexity.

*/

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <sstream>
using namespace std;

// dfs and backtracking, 128ms
// Suppose originally the board of size N contains only '+' signs, then roughly we have:
// T(N) = T(N-2) + T(N-3) + [T(2) + T(N-4)] + [T(3) + T(N-5)] + ... 
//        [T(N-5) + T(3)] + [T(N-4) + T(2)] + T(N-3) + T(N-2)
//      = 2 * sum(T[i])  (i = 2 ... N-2)
// T(N) = 2^(N-1) satisfies the above equation. Therefore, this algorithm is at least exponential.
class Solution {
public:
    bool canWin(string s) {
        return canWin(s, s.length());
    }
private:
    // guarenteed to win - means if I make this move now, no matter how the other player plays next, he can't win
    // try every move to see if we can win
    bool canWin(string& s, int n) {
        bool wins = false;
        for (int i = 0; i < n - 1; ++i)
            if (s[i] == '+' && s[i + 1] == '+')
            {
                s[i] = s[i + 1] = '-';
                if (!canWin(s, n))  // if the other player isn't guarenteed to win, then we are
                    wins = true;  // don't just return yet
                s[i] = s[i + 1] = '+';
                if (wins)
                    return true;
            }
        return false;
    }
};

// DP, 0ms
// following discussion only applies to normal impartial games (see definition of "normal" and "impartial")
// Suppose x represents a particular arrangement of board, and x0, x1, x2, ... ,xk represent the board after a valid move (all of the possible configurations)
// Sprague-Grundy Function g(x) = FirstMissingNumber(g(x_0), g(x_1), g(x_2), ... , g(x_k))
// If g(x) != 0, then 1P must have a guaranteed winning move from board state x. 
// Otherwise, no matter how 1P moves, 2P must then have a winning move.

// The S-G function of game x = (s1, s2, ..., sk) equals the XOR of all its subgames (after one move) s1, s2, ..., sk. 
// e.g. g((s1, s2, s3)) = g(s1) XOR g(s2) XOR g(s3)

// Calculating g(N) takes O(N) time (N/2 XOR operations plus the O(N) First Missing Number algorithm). 
// And we must calculate from g(1) all the way to g(N). 
// So overall, the algorithm has an O(N^2) time complexity.

class Solution2 {
public:
    bool canWin(string s) {
        int n = s.length(), longest = 0;
        vector<int> lens;  // represent the board configuration by length of consecutive '+'s
        for (int i = 0; i < n - 1; ++i)
            if (s[i] == '+' && s[i + 1] == '+')
            {
                int j = i + 2;
                while (j < n && s[j] == '+')
                    ++j;
                lens.push_back(j - i);
                longest = max(longest, j - i);
                i = j;
            }

        vector<int> g(longest + 1, 0);
        for (int i = 2; i <= longest; ++i)
        {
            unordered_set<int> gsub;
            for (int k1 = 0; k1 < i / 2; ++k1)
                gsub.insert(g[k1] ^ g[i - 2 - k1]);  // one move will produce two subgames
            g[i] = firstMissingNumber(gsub);
        }

        int result = 0;
        for (int len : lens)  // all the subgames
            result ^= g[len];
        return result != 0;
    }

private:
    int firstMissingNumber(unordered_set<int>& set) {
        int n = set.size();
        for (int i = 0; i < n; ++i)
            if (set.count(i) == 0)
                return i;
        return n;
    }
};

class Solution3 {
    bool canWin(string s) {
        replace(s.begin(), s.end(), '-', ' ');
        istringstream in(s);
        int G = 0;
        vector<int> g;
        string t;
        while (in >> t)
        {
            int p = t.length();
            while (g.size() <= p)
            {
                string x = t;
                int i = 0, j = g.size() - 2;
                while (i <= j)
                    x[g[i++] ^ g[j--]] = '-';
                g.push_back(x.find('+'));  // find the first missing number
            }
            G ^= g[p];
        }
        return G;
    }
};