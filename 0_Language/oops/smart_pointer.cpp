#include<iostream>
#include<memory>
using namespace std;
/*
unique_ptr has exclusive ownership. You must use std::move() to transfer ownership.
shared_ptr allows multiple owners, and it maintains a reference count.
weak_ptr is a non-owning reference to a shared_ptr, often used to break cyclic references (like in graphs or doubly-linked lists).
*/

int main() {
    cout << "---- unique_ptr Example ----" << endl;
    unique_ptr<int> ptr_unique(new int(20));
    cout << "Value: " << *ptr_unique << endl;
    cout << "Address held by unique_ptr: " << ptr_unique << endl;
    cout << "Address of unique_ptr itself: " << &ptr_unique << endl;

    // unique_ptr can't be copied, but can be moved
    unique_ptr<int> ptr_unique2 = std::move(ptr_unique); // transfer ownership
    if (!ptr_unique) {
        cout << "ptr_unique is now nullptr after move." << endl;
    }
    cout << "Value from moved unique_ptr: " << *ptr_unique2 << endl;

    cout << "\n---- shared_ptr Example ----" << endl;
    shared_ptr<string> ptr_shared1 = make_shared<string>("manish");
    cout << "Value: " << *ptr_shared1 << endl;
    cout << "Address held by shared_ptr: " << ptr_shared1 << endl;
    cout << "Address of shared_ptr itself: " << &ptr_shared1 << endl;
    cout << "Use count: " << ptr_shared1.use_count() << endl;

    shared_ptr<string> ptr_shared2 = ptr_shared1; // shared ownership
    cout << "Use count after sharing: " << ptr_shared1.use_count() << endl;

    ptr_shared2.reset(); // decrease reference count
    cout << "Use count after reset: " << ptr_shared1.use_count() << endl;

    cout << "\n---- weak_ptr Example ----" << endl;
    weak_ptr<string> ptr_weak = ptr_shared1; // does not increase use_count
    cout << "Use count with weak_ptr: " << ptr_shared1.use_count() << endl;

    if (auto spt = ptr_weak.lock()) { // try to get shared_ptr from weak_ptr
        cout << "Accessing from weak_ptr: " << *spt << endl;
        cout << "Use count from locked weak_ptr: " << spt.use_count() << endl;
    } else {
        cout << "Object has been deleted" << endl;
    }

    ptr_shared1.reset(); // original shared_ptr goes out of scope
    if (ptr_weak.expired()) {
        cout << "weak_ptr expired after shared_ptr deleted" << endl;
    }

    return 0;
}
