/*

A city's skyline is the outer contour of the silhouette 
formed by all the buildings in that city when viewed from a distance. 
Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), 
write a program to output the skyline formed by these buildings collectively (Figure B).

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], 
where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. 
It is guaranteed that 0 ¡Ü Li, Ri ¡Ü INT_MAX, 0 < Hi ¡Ü INT_MAX, and Ri - Li > 0. 
You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as:
    [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ].

The output is a list of "key points" (red dots in Figure B) in the format of 
    [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. 
A key point is the left endpoint of a horizontal line segment. 
Note that the last key point, where the rightmost building ends, 
is merely used to mark the termination of the skyline, and always has zero height. 
Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:
    [ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].


Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].

The input list is already sorted in ascending order by the left x position Li.

The output list must be sorted by the x position.

There must be no consecutive horizontal lines of equal height in the output skyline. 
For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; t
he three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]

*/

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;

// Sweep from left to right, and keep (height, right) pairs of "alive buildings" in the priority queue
// and don't remove them as soon as their building is left behind.
// Instead, they stay in there as long as there's a larger height in there.

// In each loop, we first check what has the smaller x-coordinate:
// adding the next building from the input, or removing the next building from the queue.
// In case of a tie, adding buildings wins, as that guarantees correctness (think about it).
// We then either add all input buildings starting at that x-coordinate
// or we remove all queued buildings ending at that x-coordinate or earlier
// And then, if the current maximum height in the queue differs from the last in the skyline, we add it to the skyline.

// each building is processed at most twice (push and pop), at most n elements in the heap
// worst case O(nlogn)

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> res;
        int i = 0, cur_X, cur_H, len = buildings.size();
        priority_queue<pair<int, int>> liveBlg;  // (height, right) pair, sort by height
        while (i < len || !liveBlg.empty())
        {
            if (liveBlg.empty() || i < len && buildings[i][0] <= liveBlg.top().second)  // compare with the new top, because the old crossing point would be overlapped if it crossed with the old top
            {
                cur_X = buildings[i][0];
                while (i < len && buildings[i][0] == cur_X)  // in case of buildings with same left, but different heights
                {
                    // we look at the highest, because if some other building crosses over its right edge
                    // there got to be a crossing point, which is guaranteed not to be overlapped
                    liveBlg.push(make_pair(buildings[i][2], buildings[i][1]));
                    ++i;
                }
            }
            else
            {
                cur_X = liveBlg.top().second;
                while (!liveBlg.empty() && liveBlg.top().second <= cur_X)  // until some right edge cross over it
                    liveBlg.pop();
            }
            cur_H = liveBlg.empty() ? 0 : liveBlg.top().first;
            if (res.empty() || (res.back().second != cur_H))
                res.push_back(make_pair(cur_X, cur_H));  // if a new highest is added, then record its left corner (cur_X is set in "if")
                                                         // otherwise, left corner is inside the top, ignore it
                                                         // record the crossing point after popping the top one
                                                         // it's safe to pop because there will only be one point, the highest one, which is valid
                                                         // which is the new highest after popping all the ones on the left
        }
        return res;
    }
};

// Divide-and-conquer, O(nlogn)
class Solution2 {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        if (buildings.empty())
            return vector<pair<int, int>>();
        return getSkyline_rec(buildings, 0, buildings.size() - 1);
    }
