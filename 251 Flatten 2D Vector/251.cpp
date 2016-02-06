/*

Implement an iterator to flatten a 2d vector.

For example,
Given 2d vector =
    [
        [1,2],
        [3],
        [4,5,6]
    ]

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

Hint:
1. How many variables do you need to keep track?

2. Two variables is all you need. Try with x and y.

3. Beware of empty rows. It could be the first few rows.

4. To write correct code, think about the invariant to maintain. What is it?

5. The invariant is x and y must always point to a valid point in the 2d vector. 
   Should you maintain your invariant ahead of time or right when you need it?

6. Not sure? Think about how you would implement hasNext(). Which is more complex?

7. Common logic in two different places should be refactored into a common method.

Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java.

*/

#include <vector>
using namespace std;

class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        x = 0;
        y = -1;
        vct = vec2d;
    }

    int next() {
        return vct[x][y];
    }

    bool hasNext() {
        ++y;
        while (x < vct.size() && y == vct[x].size())
        {
            y -= vct[x].size();
            ++x;
        }
        return x != vct.size();
    }
private:
    int x, y;
    vector<vector<int>> vct;
};

// using only iterators
class Vector2D2 {
public:
    Vector2D2(vector<vector<int>>& vec2d) {
        it = vec2d.begin();
        end = vec2d.end();
        if (it != end)
            it2 = it->begin();
    }

    int next() {
        return *it2++;
    }

    bool hasNext() {
        while (it != end && it2 == it->end())
        {
            ++it;
            it2 = it->begin();
        }
        return it != end;
    }
private:
    vector<vector<int>>::iterator it, end;
    vector<int>::iterator it2;
};

/**
* Your Vector2D object will be instantiated and called as such:
* Vector2D i(vec2d);
* while (i.hasNext()) cout << i.next();
*/