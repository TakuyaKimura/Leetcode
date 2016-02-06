/*

Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

*/

#include <string>
#include <vector>
using namespace std;

// this is the brute force method
// consider haystack has length h, needle has length n
// instead of looping h times, we only need to iterate h - n + 1 times
class Solution {
public:
    int strStr(string haystack, string needle) {
        int h = haystack.length(), n = needle.length(), start, i;
        if (n == 0)
            return 0;
        for (start = 0; start <= h - n; ++start)
        {
            i = 0;
            while (i < n && haystack[start + i] == needle[i])
                ++i;
            if (i == n)
                return start;
        }
        return -1;
    }
};

// KMP (Knuth每Morris每Pratt) algorithm
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
// runtime is O(h + n)

class Solution2 {
public:
    // worst case runtime is 2h, so O(h)
    int strStr(string haystack, string needle) {
        if (needle.empty())
            return 0;
        buildTable(needle);
        int m = 0, i = 0, h = haystack.length(), n = needle.length();
        while (m + i < h)
        {
            if (needle[i] == haystack[m + i])
            {
                if (i == n - 1)
                    return m;
                ++i;
            }
            else
            {
                if (T[i] > -1)
                {
                    m = m + i - T[i];
                    i = T[i];
                }
                else
                {
                    i = 0;
                    ++m;
                }
            }
        }
        return -1;
    }
private:
    vector<int> T;  // table of indices to the needle, i.e. in the event of a mismatch, this is the next char we need to check
                    // against the same char in haystack (don't move this pointer)
                    // new_m = old_m + old_i - T[old_i]
                    // new_i = T[old_i]
                    // so, new_m + new_i = old_m + old_i

    // needle is not empty
    // runtime is O(n)
    void buildTable(string needle) {
        int n = needle.length();
        T = vector<int>(n, 0);
        T[0] = -1;
        int pos = 2, cnd = 0;
        while (pos < n)
        {
            if (needle[pos - 1] == needle[cnd])
                T[pos++] = ++cnd;  // ++cnd, this is the next 
            else if (cnd > 0)
                cnd = T[cnd];  // fall back
            else  // cnd == 0 -> T[pos] = 0
                ++pos;
        }
    }
};

// another implementation of KMP
class Solution3 {
public:
    int strStr(string haystack, string needle) {
        const int size_h = haystack.size();
        const int size_n = needle.size();
        if (0 == size_n)
            return 0;
        vector<int> p(size_n, 0);
        for (int i = 1; i < size_n; ++i)
        {
            int pos = p[i - 1];
            while (pos > 0 && needle[i] != needle[pos])
                pos = p[pos - 1];
            if (needle[i] == needle[pos])
                p[i] = pos + 1;
        }

        int idn = 0, idh = 0;
        for (; idh < size_h; ++idh)
        {
            while (idn > 0 && needle[idn] != haystack[idh])
                idn = p[idn - 1];
            if (needle[idn] == haystack[idh])
                ++idn;
            if (idn == size_n)
                return idh - size_n + 1;
        }
        return -1;
    }
};

// Boyer每Moore每Horspool string search algorithm
// is a simplification of the Boyer每Moore algorithm using only the bad character rule
// average case O(h), worst case O(h * n)

//                   v use THIS char to find slide distance
// T = abaaabbababcabdacbaabababc
// P =     abdacabaabd
//           ^
class Solution4 {
public:
    int strStr(string haystack, string needle) {
        int start = 0, h = haystack.length(), n = needle.length();
        if (n == 0)
            return 0;
        preprocess(needle);
        while (h - start >= n)
        {
            int i = n - 1;  // starting from either end is fine
            while (haystack[start + i] == needle[i])
            {
                if (i == 0)
                    return start;
                --i;
            }
            start += T[haystack[start + n - 1]];  // if the last char doesn't exist in the needle, skip n (length of needle)
        }
        return -1;
    }
private:
    int T[256];  // "Right-most" occurence of a certain character (not including the last character)

    void preprocess(string needle) {
        int n = needle.length();
        fill(begin(T), end(T), n);
        for (int i = 0; i < n - 1; ++i)  // exlusive the last character
            T[needle[i]] = n - 1 - i;
    }
};

// Rabin-Karp algorithm
// best case running time is O(h + n), worst-case time is O(h * n)
// it speeds up the testing of equality by using a hash function
// using a rolling hash (such as the Rabin fingerprint) to computate hash values of successive substrings in CONSTANT time
// Rabin fingerprint treats every substring as a number in some base, the base being usually a large prime
class Solution5 {
public:
    int strStr(string haystack, string needle) {
        int n = needle.length(), h = haystack.length();
        if (n == 0)
            return 0;
        // msb = pow(BASE, n - 1);  // if BASE is too large, this will overflow and give wrong result
        for (int i = 0; i < n - 1; ++i)
            msb *= BASE;
        unsigned int needleHash = computeHash(needle), haystackHash = computeHash(haystack.substr(0, n));
        for (int i = 0; i <= h - n; ++i)
        {
            if (i)
                haystackHash = rollingHash(haystack[i - 1], haystack[i + n - 1], haystackHash);
            if (haystackHash == needleHash && needle == haystack.substr(i, n))
                return i;
        }
        return -1;
    }
private:
    const unsigned int BASE = 97;
    unsigned int msb = 1;  // most significant bit

    unsigned int computeHash(string& s) {
        unsigned int hash = 0;
        for (auto c : s)
            hash = hash * BASE + c;
        return hash;
    }

    unsigned int rollingHash(char front, char end, unsigned int hash) {
        return (hash - msb * front) * BASE + end;
    }
};