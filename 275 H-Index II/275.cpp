/*

Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?

Hint:
Expected runtime complexity is in O(log n) and the input is sorted.

*/

#include <vector>
using namespace std;

// find the first i where citations[i] >= n - i
// two-branch binary search, more efficient?
class Solution2 {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size(), start = 0, end = n - 1, mid;
        while (start <= end)
        {
            mid = start + (end - start) / 2;
            if (citations[mid] < n - mid)
                start = mid + 1;
            else
                end = mid - 1;
        }  // break when start == end + 1
        return n - start;
    }
};

// same idea
// three-branch binary search
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size(), start = 0, end = n - 1, mid;
        while (start <= end)
        {
            mid = start + (end - start) / 2;
            if (citations[mid] == n - mid)
                return n - mid;
            else if (citations[mid] < n - mid)
                start = mid + 1;
            else
                end = mid - 1;
        }  // break when start == end + 1
        return n - start;
    }
};