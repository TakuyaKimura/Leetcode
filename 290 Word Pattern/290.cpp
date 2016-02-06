/*

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
    pattern = "abba", str = "dog cat cat dog" should return true.
    pattern = "abba", str = "dog cat cat fish" should return false.
    pattern = "aaaa", str = "dog cat cat dog" should return false.
    pattern = "abba", str = "dog dog dog dog" should return false.

Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.

*/

#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

// pattern may also contain whitespaces
// note for unordered_map:
// If k does not match the key of any element in the container, the function inserts a new element with that key
// even if no mapped value is assigned to the element (the element is constructed using its default constructor)
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char, string> c2s;
        unordered_map<string, char> s2c;
        istringstream iss(str);
        string sub;
        for (char c : pattern)
        {
            if (!(iss >> sub))
                return false;
            if (c2s[c].empty() && s2c[sub] == 0)  // need to check both
            {
                c2s[c] = sub;
                s2c[sub] = c;
            }
            else if (c2s[c] != sub)  // only need to check one
                return false;
        }
        if (iss >> sub)  // still strings left
            return false;
        return true;
    }
};