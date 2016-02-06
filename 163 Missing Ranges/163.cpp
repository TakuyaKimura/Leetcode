/*

Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].

*/

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> result;
        int cmp = lower, num, n = nums.size();
        for (int i = 0; i < n && (num = nums[i]) <= upper && num != INT_MAX; ++i)
        {
            if (num < cmp)  // skip the ones smaller than lower bound, don't update cmp for them
                continue;
            if (num != INT_MIN)  // if it's INT_MIN, we're not missing any range before it
                addRange(result, cmp, num - 1);
            cmp = num + 1;
        }
        addRange(result, cmp, upper);
        return result;
    }
private:
    void addRange(vector<string>& result, int lowerRange, int upperRange) {
        if (lowerRange > upperRange)
            return;
        string range = to_string(lowerRange);
        if (lowerRange != upperRange)
            range += "->" + to_string(upperRange);
        result.push_back(range);
    }
};

int main() {
    Solution s;
    vector<int> v{ INT_MIN, INT_MIN, 3, INT_MAX, INT_MAX };
    s.findMissingRanges(v, INT_MIN, INT_MAX);
}