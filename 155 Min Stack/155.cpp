/*

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    getMin() -- Retrieve the minimum element in the stack.

*/

#include <deque>
#include <stack>
using namespace std;

class MinStack {
public:
    void push(int x) {
        values.push_back(x);
        if (mins.empty() || x <= mins.back())
            mins.push_back(x);
    }

    void pop() {
        if (values.back() == mins.back())
            mins.pop_back();
        values.pop_back();
    }

    int top() {
        return values.back();
    }

    int getMin() {
        return mins.back();
    }
private:
    deque<int> values, mins;
};

// use deque would be a bit faster
class MinStack {
public:
    void push(int x) {
        stk.push(x);
        if (minStk.empty() || x < minStk.top())
            minStk.push(x);
        else
            minStk.push(minStk.top());
    }

    void pop() {
        stk.pop();
        minStk.pop();
    }

    int top() {
        return stk.top();
    }

    int getMin() {
        return minStk.top();
    }
private:
    stack<int> stk, minStk;
};

// store the indices of the mins, instead of the values
// deque can be accessed by index
// and is faster than vector (in this problem)
// vectors use contiguous memory, so when grow need to copy to another place
// deques are like list of vectors
class MinStack {
public:
    void push(int x) {
        if (minIdx.empty() || x < values[minIdx.back()])
            minIdx.push_back(size);

        values.push_back(x);
        ++size;
    }

    void pop() {
        values.pop_back();
        --size;
        if (minIdx.back() == size)
            minIdx.pop_back();
    }

    int top() {
        return values.back();
    }

    int getMin() {
        return values[minIdx.back()];
    }
private:
    deque<int> values, minIdx;
    int size = 0;
};