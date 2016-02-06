/*

Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

*/

#include <vector>
#include <algorithm>
using namespace std;

// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

// O(nlogn) sort, then O(n) additional work
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b){
            return a.start < b.start; });
        vector<Interval> result;
        for (auto& interval : intervals)
        {
            if (result.empty() || interval.start > result.back().end)
                result.push_back(interval);
            else
                result.back().end = max(result.back().end, interval.end);
        }
        return result;
    }
};