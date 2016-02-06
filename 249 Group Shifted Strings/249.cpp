/*

Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". 

We can keep "shifting" which forms the sequence:

    "abc" -> "bcd" -> ... -> "xyz"

Given a list of strings which contains only lowercase alphabets, 
group all strings that belong to the same shifting sequence.

For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Return:

    [
        ["abc","bcd","xyz"],
        ["az","ba"],
        ["acef"],
        ["a","z"]
    ]

Note: For the return value, each inner list's elements must follow the lexicographic order.

*/

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        sort(strings.begin(), strings.end());
        vector<vector<string>> result;
        for (string& str : strings)
        {
            bool found = false;
            size_t len = str.length();
            for (auto& vct : result)
            {
                string cmp = vct[0];
                if (len != cmp.length())
                    continue;
                if (str.empty())
                {
                    vct.push_back(str);
                    found = true;
                    break;
                }
                int dist = str[0] - cmp[0], i;
                if (dist < 0)  // str[0] could be smaller than cmp[0]
                    dist += 26;
                for (i = 1; i < len; ++i)
                    if (str[i] - cmp[i] != dist && str[i] - cmp[i] + 26 != dist)
                        break;
                if (i == len)
                {
                    vct.push_back(str);
                    found = true;
                    break;
                }
            }
            if (!found)
                result.push_back({ str });
        }
        return result;
    }
};

class Solution2 {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        sort(strings.begin(), strings.end());

        unordered_map<string, vector<string>> hash;
        for (string& s : strings)
            hash[shift(s)].push_back(s);

        vector<vector<string>> groups;
        for (auto& m : hash)
            groups.push_back(m.second);

        return groups;
    }
private:
    string shift(string& s) {
        string t;
        int n = s.length(), diff;
        for (int i = 1; i < n; ++i)
        {
            diff = s[i] - s[i - 1];
            if (diff < 0) 
                diff += 26;
            t += (char)diff;
        }
        return t;
    }
};