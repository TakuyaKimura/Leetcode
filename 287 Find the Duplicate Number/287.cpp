/*

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), 
prove that at least one duplicate number must exist. 

Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.

*/

#include <vector>
#include <string>
using namespace std;

// http://keithschwarz.com/interesting/code/?dir=find-duplicate

// cycle detection, O(n), 12ms
// we can think of the array as a function f maps from the set {0, ..., n} to itself
// f(i) = nums[i]
// Given this setup, a duplicated value corresponds to a pair of indices i != j such that f(i) = f(j)

// imagine nums[i] to be the next pointer of i
// since the first node 0 is not gonna be visited again, it forms a "rho-shaped" sequence
// we can use "tortoise and hare" algorithm, entry of the cycle is the duplicate
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        fast = 0;
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

// binary search, O(n logn), 24ms
// mid is not the middle index, it's the average of the largest and smallest number in the range
// Let count be the number of elements in the range 1 .. mid (should == mid if no duplicates)
// - If count > mid, then there are more than mid elements in the range 1...mid and thus that range contains a duplicate.
// - If count <= mid, then there are n + 1 - count elements in the range mid + 1 ..n.
//   That is, at least n + 1 - mid elements in a range of size n - mid.Thus this range must contain a duplicate.
class Solution2 {
public:
    int findDuplicate(vector<int>& nums) {
        int low = 1, high = nums.size() - 1, mid, count;
        while (low < high)
        {
            count = 0;
            mid = (low + high) / 2;
            for (int num : nums)  // O(n)
                if (num <= mid)
                    ++count;
            if (count > mid)
                high = mid;               
            else
                low = mid + 1;
        }
        return low;
    }
};

// 24ms
class Solution3 {
public:
    int findDuplicate(vector<int>& nums) {
        int low = 1, high = nums.size() - 1, mid, count;
        while (low <= high)  // different here
        {
            count = 0;
            mid = (low + high) / 2;
            for (int num : nums)
                if (num <= mid)
                    ++count;
            if (count > mid)
                high = mid - 1;  // different here
            else
                low = mid + 1;
        }
        return low;
    }
};

// Bloom filter, 64ms
class Solution4 {
public:
    int findDuplicate(vector<int>& nums) {
        vector<bool> bitsMasks(bits);
        for (int i = 0; i < nums.size(); ++i)
        {
            int count = 0;
            for (int h = 0; h < hashes; ++h)
            {
                string s = to_string(nums[i]);
                int hash = 0;
                for (int c = 0; c < s.length(); ++c)
                    hash = primes[h] * hash + s[c];
                hash = hash % bits;
                if (hash < 0)
                    hash = (bits + hash) % bits;
                if (!bitsMasks[hash])
                    ++count;
                bitsMasks[hash] = true;
            }
            if (count == 0)
                return nums[i];
        }
        return -1;
    }
private:
    int hashes = 5;
    int bits = 5000000;
    vector<int> primes { 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
};