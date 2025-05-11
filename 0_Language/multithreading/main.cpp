/*
🔹 What is Multithreading?

Multithreading = running multiple tasks simultaneously (in parallel or concurrently) using multiple threads within the same process.

C++ supports multithreading through the <thread> and <mutex> libraries from C++11 onwards.
*/

// Basics: Threads in C++
// ✅ std::thread
#include <iostream>
#include <thread>
using namespace std;

void printHello() {
    cout << "Hello from thread!\n";
}

int main() {
    thread t(printHello); // Starts a new thread
    t.join();             // Wait for thread to finish
}
// ⚠️ Detaching a Thread: Detached threads are dangerous if your main program exits early!
void work() {
    cout << "Detached thread working...\n";
}

int main() {
    thread t(work);
    t.detach();  // Thread runs on its own
    this_thread::sleep_for(chrono::seconds(1)); // Give time for detached thread
}


// Passing Arguments to Threads
void sayHi(string name) {
    cout << "Hi, " << name << "!\n";
}

int main() {
    thread t(sayHi, "Alice");
    t.join();
}

// Synchronization with Mutex: Multiple threads accessing the same data? You need mutex.
// std::lock_guard or std::unique_lock ensures RAII-style safety.
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex m;

void increment() {
    for (int i = 0; i < 10000; ++i) {
        lock_guard<mutex> lock(m); // automatic unlock at end of scope
        ++counter;
    }
}

int main() {
    thread t1(increment), t2(increment);
    t1.join(); t2.join();
    cout << "Counter: " << counter << endl; // Should be 20000
}



// deadlocks: avoid this
// Deadlock happens if both threads lock the mutexes in opposite order.
// ✅ Use std::lock(m1, m2); + std::lock_guard with adopt_lock.
mutex m1, m2;

void taskA() {
    lock_guard<mutex> lock1(m1);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lock2(m2);
}

void taskB() {
    lock_guard<mutex> lock2(m2);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lock1(m1);
}


// ✅ std::async and std::future: Use when you want to run a function asynchronously and get the result back.
#include <iostream>
#include <future>
using namespace std;

int square(int x) {
    return x * x;
}

int main() {
    future<int> result = async(square, 6);
    cout << "Result: " << result.get() << endl; // 36
}

// Lock-Free Programming with std::atomic
// Lock-free = faster (no mutex overhead)
// std::atomic<T> supports ++, --, and compare_exchange operations safely.
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> counter(0);

void increment() {
    for (int i = 0; i < 10000; ++i) {
        counter++;
    }
}

int main() {
    thread t1(increment), t2(increment);
    t1.join(); t2.join();
    cout << "Atomic counter: " << counter << endl; // 20000
}



// Mini Project: Multithreaded Bank Account System

// 💡 Idea:
// A shared BankAccount object
// Multiple threads perform deposits and withdrawals
// Use std::mutex to prevent data races
// 🧱 Step-by-Step Plan
// Create a BankAccount class with:
// balance (private)
// deposit(int)
// withdraw(int)
// getBalance()
// Launch multiple threads that:
// Randomly deposit or withdraw money
// Print transaction info
// Use std::mutex to synchronize access.

#include <iostream>     // For input/output
#include <thread>       // For std::thread
#include <mutex>        // For std::mutex and std::lock_guard
#include <vector>       // For std::vector
#include <random>       // For random number generation
#include <chrono>       // For std::chrono and std::this_thread::sleep_for
using namespace std;

// Represents a thread-safe bank account allowing concurrent deposits and withdrawals
class BankAccount {
private:
    int balance;       // Account balance
    mutex m;           // Mutex to protect access to balance

public:
    // Constructor initializes balance to 0
    BankAccount() : balance(0) {}

    // Deposits amount into account; lock_guard ensures thread-safe access to balance
    void deposit(int amount) {
        lock_guard<mutex> lock(m);  // Lock is acquired here and released when it goes out of scope
        balance += amount;
        cout << "[Deposit] +" << amount << " | Balance: " << balance << endl;
    }

    // Withdraws amount if sufficient balance exists
    void withdraw(int amount) {
        lock_guard<mutex> lock(m);  // Lock to ensure safe access to balance
        if (balance >= amount) {
            balance -= amount;
            cout << "[Withdraw] -" << amount << " | Balance: " << balance << endl;
        } else {
            cout << "[Failed Withdrawal] -" << amount << " | Balance: " << balance << endl;
        }
    }

    // Returns the current balance in a thread-safe manner
    int getBalance() {
        lock_guard<mutex> lock(m);
        return balance;
    }
};

// Thread worker function
// Simulates banking operations by depositing and withdrawing randomly
void bankWorker(BankAccount& account, int id) {
    random_device rd;                             // Non-deterministic random seed
    mt19937 gen(rd());                            // Mersenne Twister random number generator
    uniform_int_distribution<> dist(1, 100);      // Uniform distribution of values between 1 and 100

    for (int i = 0; i < 5; ++i) {                 // Perform 5 operations per thread
        int op = dist(gen) % 2;                   // Randomly choose 0 (deposit) or 1 (withdraw)
        int amount = dist(gen);                   // Random transaction amount

        if (op == 0)
            account.deposit(amount);              // Perform deposit
        else
            account.withdraw(amount);             // Perform withdrawal

        // Simulates processing delay and increases likelihood of context switching between threads
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    BankAccount account;                          // Shared bank account instance

    vector<thread> threads;                       // Vector to store thread objects
    for (int i = 0; i < 4; ++i) {
        // Launch 4 threads, each performing random banking operations
        threads.emplace_back(bankWorker, ref(account), i + 1);
    }

    for (auto& t : threads) {
        t.join();                                 // Wait for all threads to complete
    }

    // Output the final balance after all operations
    cout << "Final Balance: " << account.getBalance() << endl;
    return 0;
}
