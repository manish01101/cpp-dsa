

bool isSorted(int arr[], int size) {
    // base case
    if (size == 0 || size == 1) return true;

    if (arr[0] > arr[1]) {
        return false;
    }
    else {
        return isSorted(arr + 1, size - 1);
    }
}

int getSum(int* arr, int size) {
    //base case
    if (size == 0) return 0;
    if (size == 1) return arr[0];

    return arr[0] + getSum(arr + 1, size - 1);
}

// linear search
int linearSearch(int* arr, int size, int key) {
    if (size == 0) return -1;
    if (arr[0] == key) return 0; 

    int result = linearSearch(arr + 1, size - 1, key);
    return (result == -1) ? -1 : result + 1;
}

// binary search
int binarySearch(int* arr, int s, int e, int key) {
    // base case
    if (s > e) return -1;

    int mid = (s + e) / 2;

    if (key == arr[mid]) {
        return mid;
    }
    else if (key < arr[mid]) { // search left part
        return binarySearch(arr, s, mid - 1, key);
    }
    else { // search right part
        return binarySearch(arr, mid + 1, e, key);
    }
}