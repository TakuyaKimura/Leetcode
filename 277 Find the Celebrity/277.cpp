/*

Suppose you are at a party with n people (labeled from 0 to n - 1) and among them, there may exist one celebrity. 

The definition of a celebrity is that all the other n - 1 people know him/her but he/she does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. 

The only thing you are allowed to do is to ask questions like: 
"Hi, A. Do you know B?" to get information of whether A knows B. 

You need to find out the celebrity (or verify there is not one) 
by asking as few questions as possible (in the asymptotic sense).

You are given a helper function bool knows(a, b) which tells you whether A knows B. 

Implement a function int findCelebrity(n), your function should minimize the number of calls to knows.

Note: 
There will be exactly one celebrity if he/she is in the party. 
Return the celebrity's label if there is a celebrity in the party. If there is no celebrity, return -1.

*/

#include <algorithm>
using namespace std;

// Forward declaration of the knows API.
bool knows(int a, int b);

// two-pass, 248ms
// find the candidate in only n - 1 checks
// at most 3n - 3 checks in total
class Solution {
public:
    int findCelebrity(int n) {
        int candidate = 0;

        // we won't miss a candidate
        // because if i was a candidate, then !knows(i, currentCandidate), then candidate = i
        for (int i = 1; i < n; ++i)
            // if (knows(candidate, i))  // same thing
            if (!knows(i, candidate))    // only checking i's after the candidate
                candidate = i;

        for (int i = 0; i < n; ++i)
            if (i != candidate && (!knows(i, candidate) || knows(candidate, i)))
                return -1;

        return candidate;
    }
};

// two-pass, 224ms
class Solution2 {
public:
    int findCelebrity(int n) {
        int candidate = 0;

        for (int i = 1; i < n; ++i)
            if (!knows(i, candidate))
                candidate = i;

        for (int i = 0; i < n; ++i)
            if (i != candidate && knows(candidate, i))
                return -1;

        for (int i = 0; i < candidate; ++i)  // all the j's after candidate are already checked in the first loop
            if (!knows(i, candidate))
                return -1;

        return candidate;
    }
};

// one-pass, but could make (1 + 2 + ... + n - 1) checks, 276ms
class Solution3 {
public:
    int findCelebrity(int n) {
        int a, b = 0;
        while (b < n)
        {
            for (a = 0; a < n && (a == b || knows(a, b) && !knows(b, a)); ++a) {}
            if (a == n)
                return b;
            b = max(b + 1, a);
        }
        return -1;
    }
};

// one-pass, 256ms, may still do redundant checks 
// because we are checking both knows(a, b) and knows(b, a) without knowing whether b is not a proper candidate
class Solution4 {
public:
    int findCelebrity(int n) {
        int a, b = 0, temp;
        while (b < n)
        {
            for (a = b + 1; a < n && knows(a, b) && !knows(b, a); ++a) {}
            temp = a;
            if (a == n)
            {
                for (a = 0; a < b && knows(a, b) && !knows(b, a); ++a) {}
                if (a == b)
                    return b;
            }
            b = temp;
        }
        return -1;
    }
};