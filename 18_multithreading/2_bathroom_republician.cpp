#include<bits/stdc++.h>
using namespace std;
/*
a bathroom is begin designed for the use of both males and females in an office but requires the following constraints to be maintained:
    -> there cannot be men and women in the bathroom at the same time.
    -> there should never be more than three employees in the bathroom simultaneously.

the solution should avoid deadlocks. (not worry about starvation)
Starvation happens when a male keeps waiting outside the bathroom while consecutive female users continue to enter as soon as it becomes vacant, preventing the male from ever getting access.
*/

class UnisexBathroom {
    // for male=>1 to 3, female=> -1 to -3
private:
    int counter;
    mutex mtx;
    condition_variable cv;

public:
    UnisexBathroom() : counter(0) { }
    void maleUseBathroom(string name) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&] {return (counter >= 0 && counter <= 2);});
        counter++;
        cout << counter << " male entered" << endl;
        lock.unlock();
        cout << "male used the bathroom" << endl;

        lock.lock();
        counter--;
        lock.unlock();

        cv.notify_all();
    }
    void femaleUseBathroom(string name) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&] {return (counter <= 0 && counter >= -2);});
        counter--;
        cout << counter << " female entered" << endl;
        lock.unlock();

        cout << "female used the bathroom" << endl;

        lock.lock();
        counter++;
        lock.unlock();

        cv.notify_all();
    }
};

void maleUseBathroom(UnisexBathroom* bathroom, string name) {
    bathroom->maleUseBathroom(name);
}
void femaleUseBathroom(UnisexBathroom* bathroom, string name) {
    bathroom->femaleUseBathroom(name);
}

int main() {
    UnisexBathroom* bathroom = new UnisexBathroom();
    thread t1(maleUseBathroom, bathroom, "Sahil");
    thread t5(femaleUseBathroom, bathroom, "Riya");
    thread t2(maleUseBathroom, bathroom, "Satya");
    thread t3(maleUseBathroom, bathroom, "Mark");
    thread t6(femaleUseBathroom, bathroom, "Rani");
    thread t4(maleUseBathroom, bathroom, "Sundar");

    t1.join(), t2.join(), t3.join(), t4.join(), t5.join(), t6.join();

}




/* -------- STARVATION FREE IMPLEMENTATION ------------*/
#include <bits/stdc++.h>
using namespace std;

class UnisexBathroom {
private:
    int counter;  // +ve for males, -ve for females
    mutex mtx;
    condition_variable cv;

    int waitingMales = 0, waitingFemales = 0;
    string turn = "none"; // "male" or "female"

public:
    UnisexBathroom() : counter(0) { }

    void maleUseBathroom(string name) {
        unique_lock<mutex> lock(mtx);
        waitingMales++;

        cv.wait(lock, [&] {
            // allow if: either no one inside OR only males inside
            // and either it's males’ turn or no turn assigned
            return ((counter >= 0 && counter < 3) &&
                (turn == "male" || turn == "none"));
            });

        waitingMales--;
        if (turn == "none") turn = "male"; // claim the turn
        counter++;
        cout << name << " entered (M) | current males: " << counter << endl;

        lock.unlock();

        // simulate usage
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << name << " leaving (M)" << endl;

        lock.lock();
        counter--;

        // if last male leaving
        if (counter == 0) {
            // if females are waiting, switch turn
            if (waitingFemales > 0)
                turn = "female";
            else if (waitingMales == 0)
                turn = "none"; // nobody waiting
            cv.notify_all();

            /* the above avoids the pathological “forced alternation” problem, which would occur if you always flipped the turn blindly:
            turn = (turn == "male") ? "female" : "male";
            */
        }
        else {
            cv.notify_all();
        }
    }

    void femaleUseBathroom(string name) {
        unique_lock<mutex> lock(mtx);
        waitingFemales++;

        cv.wait(lock, [&] {
            return ((counter <= 0 && counter > -3) &&
                (turn == "female" || turn == "none"));
            });

        waitingFemales--;
        if (turn == "none") turn = "female";
        counter--;
        cout << name << " entered (F) | current females: " << -counter << endl;

        lock.unlock();

        // simulate usage
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << name << " leaving (F)" << endl;

        lock.lock();
        counter++;

        // if last female leaving
        if (counter == 0) {
            if (waitingMales > 0)
                turn = "male";
            else if (waitingFemales == 0)
                turn = "none";
            cv.notify_all();
        }
        else {
            cv.notify_all();
        }
    }
};

// helper wrappers
void male(UnisexBathroom* b, string name) { b->maleUseBathroom(name); }
void female(UnisexBathroom* b, string name) { b->femaleUseBathroom(name); }

int main() {
    UnisexBathroom bathroom;

    vector<thread> threads;
    threads.emplace_back(male, &bathroom, "Aman");
    threads.emplace_back(female, &bathroom, "Riya");
    threads.emplace_back(female, &bathroom, "Neha");
    threads.emplace_back(male, &bathroom, "Raj");
    threads.emplace_back(male, &bathroom, "Sahil");
    threads.emplace_back(female, &bathroom, "Tina");

    for (auto& t : threads) t.join();
}
