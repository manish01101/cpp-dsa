/*
arr[i] -> no. of pages in ith book
m -> no. of students
task is to allocate all the books
    -> each student gets at least one book
    -> each book should be allocated to a student
    -> book allocation should be in contiguous manner
allocate book to m-student such that the max no. of pages assigned to a student is minimum

arr => 10, 20, 30, 40
n = 4
m = 2
allocation :
        10 | 20, 30, 40 => max(10, 90) => 90
        10, 20 | 30, 40 => max(30, 70) => 70
        10, 20, 30 | 40 => max(60, 40) => 60
    ans => min(90, 70, 60) => 60

approach : create search space s=0 to e=sumofallelements
find mid = (s+e)/2
if not possible => then => s=mid+1
if possible => then => ans = mid & e = mid-1
*/
bool isPossible(int arr[], int n, int m, int mid) {
    int studentCount = 1;
    int pageSum = 0;

    for (int i = 0; i < n; i++) {
        if (pageSum + arr[i] <= mid) { // for first student
            pageSum += arr[i];
        }
        else {
            studentCount++;
            if (studentCount > m || arr[i] > mid) {
                return false;
            }
            pageSum = arr[i];
        }
    }
    return true;
}
int allocateBooks(int arr[], int n, int m) {
    int s = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    int e = sum;
    int ans = -1;
    int mid = (s + e) / 2;

    while (s <= e) {
        if (isPossible(arr, n, m, mid)) {
            ans = mid;
            e = mid - 1; //for min
        }
        else {
            s = mid + 1;
        }
    }
    return ans;
}