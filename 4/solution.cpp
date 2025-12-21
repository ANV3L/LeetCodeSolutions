#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int N = nums1.size();
        int M = nums2.size();

        if (N >  M) return findMedianSortedArrays(nums2, nums1);

        int low{0}, high{N};

        while (low <= high){
            int p1 = low + (high - low) / 2;
            int p2 = (M + N + 1) / 2 - p1;

            int maxL1 = (p1) ? nums1[p1 - 1] : INT_MIN;
            int minR1 = (p1 == N) ? INT_MAX : nums1[p1];
            
            int maxL2 = (p2) ? nums2[p2 - 1] : INT_MIN;
            int minR2 = (p2 == M) ? INT_MAX : nums2[p2];

            if (maxL1 <= minR2 && maxL2 <= minR1){
                if ((M + N) % 2) {
                    return std::max(maxL1, maxL2);
                } else {
                     return (std::max(maxL1, maxL2) + std::min(minR1, minR2)) / 2.0;
                }
            } else if (maxL1 > minR2) {
                high = p1 - 1;
            } else {
                low = p1 + 1;
            }
        } 

        return 0.0;
    }

};
