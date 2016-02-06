/*

An abbreviation of a word follows the form <first letter><number><last letter>. 

Below are some examples of word abbreviations:

    a) it                      --> it    (no abbreviation)

         1
    b) d|o|g                   --> d1g

                  1    1  1
         1---5----0----5--8
    c) i|nternationalizatio|n  --> i18n

                  1
         1---5----0
    d) l|ocalizatio|n          --> l10n

Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. 

A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

Example:
Given dictionary = [ "deer", "door", "cake", "card" ]

    isUnique("dear") -> false
    isUnique("cart") -> true
    isUnique("cane") -> false
    isUnique("make") -> true

*/

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// for words with length less than 3, its abbrevation is always gonna be unique, so actually we don't need check them

// 204ms
class ValidWordAbbr3 {
public:
    ValidWordAbbr3(vector<string> &dictionary) {
        for (string& word : dictionary)
        {
            int len = word.length();
            string abbr = word[0] + to_string(len) + word[len - 1];
            if (hash.count(abbr) == 0)
                hash[abbr] = word;
            else if (hash[abbr] != word)
                hash[abbr] = "";
        }
    }

    bool isUnique(string word) {
        int len = word.length();
        string abbr = word[0] + to_string(len) + word[len - 1];
        return hash.count(abbr) == 0 || hash[abbr] == word;
    }

private:
    unordered_map<string, string> hash;
};

// 204ms, don't actually need to keep the set, just the count, only increase the count if different
class ValidWordAbbr2 {
public:
    ValidWordAbbr2(vector<string> &dictionary) {
        for (string& word : dictionary)
        {
            int len = word.length();
            string abbr = word[0] + to_string(len) + word[len - 1];
            if (hash[abbr].first == 0)
            {
                hash[abbr].second = word;
                ++hash[abbr].first;
            }
            else if (hash[abbr].second != word)
                ++hash[abbr].first;
        }
    }

    bool isUnique(string word) {
        int len = word.length();
        string abbr = word[0] + to_string(len) + word[len - 1];
        return hash.count(abbr) == 0 || hash[abbr].first == 1 && hash[abbr].second == word;
    }

private:
    unordered_map<string, pair<int, string>> hash;
};

// 260ms
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string>& dictionary) {
        for (string& word : dictionary)
        {
            int len = word.length();
            hash[word[0] + to_string(len) + word[len - 1]].insert(word);  // could use to_string(len) instead of len-2
        }
    }

    bool isUnique(string word) {
        int len = word.length();
        string abbr = word[0] + to_string(len) + word[len - 1];
        // either we don't have the same abbr in dict, or the words that have the same abbr are all == word
        return hash.count(abbr) == 0 || hash[abbr].count(word) == hash[abbr].size();
    }

private:
    unordered_map<string, unordered_set<string>> hash;
};


// Your ValidWordAbbr object will be instantiated and called as such:
// ValidWordAbbr vwa(dictionary);
// vwa.isUnique("hello");
// vwa.isUnique("anotherWord");