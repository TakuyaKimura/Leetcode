/*

Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:
    v1 = [1, 2]
    v2 = [3, 4, 5, 6]

By calling next repeatedly until hasNext returns false, 
the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: 
What if you are given k 1d vectors? How well can your code be extended to such cases?

The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. 

If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

    [1,2,3]
    [4,5,6,7]
    [8,9]

It should return [1,4,8,2,5,9,3,6,7].

*/

#include <vector>
using namespace std;

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (v1.begin() != v1.end())
            beginsAndEnds.push_back(make_pair(v1.begin(), v1.end()));
        if (v2.begin() != v2.end())
            beginsAndEnds.push_back(make_pair(v2.begin(), v2.end()));
        it = beginsAndEnds.begin();
    }

    int next() {
        int result = *it->first;
        if (++it->first == it->second)
            it = beginsAndEnds.erase(it);
        else
            ++it;
        if (it == beginsAndEnds.end())
            it = beginsAndEnds.begin();
        return result;
    }

    bool hasNext() {
        return !beginsAndEnds.empty();
    }

private:
    vector<pair<vector<int>::iterator, vector<int>::iterator>> beginsAndEnds;
    vector<pair<vector<int>::iterator, vector<int>::iterator>>::iterator it;
};

/**
* Your ZigzagIterator object will be instantiated and called as such:
* ZigzagIterator i(v1, v2);
* while (i.hasNext()) cout << i.next();
*/