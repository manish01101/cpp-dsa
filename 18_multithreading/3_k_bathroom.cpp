/*
Problem:
there are K bathrooms in the office:
    Each bathroom obeys the same rules:
        Max 3 people inside at once.
        No mixing of genders inside one bathroom.
    But multiple bathrooms can be used in parallel.
    A new person should choose any available bathroom that allows them (same gender or empty).
We must:
    Maintain fairness and avoid starvation (like before),
    Ensure no two threads enter the same bathroom incorrectly.

design approach:
treat each bathroom as an independent resource but protected by a shared manager.
Two Layers
    Bathroom class (same as before) — manages internal rules for 1 bathroom.
    BathroomManager class — tracks multiple bathrooms and assigns threads to one that’s available.
*/

#include <bits/stdc++.h>
using namespace std;

class UnisexBathroom {
private:
    int counter = 0; // +ve for males, -ve for females
    string turn = "none";
    int waitingMales = 0, waitingFemales = 0;
    mutex mtx;
    condition_variable cv;

public:
    void useBathroom(const string& gender, const string& name) {
        unique_lock<mutex> lock(mtx);

        if (gender == "male") waitingMales++;
        else waitingFemales++;

        cv.wait(lock, [&] {
            if (gender == "male")
                return ((counter >= 0 && counter < 3) &&
                    (turn == "male" || turn == "none"));
            else
                return ((counter <= 0 && counter > -3) &&
                    (turn == "female" || turn == "none"));
            });

        // Enter
        if (gender == "male") {
            waitingMales--;
            if (turn == "none") turn = "male";
            counter++;
            cout << name << " entered (M) | males: " << counter << endl;
        }
        else {
            waitingFemales--;
            if (turn == "none") turn = "female";
            counter--;
            cout << name << " entered (F) | females: " << -counter << endl;
        }

        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(200)); // simulate use
        lock.lock();

        // Exit
        if (gender == "male") {
            counter--;
            cout << name << " leaving (M)" << endl;
        }
        else {
            counter++;
            cout << name << " leaving (F)" << endl;
        }

        if (counter == 0) {
            if (waitingMales > 0)
                turn = "male";
            else if (waitingFemales > 0)
                turn = "female";
            else
                turn = "none";
        }
        cv.notify_all();
    }

    bool tryEnter(const string& gender) {
        lock_guard<mutex> lock(mtx);
        if (gender == "male")
            return (counter >= 0 && counter < 3);
        else
            return (counter <= 0 && counter > -3);
    }
};

class BathroomManager {
private:
    vector<shared_ptr<UnisexBathroom>> bathrooms;
    int nBathrooms;

public:
    BathroomManager(int n) : nBathrooms(n) {
        for (int i = 0; i < n; ++i)
            bathrooms.push_back(make_shared<UnisexBathroom>());
    }

    void useBathroom(const string& gender, const string& name) {
        while (true) {
            for (auto& bath : bathrooms) {
                if (bath->tryEnter(gender)) {
                    bath->useBathroom(gender, name);
                    return;
                }
            }
            this_thread::sleep_for(chrono::milliseconds(50)); // retry
        }
    }
};

// Wrappers
void male(BathroomManager* mgr, string name) {
    mgr->useBathroom("male", name);
}
void female(BathroomManager* mgr, string name) {
    mgr->useBathroom("female", name);
}

int main() {
    BathroomManager mgr(2); // 2 bathrooms

    vector<thread> threads = {
        thread(male, &mgr, "Aman"),
        thread(female, &mgr, "Riya"),
        thread(male, &mgr, "Raj"),
        thread(female, &mgr, "Neha"),
        thread(female, &mgr, "Tina"),
        thread(male, &mgr, "Sahil"),
        thread(female, &mgr, "Kriti")
    };

    for (auto& t : threads) t.join();
}





/* ADDED
Load balancing → Choose the least occupied compatible bathroom.
Global queue (fairness) → Threads wait in FIFO order (no busy waiting).
Metrics → Track average waiting time, utilization, and user count.
*/


#include <bits/stdc++.h>
using namespace std;

class UnisexBathroom {
private:
    int counter = 0;  // +ve = males, -ve = females
    string turn = "none";
    int waitingMales = 0, waitingFemales = 0;
    int totalEntries = 0;
    chrono::milliseconds totalOccupiedTime{ 0 };

