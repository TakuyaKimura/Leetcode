/*

Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
    [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].

*/

#include <vector>
using namespace std;

// similar to Problem 17 Letter Combinations of a Phone Number

// DFS
class Solution4 {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        dfs(nums, 0, nums.size() - 1, result);
        return result;
    }
private:
    void dfs(vector<int> nums, int start, int end, vector<vector<int>>& result) {
        if (start == end)
        {
            result.push_back(nums);
            return;
        }
        for (int i = start; i <= end; ++i)
        {
            swap(nums[start], nums[i]);
            dfs(nums, start + 1, end, result);  // note it's not "i + 1"
            // don't need to swap back, because nums is passed by value not reference
        }
    }
};

// DFS
class Solution2 {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        permuteRecursive(nums, 0, nums.size() - 1, result);
        return result;
    }
private:
    // permute nums[begin..end]
    // invariant: nums[0..start-1] have been fixed/permuted
    void permuteRecursive(vector<int>& nums, int start, int end, vector<vector<int>>& result) {
        if (start == end)  // pass n is also correct, in the for loop "i < n"
        {
            // one permutation instance
            result.push_back(nums);
            return;
        }

        for (int i = start; i <= end; ++i)
        {
            swap(nums[start], nums[i]);
            permuteRecursive(nums, start + 1, end, result);
            // reset
            swap(nums[start], nums[i]);
            // or don't pass nums as reference, then don't swap back
        }
    }
};

// iterative
class Solution5 {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result{ {} };
        int n = nums.size(), i, j, k, num, size;
        vector<int> temp;
        for (i = 0; i < n; ++i)
        {
            num = nums[i];
            size = result.size();
            for (j = 0; j < size; ++j)
                for (k = 0; k <= i; ++k)
                {
                    temp = result[j];
                    temp.insert(temp.begin() + k, num);
                    result.push_back(temp);
                }

            result.erase(result.begin(), result.begin() + size);
        }
        return result;
    }
};

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> pre{ {} }, cur;
        vector<int> vct;
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            for (auto &v : pre)
                for (int j = 0; j <= i; ++j)
                {
                    vct = v;
                    vct.insert(vct.begin() + j, nums[i]);
                    cur.push_back(vct);
                }
            pre = cur;
            cur.clear();
        }
        return pre;
    }
};

// recursive
class Solution3 {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        if (nums.empty())
            return result;
        permuteRecursive(nums, result);
        return result;
    }
private:
    void permuteRecursive(vector<int>& nums, vector<vector<int>>& pre) {
        if (nums.size() == 1)
        {
            pre.push_back({ nums[0] });
            return;
        }
        vector<vector<int>> cur;
        vector<int> numsAfter(nums.begin() + 1, nums.end());
        permuteRecursive(numsAfter, pre);
        for (auto &v : pre)
            for (int i = 0; i <= v.size(); ++i)
            {
                vector<int> tmp = v;
                tmp.insert(tmp.begin() + i, nums[0]);
                cur.push_back(tmp);
            }
        pre = cur;
    }
};