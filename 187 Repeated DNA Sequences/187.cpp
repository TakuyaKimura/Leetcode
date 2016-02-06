/*

All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". 

When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].

*/

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// for 20-bit hashSum, we could use array (size of 2^20) to speed up
// but for 30-bit hashSum, the array size would be 2^30 = 1073741824  (INTMAX = 2147483647 = 2^31 - 1)

// A = 65, C = 67, G = 71, T = 84
// (s[i] - 'A' + 1) % 5 or (s[i] - 64) % 5
// 1, 3, 2, 0, respectively
// so we only need 2 bits per char, that's 20 bits for a 10-character string
// 2^20 - 1 = (fffff)16 = (1048575)10, this is all the hashSum we may get (2^20)
// use & 0xfffff to get the last 20 bits
// 8ms
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        char hashMap[1048576] = { 0 };  // each hashSum has 3 states: 0, 1, 2(multiple)
        vector<string> ans;
        int len = s.size(), hashNum = 0;

        if (len < 11)
            return ans;

        for (int i = 0; i < 9; ++i)
            hashNum = hashNum << 2 | (s[i] - 64) % 5;

        for (int i = 9; i < len; ++i)
        {
            hashNum = (hashNum << 2 | (s[i] - 64) % 5) & 0xfffff;
            
            if (hashMap[hashNum] == 0)
                ++hashMap[hashNum];
            else if (hashMap[hashNum] == 1)
            {
                ++hashMap[hashNum];
                ans.push_back(s.substr(i - 9, 10));
            }
        }
        return ans;
    }
};

// only difference is how to map ATCG to 2-bit string
// 8ms
class Solution2 {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        char map[26] = { 0 };
        map['C' - 'A'] = 1;
        map['G' - 'A'] = 2;
        map['T' - 'A'] = 3;
        char hashMap[1048576] = { 0 };  // each hashSum has 3 states: 0, 1, 2(multiple)
        vector<string> ans;
        int len = s.size(), hashNum = 0;

        if (len < 11)
            return ans;

        for (int i = 0; i < 9; ++i)
            hashNum = hashNum << 2 | map[s[i] - 'A'];

        for (int i = 9; i < len; ++i)
        {
            hashNum = (hashNum << 2 | map[s[i] - 'A']) & 0xfffff;

            if (hashMap[hashNum] == 0)
                ++hashMap[hashNum];
            else if (hashMap[hashNum] == 1)
            {
                ++hashMap[hashNum];
                ans.push_back(s.substr(i - 9, 10));
            }
        }
        return ans;
    }
};

// only difference is how to map ATCG to 2-bit string
// 24ms
class Solution3 {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<char, int> ch{ { 'A', 0 }, { 'C', 1 }, { 'G', 2 }, { 'T', 3 } };
        char hashMap[1048576] = { 0 };  // each hashSum has 3 states: 0, 1, 2(multiple)
        vector<string> ans;
        int len = s.size(), hashNum = 0;

        if (len < 11)
            return ans;

        for (int i = 0; i < 9; ++i)
            hashNum = hashNum << 2 | ch[s[i]];

        for (int i = 9; i < len; ++i)
        {
            hashNum = (hashNum << 2 | ch[s[i]]) & 0xfffff;

            if (hashMap[hashNum] == 0)
                ++hashMap[hashNum];
            else if (hashMap[hashNum] == 1)
            {
                ++hashMap[hashNum];
                ans.push_back(s.substr(i - 9, 10));
            }
        }
        return ans;
    }
};

// A = 65, C = 67, G = 71, T = 84
// in octal A is 0101, C is 0103, G is 0107, T is 0124
// the last bit which is the last 3 bits in binary is different (001 011 111 100)
// can use s[i] & 7 to get the last 3 bits
// then we need & 0x3FFFFFFF to get the last 30 bits

// s[i] & 7 is never 0, each of the first nine substrings with length < 10 will have unique hash key
// and will never collide with other 10-letter long sequences
// so don't need to calculate for the first 9 characters first
// 92ms
class Solution4 {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, int> hashMap;
        vector<string> result;
        for (int hashNum = 0, i = 0; i < s.size(); ++i)
            if (hashMap[hashNum = hashNum << 3 & 0x3FFFFFFF | s[i] & 7]++ == 1)
                result.push_back(s.substr(i - 9, 10));
        return result;
    }
};

// mapped value need not be an integer counter, and could simply be a boolean to further save space
// This requires some extra logic though
// 112ms
class Solution5 {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, bool> hashMap;
        vector<string> result;
        for (int hashNum = 0, i = 0; i < s.size(); ++i)
        {
            hashNum = hashNum << 3 & 0x3FFFFFFF | s[i] & 7;
            if (hashMap.find(hashNum) != hashMap.end())
            {
                if (hashMap[hashNum])
                {
                    result.push_back(s.substr(i - 9, 10));
                    hashMap[hashNum] = false;
                }
            }
            else
                hashMap[hashNum] = true;
        }
        return result;
    }
};

// "Compile time limit exceeded" in OJ
class Solution6 {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        char hashMap[1073741824] = { 0 };  // each hashSum has 3 states: 0, 1, 2(multiple)
        vector<string> ans;
        int len = s.size(), hashNum = 0;

        if (len < 11)
            return ans;

        for (int i = 0; i < len; ++i)
        {
            hashNum = hashNum << 3 & 0x3FFFFFFF | s[i] & 7;

            if (hashMap[hashNum] == 0)
                ++hashMap[hashNum];
            else if (hashMap[hashNum] == 1)
            {
                ++hashMap[hashNum];
                ans.push_back(s.substr(i - 9, 10));
            }
        }
        return ans;
    }
};