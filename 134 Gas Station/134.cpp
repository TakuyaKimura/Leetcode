/*

There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). 

You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.

*/

#include <vector>
using namespace std;

/**

Theorem: if the total gas is greater than the total cost,
         i.e., gas(1) + gas(2) + ¡­ + gas(n) > cost(1) + cost(2) + ¡­ + cost(n),
         there must be a way to travel around the circuit once.

Proof:

  - If there is only one gas station, it¡¯s true.

  - If there are two gas stations a and b, and gas(a) cannot afford cost(a), i.e., gas(a) < cost(a),
    then gas(b) must be greater than cost(b), i.e., gas(b) > cost(b), since gas(a) + gas(b) > cost(a) + cost(b);
    so there must be a way too.

  - If there are three gas stations a, b, and c, where gas(a) < cost(a), i.e., we cannot travel from a to b directly, then:

      - either if gas(b) < cost(b), i.e., we cannot travel from b to c directly,
        then cost(c) > cost(c), so we can start at c and travel to a;
        since gas(b) < cost(b), gas(c) + gas(a) must be greater than cost(c) + cost(a),
        so we can continue traveling from a to b.
        Key Point: this can be considered as there is one station at c¡¯ with gas(c¡¯) = gas(c) + gas(a)
        and the cost from c¡¯ to b is cost(c¡¯) = cost(c) + cost(a), and the problem reduces to a problem with two stations.
        This in turn becomes the problem with two stations above.

      - or if gas(b) >= cost(b), we can travel from b to c directly.
        Similar to the case above, this problem can reduce to a problem with two stations b¡¯ and a,
        where gas(b¡¯) = gas(b) + gas(c) and cost(b¡¯) = cost(b) + cost(c).
        Since gas(a) < cost(a), gas(b¡¯) must be greater than cost(b¡¯), so it¡¯s solved too.

  - For problems with more stations, we can reduce them in a similar way.
    In fact, as seen above for the example of three stations, the problem of two stations can also reduce to the initial problem with one station.

*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // left: leaving from start, arriving at 0, how much gas is left
        // need: leaving from 0, arriving at start, how much gas in the tank is needed
        // (taking gas from the station when leaving, not arriving)
        int left = 0, needed = 0, start = 0, n = gas.size();
        for (int i = 0; i < n; ++i)
        {
            left += gas[i] - cost[i];
            if (left < 0)
            {
                needed -= left;
                left = 0;
                start = i + 1;
            }
        }
        return needed <= left ? start : -1;

    }
};