private:
    // parameters as reference type will be slower in OJ. Why?
    vector<pair<int, int>> merge(vector<pair<int, int>> skyline1, vector<pair<int, int>> skyline2) {
        vector<pair<int, int>> res;
        //priority_queue<pair<int, int>> pq(skyline1.begin(), skyline1.end()); // first: x, second: h
        //priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq(skyline1.begin(), skyline1.end()); // first: x, second: h
        int len1 = skyline1.size(), len2 = skyline2.size(), cur1 = 0, cur2 = 0, cur1_H = -1, cur2_H = -1, cur_H, cur_X;
        while (cur1 < len1 && cur2 < len2)
        {
            if (skyline1[cur1].first < skyline2[cur2].first)
            {
                cur_X = skyline1[cur1].first;
                cur1_H = skyline1[cur1].second;
                ++cur1;
            }
            else if (skyline1[cur1].first > skyline2[cur2].first)
            {
                cur_X = skyline2[cur2].first;
                cur2_H = skyline2[cur2].second;
                ++cur2;
            }
            else
            {
                cur_X = skyline1[cur1].first;
                cur1_H = skyline1[cur1].second;
                cur2_H = skyline2[cur2].second;
                ++cur1;
                ++cur2;
            }
            cur_H = max(cur1_H, cur2_H);
            if (res.empty() || res.back().second != cur_H)
                res.push_back(make_pair(cur_X, cur_H));
        }
        while (cur1 < len1)
            res.push_back(skyline1[cur1++]);
        while (cur2 < len2)
            res.push_back(skyline2[cur2++]);
        return res;
    }

    // recursive
    vector<pair<int, int>> getSkyline_rec(vector<vector<int>>& buildings, int start, int end) {
        if (start < end)
        {
            int mid = start + (end - start) / 2;
            vector<pair<int, int>> skyline1 = getSkyline_rec(buildings, start, mid);
            vector<pair<int, int>> skyline2 = getSkyline_rec(buildings, mid + 1, end);
            return merge(skyline1, skyline2);
        }
        else  // base case, one building
        {
            vector<pair<int, int>> res(2);
            res[0] = make_pair(buildings[start][0], buildings[start][2]);
            res[1] = make_pair(buildings[start][1], 0);
            return res;
        }
    }
};

// another O(nlogn). The basic idea is: 
// 1. put the start and end of each rectangle into a multimap, we will scan it later.
//    The second parameter of the pair is its height. (i.e. as for [0,5,3] we will put {0, 3} and {5, -3} into the map)
// 2. for each element in multimap, if the height is greater than zero, we put it into multiset, else we find and erase it from the set.
// 3. the multiset means at each x value, the existing rectangle.
// 4. After processing each x value, the max in the set is what we need, just put it into the vector.
class Solution3 {
public:
    struct comp {
        bool operator() (const int &a, const int &b) { return a > b; }
    };

    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> ret;
        multimap<int, int> pairs;
        int last_height, height, cur;
        for (auto& building : buildings)
        {
            pairs.insert(make_pair(building[0], building[2]));
            pairs.insert(make_pair(building[1], 0 - building[2]));
        }
        multiset<int, comp> heights;  // begin() will be the largest (default is smallest)
        heights.insert(0);
        while (!pairs.empty())
        {
            last_height = *heights.begin();  // this is the last value we pushed into result
            cur = pairs.begin()->first;
            while (pairs.begin()->first == cur)
            {
                height = pairs.begin()->second;
                if (height > 0)
                    heights.insert(height);
                else  // end of this rectangle, so remove it from the "heights"
                    heights.erase(heights.find(0 - height));  // don't erase by value, because that will erase all elements with that value
                pairs.erase(pairs.begin());
            }
            if (*heights.begin() != last_height)
                ret.push_back(make_pair(cur, *heights.begin()));
        }
        return ret;
    }
};

// Segment tree, slow
class Solution4 {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        unordered_map<int, int> line, rline;
        int n = buildings.size();
        set<int> l;
        int top = -2, pre = -1, i, h;
        for (i = 0; i < n; ++i)
        {
            l.insert(buildings[i][0]);
            l.insert(buildings[i][1]);
        }
        for (set<int>::iterator it = l.begin(); it != l.end(); ++it)
        {
            if (pre != -1 && *it == pre + 1)
                ++top;
            else
                top += 2;
            line[*it] = top;
            rline[top] = *it;
            pre = *it;
        }
        for (i = 0; i < n; ++i)
            update(1, 0, top, line[buildings[i][0]], line[buildings[i][1]], buildings[i][2]);

