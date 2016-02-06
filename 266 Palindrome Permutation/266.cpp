/*

Given a string, determine if a permutation of the string could form a palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.

Hint:
1. Consider the palindromes of odd vs even length. What difference do you notice?

2. Count the frequency of each character.

3. If each character occurs even number of times, then it must be a palindrome. 
   How about character which occurs odd number of times?

*/

#include <string>
#include <bitset>
using namespace std;

class Solutions2 {
    bool canPermutePalindrome(string s) {
        bitset<256> b;
        for (char c : s)
            // b[c].flip();  // both are correct
            b.flip(c);
        return b.count() < 2;
    }
};

class Solution {
public:
    bool canPermutePalindrome(string s) {
        bool count[128] = { false }, oneOdd = false;
        for (char c : s)
            count[c] = !count[c];
        for (bool cnt : count)
            if (cnt)
                if (oneOdd)
                    return false;
                else
                    oneOdd = true;
        return true;
    }
};