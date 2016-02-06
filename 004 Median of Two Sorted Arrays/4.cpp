/*

There are two sorted arrays nums1 and nums2 of size m and n respectively. 
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

*/

#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int total = m + n;
        if (total % 2)
            return find_kth(A, m, B, n, total / 2);
        else
            return (find_kth(A, m, B, n, (total - 1) / 2) + find_kth(A, m, B, n, total / 2)) / 2.0;
    }

private:
    int find_kth(int A[], int m, int B[], int n, int k) {
        if (m == 0)
            return B[k];
        if (n == 0)
            return A[k];

        // A[0] ...... A[m-1/2]  A[m+1/2] ...... A[m-1]
        //    m+1/2 elements

        // B[0] ...... B[n-1/2]  B[n+1/2] ...... B[n-1]
        //    n+1/2 elements

        if (A[(m - 1) / 2] > B[(n - 1) / 2])
            if (k < (m + n) / 2)
                return find_kth(A, m / 2, B, n, k);  // also drop the middle if odd elements, because the middle is (m + n) / 2
            else
                return find_kth(A, m, B + (n + 1) / 2, n / 2, k - (n + 1) / 2);
        // if k = (m + n) / 2, which is (m+1)/2 + (n+1)/2 - 1
        // is the last element in A left and B left combined, which is A median
        // we shouldn't drop it, so don't put it in if, put it in else

        else
            if (k < (m + n) / 2)
                return find_kth(A, m, B, n / 2, k);
            else
                return find_kth(A + (m + 1) / 2, m / 2, B, n, k - (m + 1) / 2);

    }
};

int main()
{
    Solution s;
    int A[] {1, 2, 3};
    int B[] {1, 2, 2};
    s.findMedianSortedArrays(A, 3, B, 3);
}