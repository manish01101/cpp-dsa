/*
875. Koko Eating Bananas
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.
*/
class Solution {
    bool isPossible(vector<int>& piles, int maxAllowed, int h) {
        for (int i = 0; i < piles.size(); ++i) {
            if (piles[i] <= maxAllowed) {
                --h;
            }
            else {
                int freq = (piles[i] + maxAllowed - 1) / maxAllowed;
                h -= freq;
            }
            if (h < 0)
                return false;
        }
        return true;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int s = 1;
        int e = *max_element(piles.begin(), piles.end());
        int ans = e;
        while (s <= e) {
            int mid = (s + e) / 2;
            if (isPossible(piles, mid, h)) {
                ans = mid;
                e = mid - 1;
            }
            else {
                s = mid + 1;
            }
        }
        return ans;
    }
};