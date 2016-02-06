/*

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

// merge with its neighbor
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> seqLen;
        int leftLen, rightLen, wholeLen, longest = 0;
        for (int num : nums)
            if (!seqLen[num])
            {
                leftLen = seqLen[num - 1];  // if not already inserted, it will be 0
                rightLen = seqLen[num + 1];
                wholeLen = leftLen + rightLen + 1;
                longest = max(wholeLen, longest);
                seqLen[num] = seqLen[num - leftLen] = seqLen[num + rightLen] = wholeLen;  // only change both ends
            }

        return longest;
    }
};

// strike off from a set
class Solution2 {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set(nums.begin(), nums.end());
        int longest = 0, start, end;
        for (int num : nums)
            if (set.find(num) != set.end())
            {
                set.erase(num);
                start = num - 1;
                end = num + 1;
                while (set.find(start) != set.end())
                    set.erase(start--);
                while (set.find(end) != set.end())
                    set.erase(end++);
                longest = max(longest, end - start - 1);
            }

        return longest;
    }
};

// UnionFind
class UF {
public:
    UF(int n) : count(n), id(n), size(n, 1) {
        for (int i = 0; i < n; ++i)
            id[i] = i;
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }

    void connect(int a, int b) {
        int i = find(a), j = find(b);
        if (i == j)
            return;
        if (size[i] < size[j])
        {
            id[i] = j;
            size[j] += size[i];
        }
        else
        {
            id[j] = i;
            size[i] += size[j];
        }
        --count;
    }

    int maxSize() {
        int ans = 1;
        for (int sz : size)
            ans = max(ans, sz);
        return ans;
    }

    int getCount() {
        return count;
    }

private:
    int count;
    vector<int> id;
    vector<int> size;

    int find(int num) {
        while (num != id[num])
            num = id[num] = id[id[num]];
        return num;
    }
};

class Solution3 {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size(), num;
        UF uf(n);
        unordered_map<int, int> indices;

        for (int i = 0; i < n; ++i)
        {
            num = nums[i];
            if (indices.find(num) != indices.end())
                continue;
            indices[num] = i;

            // like 2-sum, can insert and search at the same time
            if (indices.find(num - 1) != indices.end())
                uf.connect(i, indices[num - 1]);
                //uf.connect(indices[num], indices[num - 1]);  // if didn't check for duplicate, have to use indices[num] instead of i
            if (indices.find(num + 1) != indices.end())
                uf.connect(i, indices[num + 1]);
                //uf.connect(indices[num], indices[num + 1]);
        }
        return uf.maxSize();
    }
};