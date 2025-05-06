#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MyVector {
    T* data;
    size_t len;
    size_t cap;

    void resize(size_t new_cap) {
        cap = new_cap;
        T* new_data = new T[cap];
        for (size_t i = 0; i < len; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
    }

public:
    // Constructor
    MyVector() : data(nullptr), len(0), cap(0) {
        resize(1);
    }

    // Destructor
    ~MyVector() {
        delete[] data;
    }

    // Copy Constructor
    MyVector(const MyVector& other) {
        cap = other.cap;
        len = other.len;
        data = new T[cap];
        for (size_t i = 0; i < len; ++i)
            data[i] = other.data[i];
    }

    // Copy Assignment
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            cap = other.cap;
            len = other.len;
            data = new T[cap];
            for (size_t i = 0; i < len; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Move Constructor
    MyVector(MyVector&& other) noexcept : data(other.data), len(other.len), cap(other.cap) {
        other.data = nullptr;
        other.len = 0;
        other.cap = 0;
    }

    // Move Assignment
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            len = other.len;
            cap = other.cap;
            other.data = nullptr;
            other.len = 0;
            other.cap = 0;
        }
        return *this;
    }

    // push_back
    void push_back(const T& val) {
        if (len == cap) resize(cap * 2);
        data[len++] = val;
    }

    // pop_back
    void pop_back() {
        if (len > 0) --len;
    }

    // insert at index
    void insert(size_t index, const T& val) {
        if (index > len) throw out_of_range("Index out of range");
        if (len == cap) resize(cap * 2);
        for (size_t i = len; i > index; --i)
            data[i] = data[i - 1];
        data[index] = val;
        ++len;
    }

    // erase at index
    void erase(size_t index) {
        if (index >= len) throw out_of_range("Index out of range");
        for (size_t i = index; i < len - 1; ++i)
            data[i] = data[i + 1];
        --len;
    }

    // clear
    void clear() {
        len = 0;
    }

    // operator[]
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // at() with bounds checking
    T& at(size_t index) {
        if (index >= len) throw out_of_range("Index out of range");
        return data[index];
    }

    // size and capacity
    size_t size() const { return len; }
    size_t capacity() const { return cap; }
    bool empty() const { return len == 0; }

    // Iterators (basic)
    T* begin() { return data; }
    T* end() { return data + len; }

    // print for debugging
    void print() const {
        for (size_t i = 0; i < len; ++i)
            cout << data[i] << " ";
        cout << endl;
    }
};

int main() {
    MyVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.insert(1, 15);   // [10, 15, 20, 30]
    v.erase(2);        // [10, 15, 30]
    v.print();

    v.pop_back();      // [10, 15]
    v.print();

    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;

    for (auto x : v) cout << x << " ";
    cout << endl;

    v.clear();
    cout << "Cleared. Is empty? " << v.empty() << endl;
}

