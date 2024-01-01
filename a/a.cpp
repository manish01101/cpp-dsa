#include<iostream>
#include<vector>

using namespace std;
class Solution {
public:
    int dominantPairs(int n, int arr[]) {
        int count = 0;
        // int i = 0;
        // while (i < n / 2) {
        //     int j = n / 2;
        //     while (j < n) {
        //         if (arr[i] >= 5 * arr[j]) {
        //             count++;
        //         }
        //         j++;
        //     }
        //     i++;
        // }
        for(int i=0, j=n/2; i<n/2, j<n; i++, j++) {
            if(arr[i]>=5*arr[j]) {
                count++;
            }
            if(j==n-1) {
                j = n/2;
                i++;
            }
            i--;
        }
        return count;
    }
};
int main() {
    int arr[6] = {10,8,2,1,1,2};
    int n = 6;
    Solution s;
    std::cout << s.dominantPairs(n, arr) << std::endl;
    return 0;
}