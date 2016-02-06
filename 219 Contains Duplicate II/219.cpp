/*

Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array 
such that nums[i] = nums[j] and the difference between i and j is at most k.

*/

#include <unordered_map>
#include <unordered_set>
using namespace std;

// maintain a hash of nums[i-k] ... nums[i-1]
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> hash;
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            if (hash.find(nums[i]) != hash.end())
                return true;
            hash.insert(nums[i]);
            if (hash.size() == k + 1)
                hash.erase(nums[i - k]);
        }
        return false;
    }
};