/*

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), 
find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

*/

#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

// Greedy
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        int rooms = 0, n = intervals.size(), startIdx, endIdx = 0;
        vector<int> starts(n), ends(n);
        for (int i = 0; i < n; ++i)
        {
            starts[i] = intervals[i].start;
            ends[i] = intervals[i].end;
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());
        for (startIdx = 0; startIdx < n; ++startIdx)
            if (starts[startIdx] < ends[endIdx])
                ++rooms;
            else  // since ends[endIdx] ends before starts[startIdx], we can add it after in the same room
                ++endIdx;  // go to check the next ending meeting

        return rooms;
    }
};

// slower, 2n elements
class Solution2 {
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> numMtChange;  // at each time point, how number of meetings changed
        for (auto& interval : intervals)
        {
            ++numMtChange[interval.start];
            --numMtChange[interval.end];
        }
        int rooms = 0, maxRooms = 0;
        for (auto& change : numMtChange)  // map is sorted
        {
            rooms += change.second;
            maxRooms = max(maxRooms, rooms);
        }
        return maxRooms;
    }
};

class Solution3 {
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<pair<int, int>> changes;
        for (auto& i : intervals)
        {
            changes.push_back(make_pair(i.start, 1));
            changes.push_back(make_pair(i.end, -1));
        }
        sort(begin(changes), end(changes));  // same as changes.begin() & changes.end()
        int rooms = 0, maxRooms = 0;
        for (auto& change : changes)
            maxRooms = max(maxRooms, rooms += change.second);
        return maxRooms;
    }
};