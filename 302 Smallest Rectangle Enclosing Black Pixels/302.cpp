/*

An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. 

The black pixels are connected, i.e., there is only one black region. 

Pixels are connected horizontally and vertically. 

Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle 
that encloses all black pixels.

For example, given the following image:

    [
        "0010",
        "0110",
        "0100"
    ]

and x = 0, y = 2,
Return 6.

*/

#include <vector>
using namespace std;

class Solution {
public:
	int minArea(vector<vector<char>>& image, int x, int y) {
		int left = searchCols(image, 0, y, true);
		int right = searchCols(image, y + 1, image[0].size() - 1, false);
		int top = searchRows(image, 0, x, true);
		int bottom = searchRows(image, x + 1, image.size() - 1, false);
		return (right - left) * (bottom - top);
	}

private:
	int searchCols(vector<vector<char>>& image, int start, int end, bool black) {
		int m = image.size(), mid, i;
		while (start <= end)
		{
			mid = (start + end) / 2;
			for (i = 0; i < m; ++i)
				if (image[i][mid] == '1')
					break;

			if (i < m == black)
				end = mid - 1;
			else
				start = mid + 1;
		}
		return start;
	}

	int searchRows(vector<vector<char>>& image, int start, int end, bool black) {
		int n = image[0].size(), mid, i;
		while (start <= end)
		{
			mid = (start + end) / 2;
			for (i = 0; i < n; ++i)
				if (image[mid][i] == '1')
					break;

			if (i < n == black)
				end = mid - 1;
			else
				start = mid + 1;
		}
		return start;
	}
};