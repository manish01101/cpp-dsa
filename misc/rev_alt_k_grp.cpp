/*everse elements in alternate k-sized groups within both the div and nondiv vectors. The logic handles the condition where the remaining elements are less than k by reversing them as well*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    // Read n first
    if (!(cin >> n)) return 0;

    // Use std::vector for dynamic sizing
    vector<int> arr(n); 
    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }
    
    int x, k;
    cin >> x >> k;
    
    vector<int> div, nondiv;
    for(int i=0; i<n; ++i) {
        if(arr[i] % x == 0) {
            div.push_back(arr[i]);
        }
        else {
            nondiv.push_back(arr[i]);
        }
    }

    // --- Corrected logic for reversing alternate k-sized chunks ---

    // Function to handle the alternate reversal logic for any vector
    auto reverseAlternateK = [&](vector<int>& v, int K) {
        for (int i = 0; i < v.size(); i += 2 * K) {
            // Reverse the first K elements of the current 2K block
            auto start_it = v.begin() + i;
            // The end of the range is limited by the actual size of the vector
            auto end_it = min(v.begin() + i + K, v.end());
            std::reverse(start_it, end_it);
            
            // The loop increment `i += 2 * K` automatically skips the next K elements
            // which should remain in their original order.
        }
    };

    // Apply the function to both vectors
    reverseAlternateK(div, k);
    reverseAlternateK(nondiv, k);

    // --- Merging logic ---
    
    vector<int> ans;
    int a = 0, b = 0;
    while(a < div.size() && b < nondiv.size()) {
        ans.push_back(div[a++]);
        ans.push_back(nondiv[b++]);
    }
    while(a < div.size()) {
        ans.push_back(div[a++]);
    }
    while(b < nondiv.size()) {
        ans.push_back(nondiv[b++]);
    }
    
    for(auto const& val : ans) {
        cout << val << " ";
    }
    cout << endl; // Add a newline at the end of output
    
    return 0;
}
