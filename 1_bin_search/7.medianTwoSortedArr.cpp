/*
create partition: left pool & right pool (both should have equal ele if total ele is even else half+1 ele in left pool if odd)
check for correct partition: max ele of left pool < min ele of right pool
demo: nums1 = [..., x | y, ...]	nums2 = [..., p | q, ...]
	then x <= q and p <= y
*/
class Solution { // tc: O(log(min(m, n)))
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int n1 = nums1.size();
		int n2 = nums2.size();
		if (n1 > n2)
			return findMedianSortedArrays(nums2, nums1);

		int l = 0;
		int r = n1;

		while (l <= r) {
			int partition1 = (l + r) / 2;
			int partition2 = (n1 + n2 + 1) / 2 - partition1;

			int maxLeft1 = partition1 == 0 ? INT_MIN : nums1[partition1 - 1];
			int maxLeft2 = partition2 == 0 ? INT_MIN : nums2[partition2 - 1];

			int minRight1 = partition1 == n1 ? INT_MAX : nums1[partition1];
			int minRight2 = partition2 == n2 ? INT_MAX : nums2[partition2];

			if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1)
				if ((n1 + n2) % 2 == 0)
					return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
				else
					return max(maxLeft1, maxLeft2);
			else if (maxLeft1 > minRight2)
				r = partition1 - 1;
			else if(maxLeft2 > minRight1)
				l = partition1 + 1;
		}

		return double(0);
	}
};

class Solution { // tc: O((m + n)/2) = O(m + n)
    int i=0, j=0;

    int findMin(vector<int> &nums1, vector<int> &nums2) {
        if(i < nums1.size() && j < nums2.size()) {
            if(nums1[i] < nums2[j]) {
                return nums1[i++];
            }
            else {
                return nums2[j++];
            }
        }
        else if(i < nums1.size()) 
            return nums1[i++];
        else if(j < nums2.size())
            return nums2[j++];
        return -1;
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m=nums1.size(), n=nums2.size();

        if((m+n)%2 == 0) { // for even size
            for(int i=0; i < (m+n)/2-1; ++i) {
                int _ = findMin(nums1, nums2);
            }
            // now fetch middle two ele
            return (double)(findMin(nums1, nums2)+findMin(nums1, nums2))/2;
        }
        else { // for odd size
            for(int i=0; i<(m+n)/2; ++i) {
                int _ = findMin(nums1, nums2);
            }
            return findMin(nums1, nums2);
        }

        return -1;
    }
};