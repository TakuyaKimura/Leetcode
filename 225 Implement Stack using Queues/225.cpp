/*

Implement the following operations of a stack using queues.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    empty() -- Return whether the stack is empty.

Notes:
1. You must use only standard operations of a queue 
   -- which means only push to back, peek/pop from front, size, and is empty operations are valid.

2. Depending on your language, queue may not be supported natively. 
   You may simulate a queue by using a list or deque (double-ended queue), 
   as long as you use only standard operations of a queue.

3. You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).

*/

#include <queue>
using namespace std;

// use only one queue!!!
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        int n = q.size();
        q.push(x);
        // move each element to the back
        for (int i = 0; i < n; ++i)
        {
            q.push(q.front());
            q.pop();
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        q.pop();
    }

    // Get the top element.
    int top() {
        return q.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q.empty();
    }
private:
    queue<int> q;
};

// same idea
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        q.push(x);
        for (int i = 0; i < size; ++i)
        {
            q.push(q.front());
            q.pop();
        }
        ++size;
    }

    // Removes the element on top of the stack.
    void pop() {
        q.pop();
        --size;
    }

    // Get the top element.
    int top() {
        return q.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return size == 0;
    }
private:
    queue<int> q;
    int size = 0;  // allowed in C++11: non-static data member initialized where it is declared (in its class). A constructor can then use the initializer when run-time initialization is needed
};