    mutex mtx;
    condition_variable cv;

public:
    // ---------------- Core Usage Logic ----------------
    void useBathroom(const string& gender, const string& name) {
        auto startWait = chrono::steady_clock::now();
        unique_lock<mutex> lock(mtx);

        if (gender == "male") waitingMales++;
        else waitingFemales++;

        cv.wait(lock, [&] {
            if (gender == "male")
                return ((counter >= 0 && counter < 3) &&
                    (turn == "male" || turn == "none"));
            else
                return ((counter <= 0 && counter > -3) &&
                    (turn == "female" || turn == "none"));
            });

        // Record waiting time
        auto endWait = chrono::steady_clock::now();
        totalEntries++;
        totalOccupiedTime += chrono::duration_cast<chrono::milliseconds>(endWait - startWait);

        // Enter bathroom
        if (gender == "male") {
            waitingMales--;
            if (turn == "none") turn = "male";
            counter++;
            cout << name << " entered (M) | males: " << counter << endl;
        }
        else {
            waitingFemales--;
            if (turn == "none") turn = "female";
            counter--;
            cout << name << " entered (F) | females: " << -counter << endl;
        }

        lock.unlock();

        // simulate using bathroom
        this_thread::sleep_for(chrono::milliseconds(200));

        lock.lock();
        if (gender == "male") {
            counter--;
            cout << name << " leaving (M)" << endl;
        }
        else {
            counter++;
            cout << name << " leaving (F)" << endl;
        }

        if (counter == 0) {
            if (waitingMales > 0)
                turn = "male";
            else if (waitingFemales > 0)
                turn = "female";
            else
                turn = "none";
        }
        cv.notify_all();
    }

    // ---------------- Support Methods ----------------
    bool canEnter(const string& gender) {
        lock_guard<mutex> lock(mtx);
        if (gender == "male")
            return (counter >= 0 && counter < 3);
        else
            return (counter <= 0 && counter > -3);
    }

    int getOccupancy() {
        lock_guard<mutex> lock(mtx);
        return abs(counter);
    }

    pair<int, chrono::milliseconds> getMetrics() {
        lock_guard<mutex> lock(mtx);
        return { totalEntries, totalOccupiedTime };
    }
};

// ------------------------------------------------------------------------

class BathroomManager {
private:
    vector<shared_ptr<UnisexBathroom>> bathrooms;
    queue<pair<string, string>> waitingQueue;
    mutex queueMtx;
    condition_variable queueCV;

    atomic<int> totalUsers{ 0 };
    atomic<long long> totalWaitTime{ 0 };

public:
    BathroomManager(int n) {
        for (int i = 0; i < n; ++i)
            bathrooms.push_back(make_shared<UnisexBathroom>());
    }

    // Smart bathroom selection (load balancing)
    shared_ptr<UnisexBathroom> findBestBathroom(const string& gender) {
        shared_ptr<UnisexBathroom> best = nullptr;
        int minOcc = INT_MAX;
        for (auto& bath : bathrooms) {
            if (bath->canEnter(gender)) {
                int occ = bath->getOccupancy();
                if (occ < minOcc) {
                    minOcc = occ;
                    best = bath;
                }
            }
        }
        return best;
    }

    void useBathroom(const string& gender, const string& name) {
        auto startWait = chrono::steady_clock::now();

        // enqueue globally (FIFO fairness)
        {
            unique_lock<mutex> qlock(queueMtx);
            waitingQueue.push({ gender, name });
            queueCV.wait(qlock, [&] { return waitingQueue.front() == make_pair(gender, name); });
        }

        while (true) {
            auto bath = findBestBathroom(gender);
            if (bath) {
                // dequeue since user got a bathroom
                {
                    lock_guard<mutex> qlock(queueMtx);
                    waitingQueue.pop();
                    queueCV.notify_all();  // wake next in line
                }

                auto endWait = chrono::steady_clock::now();
                totalUsers++;
                totalWaitTime += chrono::duration_cast<chrono::milliseconds>(endWait - startWait).count();

                bath->useBathroom(gender, name);
                return;
            }
            this_thread::sleep_for(chrono::milliseconds(50)); // small retry
        }
    }

    // --------------- Metrics ---------------
    void printMetrics() {
        cout << "\n===== Global Metrics =====" << endl;
        cout << "Total users served: " << totalUsers << endl;
        if (totalUsers > 0)
            cout << "Average wait time: " << (totalWaitTime / totalUsers) << " ms" << endl;

        for (int i = 0; i < bathrooms.size(); ++i) {
            auto [entries, time] = bathrooms[i]->getMetrics();
            cout << "Bathroom " << i + 1 << " served " << entries
                << " users | avg local wait: "
                << (entries ? time.count() / entries : 0)
                << " ms" << endl;
        }
        cout << "==========================\n";
    }
};

// ------------------------------------------------------------------------

void male(BathroomManager* mgr, string name) { mgr->useBathroom("male", name); }
void female(BathroomManager* mgr, string name) { mgr->useBathroom("female", name); }

int main() {
    BathroomManager mgr(2); // 2 bathrooms

    vector<thread> threads = {
        thread(male, &mgr, "Aman"),
        thread(female, &mgr, "Riya"),
        thread(male, &mgr, "Raj"),
        thread(female, &mgr, "Neha"),
        thread(female, &mgr, "Tina"),
        thread(male, &mgr, "Sahil"),
        thread(female, &mgr, "Kriti"),
        thread(male, &mgr, "Mark"),
        thread(female, &mgr, "Pooja")
    };

    for (auto& t : threads) t.join();

    mgr.printMetrics();
}
