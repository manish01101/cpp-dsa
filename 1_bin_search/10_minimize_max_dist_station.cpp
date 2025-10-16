/*
We have a horizontal number line. On that number line, we have gas stations at positions stations[0], stations[1], ..., stations[n-1]. Now, we add k more gas stations so that d, the maximum distance between adjacent gas stations, is minimized. We have to find the smallest possible value of d. Find the answer exactly to 2 decimal places.
Note: stations is in a strictly increasing order.
*/

class Solution {
    bool isPossible(vector<int>& stations, double allowed, int K) {
        int totalStation = 0;
        for (int i = 1; i < stations.size(); ++i) {
            int stationToBeAdded = double(stations[i] - stations[i - 1]) / allowed;
            if (stationToBeAdded >= 1) {
                totalStation += stationToBeAdded;
                if (totalStation > K)
                    return false;
            }
        }
        return true;
    }
public:
    double minMaxDist(vector<int>& stations, int K) {
        int n = stations.size();
        double s = 0;
        double e = stations[n - 1];

        double ans = 0;
        while (s <= e) {
            double mid = (s + e) / 2.0;
            if (isPossible(stations, mid, K)) {
                ans = mid;
                e = mid - 0.00001;
            }
            else {
                s = mid + 0.00001;
            }
        }
        return ans;
    }
};