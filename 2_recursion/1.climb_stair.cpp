/*
steps coverd at a time => 1 or 2
f(n) = f(n-1) + f(n-2)
base case:
    if(n<0) return 0
    if(n==0) return 1
*/

int countDistinctWay(long long n) {
    // base case
    if(n < 0) return 0;
    if(n == 0) return 1;

    // rec rel
    return countDistinctWay(n-1) + countDistinctWay(n-2);
}