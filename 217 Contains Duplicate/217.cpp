/*

Given an array of integers, find if the array contains any duplicates. 

Your function should return true if any value appears at least twice in the array, 
and it should return false if every element is distinct.

*/

#include <unordered_set>
#include <set>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> hash;
        for (auto& num : nums)
        {
            if (hash.find(num) != hash.end())
                return true;
            hash.insert(num);
        }
        return false;
    }
};

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        return nums.size() > set<int>(nums.begin(), nums.end()).size();  // faster than using unordered_set
    }
};