        vector<pair<int, int>> res;
        int ph = 0;
        for (i = 0; i <= top; ++i)
        {
            h = query(1, 0, top, i);
            if (h != ph)
            {
                res.push_back(make_pair(h > ph ? rline[i] : rline[i - 1], h));
                ph = h;
            }
        }
        if (n > 0)
            res.push_back(make_pair((rline[top]), 0));
        return res;
    }
private:
    int tree[20000 << 2] = {};
    void update(int n, int l, int r, int left, int right, int value) {
        if (l == left && r == right)
            tree[n] = max(tree[n], value);
        else
        {
            int m = (l + r) >> 1;
            if (right <= m)
                update(n << 1, l, m, left, right, value);
            else if (left > m)
                update(n << 1 | 1, m + 1, r, left, right, value);
            else
            {
                update(n << 1, l, m, left, m, value);
                update(n << 1 | 1, m + 1, r, m + 1, right, value);
            }
        }
    }
    int query(int n, int l, int r, int index) {
        if (l == r)
            return tree[n];
        else
        {
            int m = (l + r) >> 1;
            int res = (index <= m ? query(n << 1, l, m, index) : query(n << 1 | 1, m + 1, r, index));
            return max(res, tree[n]);
        }
    }
};

// slow
class Solution5 {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        const int N = buildings.size();
        vector<pair<int, int>> result;
        if (0 == N)
            return result;
        map<int, int> x2hmap;
        vector<int> building = buildings[0];
        int lb = building[0];
        int rb = building[1];
        int tb = building[2];
        x2hmap[lb] = 0;
        x2hmap[rb] = 0;
        for (int i = 1; i < N; ++i)
        {
            building = buildings[i];
            if (building[0] >= lb && building[1] <= rb && building[2] <= tb)
                continue;
            lb = building[0];
            rb = building[1];
            tb = building[2];
            x2hmap[lb] = 0;
            x2hmap[rb] = 0;
        }
        for (int i = 0; i < N; ++i)
        {
            building = buildings[i];
            auto lowbound = x2hmap.lower_bound(building[0]);
            auto upperbound = x2hmap.upper_bound(building[1] - 1);
            for (auto it = lowbound; it != upperbound; ++it)
                if (building[2] > it->second)
                    it->second = building[2];
        }
        for (auto &x2hpair : x2hmap)
        {
            const int &curx = x2hpair.first;
            const int &maxh = x2hpair.second;
            if (result.empty() || (curx != result.back().first && maxh != result.back().second))
                result.emplace_back(pair<int, int>(curx, maxh));
        }
        return result;
    }
};


// linear time, but can't pass OJ
// because vector or array can't be too large
// 2^31 entries, each 4 bytes, that's 8G!!!
// the max_size for int vector is 1073741823
// can't declare arrays that large on stack or even heap either
class Solution6 {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        int maxRight = -1, i, h, r, preH = 0;
        vector<int> heights;
        vector<pair<int, int>> result;
        for (auto& building : buildings)
        {
            r = building[1];
            h = building[2];
            if (r > maxRight)
            {
                maxRight = r;
                heights.resize(maxRight + 1);
            }
            for (i = building[0]; i <= r; ++i)
                if (heights[i] < h)
                    heights[i] = h;
        }
        for (i = 0; i <= maxRight; ++i)
        {
            if (heights[i] != preH)
            {
                result.push_back(make_pair(i, heights[i]));
                preH = heights[i];
            }
        }
        if (maxRight > -1)
            result.push_back(make_pair(maxRight, 0));
        return result;
    }
};

int main()
{
    Solution2 s;
    vector<vector<int>> buildings{ { 0, 2147483647, 2147483647 } };
    s.getSkyline(buildings);
}