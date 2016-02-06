/*

Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
    add(1); add(3); add(5);
    find(4) -> true
    find(7) -> false

*/

#include <unordered_map>
using namespace std;

// 1104ms, speed up by only checking the smaller one of the two number, and using .count() is faster than .find()
class TwoSum {
public:

    // Add the number to an internal data structure.
    void add(int number) {
        ++count[number];
    }

    // Find if there exists any pair of numbers which sum is equal to the value.
    bool find(int value) {
        for (auto& cnt : count)
            if (value - cnt.first < cnt.first && count.count(value - cnt.first) || value - cnt.first == cnt.first && cnt.second > 1)
                return true;
        return false;
    }

private:
    unordered_map<int, int> count;
};


// Your TwoSum object will be instantiated and called as such:
// TwoSum twoSum;
// twoSum.add(number);
// twoSum.find(value);