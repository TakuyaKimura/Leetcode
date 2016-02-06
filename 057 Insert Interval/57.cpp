/*

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

*/

#include <vector>
#include <algorithm>  // for lower_bound & upper_bound
using namespace std;

// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

// use binary search to find the overlapping range
// 1. Find low interval that overlaps with new interval
//    i.e. First interval whose end is greater than or equal to newInterval.start
// 2. Find high interval (noninclusive) that overlaps with new interval
//    i.e. First interval whose start is greater than newInterval.end

// O(logn) to find the overlapping range, O(n) to move the elements around
// 584ms
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        // Returns an iterator pointing to the first element which does not compare less than val
        // val is used as the SECOND argument in comp()
        auto low = lower_bound(intervals.begin(), intervals.end(), newInterval,
            [](const Interval& l, const Interval& r){ return l.end < r.start; });  // -------------------- same function

        if (low == intervals.end())  // won't be able to dereference
        {
            intervals.push_back(newInterval);
            return intervals;
        }

        // Returns an iterator pointing to the first element which compares greater than val
        // val is used as the FIRST argument in comp()
        auto high = upper_bound(intervals.begin(), intervals.end(), newInterval,
            [](const Interval& l, const Interval& r){ return l.end < r.start; });  // -------------------- same function

        if (high == intervals.begin())  // won't be able to dereference high - 1
        {
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }

        // Result is [intervals.begin(), low) U mergedInterval U [high, intervals.end())
        newInterval.start = min(newInterval.start, low->start);
        newInterval.end = max(newInterval.end, (high - 1)->end);
        intervals.insert(intervals.erase(low, high), newInterval);  // erase returns an iterator to the new position
        return intervals;
    }
private:
    static bool cmp(const Interval& i1, const Interval& i2) {
        return i1.end < i2.start;
    }
};

// 580ms, same idea, linear search
class Solution2 {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int start = newInterval.start, end = newInterval.end;
        vector<Interval>::iterator low, high, it = intervals.begin();
        while (it != intervals.end() && it->end < start)
            ++it;
        low = it;

        if (low == intervals.end())
        {
            intervals.push_back(newInterval);
            return intervals;
        }

        while (it != intervals.end() && it->start <= end)
            ++it;
        high = it;

        if (high == intervals.begin())
        {
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }

        Interval merged(min(low->start, start), max((high - 1)->end, end));
        it = intervals.erase(low, high);
        intervals.insert(it, merged);
        return intervals;
    }
};

// 576ms, same idea
class Solution3 {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int start = newInterval.start, end = newInterval.end, mergedStart = start, mergedEnd = end;
        vector<Interval>::iterator it = intervals.begin();
        vector<Interval> result;
        while (it != intervals.end() && it->end < start)
        {
            result.push_back(*it);
            ++it;
        }

        if (it == intervals.end())
        {
            result.push_back(newInterval);
            return result;
        }

        if (it->start < start)
            mergedStart = it->start;

        while (it != intervals.end() && it->start <= end)
            ++it;

        if (it != intervals.begin() && (it - 1)->end > end)
            mergedEnd = (it - 1)->end;

        result.push_back(Interval(mergedStart, mergedEnd));
        while (it != intervals.end())
        {
            result.push_back(*it);
            ++it;
        }
        return result;
    }
};

// 576ms
class Solution4 {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int start = newInterval.start, end = newInterval.end, n = intervals.size(), i;
        vector<Interval> result;
        for (i = 0; i < n && intervals[i].start <= end; ++i)
        {
            if (intervals[i].end < start)
                result.push_back(intervals[i]);
            else
            {
                start = min(start, intervals[i].start);  // update for each iterval, it actually won't becomes smaller
                end = max(end, intervals[i].end);
            }
        }
        result.push_back(Interval(start, end));

        for (; i < n; ++i)
            result.push_back(intervals[i]);

        return result;
    }
};