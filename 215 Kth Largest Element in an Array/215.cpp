/*

Find the kth largest element in an unsorted array. 

Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note:
You may assume k is always valid, 1 ¡Ü k ¡Ü array's length.

*/

#include <vector>
#include <queue>
#include <set>
using namespace std;

// quickselect using partition (as in quicksort)
// best and average case O(n), T(n) = n + T(n/2)
// worst case O(n^2),          T(n) = n + T(n-1)
// could randomize the input to avoid worst case
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1, idx;
        while (true)
        {
            idx = partition(nums, left, right);
            if (idx == k - 1)
                return nums[idx];
            if (idx > k - 1)
                right = idx - 1;
            else
                left = idx + 1;
        }
    }
private:
    // put larger number before the pivot, smaller number after
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left], l = left + 1, r = right;
        while (l <= r)
        {
            if (nums[l] < pivot && nums[r] > pivot)
                swap(nums[l++], nums[r--]);
            else if (nums[l] >= pivot)
                ++l;
            else  // nums[r] <= pivot
                --r;
        }
        swap(nums[left], nums[r]);  // l could be out of range, but r is safe because r could be equal to "left"
        return r;
    }
};

// priority_queue: first element is always the greatest of the elements it contains
class Solution2 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> maxHeap(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; ++i)
            maxHeap.pop();
        return maxHeap.top();
    }
};

// heapselect, O(n + klogn)
class Solution3 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        build_max_heap(nums);
        for (int i = 0; i < k - 1; ++i)
        {
            swap(nums[0], nums[--heap_size]);
            max_heapify(nums, 0);
        }
        return nums[0];
    }
private:
    int heap_size;

    inline int left(int idx) {
        return (idx << 1) + 1;
    }

    inline int right(int idx) {
        return (idx << 1) + 2;
    }

    // siftdown
    void max_heapify(vector<int>& nums, int idx) {
        int largest = idx, l = left(idx), r = right(idx);
        if (l < heap_size && nums[l] > nums[largest])
            largest = l;
        if (r < heap_size && nums[r] > nums[largest])
            largest = r;
        if (largest != idx)
        {
            swap(nums[idx], nums[largest]);
            max_heapify(nums, largest);
        }
    }

    // bottom-up, O(n)
    // https://en.wikipedia.org/wiki/Binary_heap#Building_a_heap
    void build_max_heap(vector<int>& nums) {
        heap_size = nums.size();
        for (int i = (heap_size >> 1) - 1; i >= 0; --i) // last parent = (last node - 1) / 2 = (heap_size - 2) / 2
            max_heapify(nums, i);
    }
};

class Solution4 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int> mset;
        for (auto num : nums)
        {
            mset.insert(num);
            if (mset.size() > k)
                mset.erase(mset.begin());
        }
        return *mset.begin();
    }
};

// Blum-Floyd-Pratt-Rivest-Tarjan algorithm
// linear time selection
// https://en.wikipedia.org/wiki/Median_of_medians
// http://www.cs.princeton.edu/~wayne/cs423/lectures/selection-4up.pdf
// saved in project folder