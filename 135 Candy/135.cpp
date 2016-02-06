/*

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give?

*/

#include <vector>
#include <algorithm>
using namespace std;

// O(n) extra space for candies array
// two passes through the ratings array, one pass through the candies array
class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size(), total = 0;;
        vector<int> candies(n, 1);
        for (int i = 1; i < n; ++i)
            if (ratings[i] > ratings[i - 1])
                candies[i] = candies[i - 1] + 1;
        for (int i = n - 2; i >= 0; --i)
            if (ratings[i] > ratings[i + 1])
                candies[i] = max(candies[i + 1] + 1, candies[i]);
        for (int candy : candies)
            total += candy;
        return total;
    }
};

// O(1) extra space, one pass
class Solution2 {
public:
    int candy(vector<int>& ratings) {
        if (ratings.empty())
            return 0;
        int pre = ratings[0], cur, total = 1, peak = 1, candy = 1, numDesc = 1;  // numDesc is at least 1, always assume it's descending from the previous one
        for (int i = 1; i < ratings.size(); ++i)
        {
            cur = ratings[i];
            if (cur > pre)
            {
                peak = ++candy;
                numDesc = 1;
            }
            else if (cur < pre)
            {
                candy = 1;
                total += numDesc;    // these ones need to be elevated
                if (peak > numDesc)  // the peak doesn't need to be elevated
                    --total;
                ++numDesc;
            }
            else
                peak = candy = numDesc = 1;  // also need to reset peak

            total += candy;
            pre = cur;
        }
        return total;
    }
};