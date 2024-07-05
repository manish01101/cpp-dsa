#include<iostream>
using namespace std;

int sqrtInt(int n) {
    int s = 0, e = n;
    int ans = -1;
    while (s <= e) {
        long long mid = (s+e)/2;
        if(mid*mid == n) {
            return mid;
        }
        else if(mid*mid < n) {
            ans = mid;
            s = mid + 1;
        }
        else if(mid*mid > n) {
            e = mid - 1;
        }
    }
    return ans;
}
double sqrtDecimal(int n, int precision, int intSol) {
    double factor = 1;
    double ans = intSol;
    for(int i=0; i<precision; i++) {
        factor = factor/10; // i=0 => factor=0.1, i=1 => fac=0.01 ...
        for(double j = ans; j*j < n; j+=factor) {
            ans = j;
        }
    }
    return ans;
}
int main() {
    int intSol = sqrtInt(39);
    double floatSol = sqrtDecimal(37, 3, intSol);
    cout << floatSol << endl;
}