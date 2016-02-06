/*

Median is the middle value in an ordered integer list. 

If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples:
    [2,3,4] , the median is 3

    [2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

    void addNum(int num) - Add a integer number from the data stream to the data structure.
    double findMedian() - Return the median of all elements so far.

For example:

    add(1)
    add(2)
    findMedian() -> 1.5
    add(3)
    findMedian() -> 2

*/

#include <queue>
#include <functional>  // std::greater<int>
#include <iostream>
using namespace std;

class MedianFinder {
public:

    // Adds a number into the data structure.
    void addNum(int num) {
		if (maxHeap.size() == minHeap.size())
		{
			minHeap.push(num);
			maxHeap.push(minHeap.top());
			minHeap.pop();
		}
		else
		{
			maxHeap.push(num);
			minHeap.push(maxHeap.top());
			maxHeap.pop();
		}
	}

	// Returns the median of current data stream
	double findMedian() {
		if (maxHeap.size() == minHeap.size())
			return ((long long)maxHeap.top() + minHeap.top()) / 2.0;  // note "2.0", and long long in case of overflow
		return maxHeap.top();
	}

private:
	priority_queue<int> maxHeap;                             // smaller half
	priority_queue<int, vector<int>, greater<int>> minHeap;  // larger half
};

class MedianFinder2 {
public:

	// Adds a number into the data structure.
	void addNum(int num) {
		small.push(num);
		large.push(-small.top());
		small.pop();
		if (large.size() > small.size())
		{
			small.push(-large.top());
			large.pop();
		}
	}

	// Returns the median of current data stream
	double findMedian() {
		if (small.size() == large.size())
			return (small.top() - large.top()) / 2.0;  // notice it's minus, not plus
		return small.top();
	}

private:
	priority_queue<long long> small, large;  // negating num when pushing into large, so that it's a minHeap
											 // if num == INT_MIN, then it'll overflow, so use long long
};

class MedianFinder3 {
public:

	// Adds a number into the data structure.
	void addNum(int num) {
		if (maxHeap.empty() || num < maxHeap.top())
			maxHeap.push(num);
		else
			minHeap.push(num);

		if (minHeap.size() > maxHeap.size())
		{
			maxHeap.push(minHeap.top());
			minHeap.pop();
		}
		else if (minHeap.size() + 1 < maxHeap.size())
		{
			minHeap.push(maxHeap.top());
			maxHeap.pop();
		}
	}

	// Returns the median of current data stream
	double findMedian() {
		if (maxHeap.size() == minHeap.size())
			return ((long long)maxHeap.top() + minHeap.top()) / 2.0;  // note "2.0", and long long in case of overflow
		return maxHeap.top();
	}

private:
	priority_queue<int> maxHeap;                             // smaller half
	priority_queue<int, vector<int>, greater<int>> minHeap;  // larger half
};


// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();