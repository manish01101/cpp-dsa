#include<iostream>
#include<thread>
#include<mutex>
#include<shared_mutex>
#include<map>

using namespace std;
mutex mtx;  //mutex doesn’t support shared locking — only exclusive locks.
shared_mutex smtx;
/*
lock makes the program synchronous
granularity of locking: size of data item that is protected by lock
lock_guard vs unique_lock
| Feature                                    | `lock_guard`     | `unique_lock`                      |
| ------------------------------------------ | ---------------- | ---------------------------------- |
| Lock type                                  | Exclusive only   | Exclusive only (but more flexible) |
| Unlock manually                            | No               | Yes (`lock.unlock()`)              |
| Relock                                     | No               | Yes (`lock.lock()`)                |
| Moveable (transfer ownership)              | No               | Yes                                |
| Works with `shared_mutex` for shared_lock? | No               | (via `std::shared_lock`)           |
| Performance                                | Slightly lighter | Slightly heavier (more flexible)   |

*/
void hello() {
	lock_guard<mutex> lock(mtx); // it automatically unlock, if goes out of scope
	cout << "hello manish" << " " << this_thread::get_id() << endl;
	cout << "hi" << endl;
}
void hi() {
	unique_lock<mutex> lock(mtx); // manual unlocking and relocking
	cout << "hi" << endl;
	lock.unlock();
	cout << "hello manish" << endl;
}
// SHARED OR READ WRITE LOCKS
/*
problem is when there is no write and only read calls they still have to wait for each other to complete even though read individually does not do any race condition => this makes them synchronous
*/
map<string, int> dnsCache;
void dnsWrite(int ip, string name) {
	lock_guard<mutex> lock(mtx);
	dnsCache[name] = ip;
}
int dnsRead(string name) {
	lock_guard<mutex> lock(mtx);
	return dnsCache[name];
}
/*
to solve above problem -> use shared_lock on read
so when write, no read available
but when no write req, all can read parallely
*/
void dnsWrite2(int ip, string name) {
	// lock_guard<shared_mutex> lock(smtx); // Simple exclusive lock (fine)
	unique_lock<shared_mutex> lock(smtx); // More flexible exclusive lock
	dnsCache[name] = ip;
}
int dnsRead2(string name) {
	shared_lock<shared_mutex> lock(smtx);
	return dnsCache[name];
}


int main() {
	cout << this_thread::get_id() << endl;

	int n = thread::hardware_concurrency();
	cout << "total thread is: " << n << endl;

	vector<thread> threads;
	for (int i = 0; i < n; ++i) {
		threads.push_back(thread(hello));
	}
	for (int i = 0; i < n; ++i) {
		threads[i].join();
	}

	return 0;
}