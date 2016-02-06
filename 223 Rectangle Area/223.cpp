/*

Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Assume that the total area is never beyond the maximum possible value of int.

*/

#include <algorithm>
using namespace std;

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int overlap_width = min(C, G) > max(A, E) ? min(C, G) - max(A, E) : 0;  // if a<b, a-b could overflow, max(a-b, 0) is not correct
        int overlap_height = min(D, H) > max(B, F) ? min(D, H) - max(B, F) : 0;
        // because the total area is guaranteed not to overflow
        // it's OK for the sum of the first two terms to overflow
        return (C - A) * (D - B) + (G - E) * (H - F) - overlap_width * overlap_height;
    }
};

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        return (C - A) * (D - B) + (G - E) * (H - F) - (C <= E || G <= A || D <= F || H <= B ? 0 : (min(C, G) - max(A, E)) * (min(D, H) - max(B, F)));
    }
};