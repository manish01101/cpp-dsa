#include <iostream>
#include <vector>
using namespace std;

class BIT {
private:
    vector<int> tree;
    int n;

public:
    BIT(int size) {
        n = size;
        tree.assign(n + 1, 0); // 1-based indexing
    }

    // Add 'val' to index 'idx' (0-based index)
    void update(int idx, int val) {
        idx++; // convert to 1-based index
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }

    // Get prefix sum from index 0 to idx (0-based index)
    int query(int idx) {
        idx++; // convert to 1-based index
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

    // Get sum of range [l, r] (both inclusive, 0-based)
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Build BIT from an array
    void build(const vector<int>& arr) {
        for (int i = 0; i < arr.size(); ++i)
            update(i, arr[i]);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    BIT bit(arr.size());

    bit.build(arr);

    cout << "Sum of range [1, 3]: " << bit.rangeQuery(1, 3) << endl; // 3+5+7 = 15

    bit.update(1, 7); // arr[1] += 7, now arr[1] = 10
    cout << "After update, sum of range [1, 3]: " << bit.rangeQuery(1, 3) << endl; // 10+5+7 = 22

    return 0;
}
