#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <semaphore> // Requires C++20

using namespace std;

// --- 1. Using std::atomic ---
// std::atomic provides lock-free, atomic operations for basic data types.
atomic<int> atomic_counter(0);

void increment_atomic() {
    for (int i = 0; i < 1000; ++i) {
        // fetch_add performs an atomic increment.
        atomic_counter.fetch_add(2, memory_order_relaxed);
    }
}

// --- 2. Using std::mutex ---
// std::mutex is a locking mechanism for protecting shared resources that require a critical section.
mutex mtx;
int shared_resource = 0;

void increment_mutex() {
    for (int i = 0; i < 1000; ++i) {
        // Lock the mutex before entering the critical section.
        mtx.lock();
        shared_resource++;
        // Unlock the mutex when exiting the critical section.
        mtx.unlock();
    }
}

// For automatic locking and unlocking (exception safe), use std::lock_guard or std::unique_lock.
void increment_mutex_safe() {
    for (int i = 0; i < 1000; ++i) {
        lock_guard<mutex> guard(mtx);
        shared_resource++;
    }
}

// --- 3. Using std::counting_semaphore (C++20) ---
// A semaphore is a signaling mechanism that controls access to resources by multiple threads through a counter.
// Here, we limit access to a certain operation to 3 threads at a time.
counting_semaphore<3> resource_semaphore(3); // Initialize with 3 available resources

void limited_resource_access(int thread_id) {
    // Acquire a permit from the semaphore (wait operation).
    resource_semaphore.acquire();
    cout << "Thread " << thread_id << " acquired resource. Count: " << resource_semaphore.max() << endl;

    // Simulate some work in the critical section.
    this_thread::sleep_for(chrono::seconds(1));

    cout << "Thread " << thread_id << " releasing resource." << endl;
    // Release the permit (signal operation).
    resource_semaphore.release();
}


int main() {
    cout << "--- Atomic Example ---" << endl;
    thread t1(increment_atomic);
    thread t2(increment_atomic);
    t1.join();
    t2.join();
    cout << "Atomic Counter Result: " << atomic_counter << endl << endl;

    cout << "--- Mutex Example ---" << endl;
    thread t3(increment_mutex_safe);
    thread t4(increment_mutex_safe);
    t3.join();
    t4.join();
    cout << "Mutex Shared Resource Result: " << shared_resource << endl << endl;

    cout << "--- Semaphore Example (C++20 required) ---" << endl;
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(limited_resource_access, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}