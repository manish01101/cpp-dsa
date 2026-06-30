#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;
/*
| Situation                                                    | Function Called              |
| ------------------------------------------------------------ | ---------------------------- |
| create a new object from another → `MyString b = a;` | Copy constructor         |
| assign to an existing object → `b = a;`              | Copy assignment operator |
*/
class MyString {
    char* data;
    size_t len;

public:
    // Default Constructor
    MyString() : data(new char[1] {'\0'}), len(0) { }

    // Constructor from const char*
    MyString(const char* str) {
        len = strlen(str);
        data = new char[len + 1];
        strcpy(data, str);
    }

    // Copy Constructor
    MyString(const MyString& other) {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
    }

    // Move Constructor
    MyString(MyString&& other) noexcept : data(other.data), len(other.len) {
        other.data = new char[1] {'\0'};
        other.len = 0;
    }

    // Copy Assignment
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            len = other.len;
            data = new char[len + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // Move Assignment
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            len = other.len;
            other.data = new char[1] {'\0'};
            other.len = 0;
        }
        return *this;
    }

    // Destructor
    ~MyString() {
        delete[] data;
    }

    // Length
    size_t length() const {
        return len;
    }

    // c_str
    const char* c_str() const {
        return data;
    }

    // Clear
    void clear() {
        delete[] data;
        data = new char[1] {'\0'};
        len = 0;
    }

    // Empty
    bool empty() const {
        return len == 0;
    }

    // Operator []
    char& operator[](size_t index) {
        if (index >= len) throw out_of_range("Index out of range");
        return data[index];
    }

    const char& operator[](size_t index) const {
        if (index >= len) throw out_of_range("Index out of range");
        return data[index];
    }

    // Operator ==
    bool operator==(const MyString& other) const {
        return strcmp(data, other.data) == 0;
    }

    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }

    // Operator +=
    MyString& operator+=(const MyString& other) {
        size_t new_len = len + other.len;
        char* new_data = new char[new_len + 1];
        strcpy(new_data, data);
        strcat(new_data, other.data);

        delete[] data;
        data = new_data;
        len = new_len;
        return *this;
    }

    // Operator +
    friend MyString operator+(const MyString& a, const MyString& b) {
        MyString result = a;
        result += b;
        return result;
    }

    // Stream output <<
    friend ostream& operator<<(ostream& os, const MyString& str) {
        return os << str.data;
    }

    // Stream input >>
    friend istream& operator>>(istream& is, MyString& str) {
        char buffer[1000];
        is >> buffer;
        str = MyString(buffer);
        return is;
    }
};

int main() {
    MyString a("Hello");
    MyString b(" World");
    MyString c = a + b;

    cout << "Concatenated: " << c << endl;
    cout << "Length: " << c.length() << endl;
    cout << "Char at 1: " << c[1] << endl;

    c[0] = 'h';
    cout << "Modified: " << c << endl;

    if (c != a)
        cout << "c and a are different" << endl;

    MyString input;
    cout << "Enter something: ";
    cin >> input;
    cout << "You entered: " << input << endl;
}


/* 
-------- updated version -------
| Concept                  | Meaning                             | Why it matters                        |
| ------------------------ | ----------------------------------- | ------------------------------------- |
| `explicit`               | Prevents automatic type conversion  | Avoids unintended constructor calls   |
| `char&` vs `const char&` | Allows modifying vs. only reading   | Enables correct const usage           |
| `memcpy`                 | Copies fixed-size raw memory blocks | Faster and safer when you know length |


*/

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <string>   // for safe input
using namespace std;

class MyString {
    char* data;
    size_t len;

public:
    // --- Constructors ---
    MyString() noexcept : data(new char[1]{'\0'}), len(0) {}

    explicit MyString(const char* str) {
        if (!str) str = ""; // handle nullptr safely
        len = strlen(str);
        data = new char[len + 1];
        memcpy(data, str, len + 1); // faster than strcpy
    }

    // Copy Constructor
    MyString(const MyString& other)
        : data(new char[other.len + 1]), len(other.len) {
        memcpy(data, other.data, len + 1);
    }

    // Move Constructor
    MyString(MyString&& other) noexcept
        : data(other.data), len(other.len) {
        other.data = nullptr;
        other.len = 0;
    }

    // Destructor
    ~MyString() { delete[] data; }

    // --- Assignment Operators ---
    // Copy Assignment (copy-and-swap idiom)
    MyString& operator=(MyString other) noexcept {
        swap(*this, other);
        return *this;
    }

    // --- Swap helper ---
    friend void swap(MyString& a, MyString& b) noexcept {
        std::swap(a.data, b.data);
        std::swap(a.len, b.len);
    }

    // --- Member Functions ---
    size_t length() const noexcept { return len; }
    bool empty() const noexcept { return len == 0; }
    const char* c_str() const noexcept { return data; }

    void clear() noexcept {
        delete[] data;
        data = new char[1]{'\0'};
        len = 0;
    }

    // --- Element Access ---
    char& operator[](size_t index) {
        if (index >= len) throw out_of_range("Index out of range");
        return data[index];
    }

    const char& operator[](size_t index) const {
        if (index >= len) throw out_of_range("Index out of range");
        return data[index];
    }

    // --- Comparison ---
    bool operator==(const MyString& other) const noexcept {
        return strcmp(data, other.data) == 0;
    }

    bool operator!=(const MyString& other) const noexcept {
        return !(*this == other);
    }

    // --- Concatenation ---
    MyString& operator+=(const MyString& other) {
        size_t new_len = len + other.len;
        char* new_data = new char[new_len + 1];
        memcpy(new_data, data, len);
        memcpy(new_data + len, other.data, other.len + 1);
        delete[] data;
        data = new_data;
        len = new_len;
        return *this;
    }

    friend MyString operator+(MyString a, const MyString& b) {
        a += b; // move-optimized since 'a' is by value
        return a; // RVO or move
    }

    // --- Stream Operators ---
    friend ostream& operator<<(ostream& os, const MyString& s) {
        return os << s.data;
    }

    friend istream& operator>>(istream& is, MyString& s) {
        std::string temp;
        is >> temp; // automatically resizes
        s = MyString(temp.c_str());
        return is;
    }
};
