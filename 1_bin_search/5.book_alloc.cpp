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

    while (s <= e) {
        int mid = (s + e) / 2;
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

bool isValid(int maxAllowedPages, int arr[], int n, int k) {
    int studentCnt = 1;
    int bookPages = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxAllowedPages) { // pages > maxAllowed
            return false;
        }
        if (bookPages + arr[i] <= maxAllowedPages) {
            bookPages += arr[i];
        }
        else { // allocate to new student
            studentCnt++;
            bookPages = arr[i]; // pages assigned to new student
        }
    }
    if (studentCnt > k) return false;
    return true;
}
int findPages(int arr[], int n, int k) {
    if (n < k) return -1;

    int sumPages = 0;
    for (int i = 0; i < n; i++) {
        sumPages += arr[i];
    }

    int s = 0, e = sumPages, ans = -1;
    while (s <= e) {
        int mid = s + (e - s) / 2;
        if (isValid(mid, arr, n, k)) {
            ans = mid;
            e = mid - 1;
        }
        else {
            s = mid + 1;
        }
    }
    return ans;
}