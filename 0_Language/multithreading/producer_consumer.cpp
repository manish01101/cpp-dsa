#include<iostream>
#include<mutex>
#include<thread>

using namespace std;

mutex mtx;
condition_variable cv; // this will notify the consumer about new item produced
queue<int> messageQueue;
bool done = false; //shared flag to signal producer finished


void pushToMessageQueue(int msg) {
	unique_lock<mutex> lock(mtx);
	messageQueue.push(msg);
	cout << "[Producer] Produced message: " << msg << endl;
	cv.notify_one(); // wake one waiting consumer
}

void consumeFromMessageQueue() {
	while (true) {
		unique_lock<mutex> lock(mtx);
		// cv.wait() releases the lock and sleeps until predicate is true
		/* cv.wait() will make consumer thread to sleep and also release the lock, not blocking the producer from pushing message*/

		/*
		What happens when cv.wait() is called:

		cv.wait releases the lock and BLOCKS on *this (source)
		After being woken up (through cv.notify_one() or cv.notify_all() on another thread, cv.wait() checks the condition of second argument (a lambda function returning true or false).
		If the predicate returns true, the waiting ends, and the thread proceeds with the next steps. Mutex is LOCKED again.
		If the predicate returns false, the thread goes back to waiting and blocks. Mutex is UNLOCKED.


		Why is the mutex needed, isn't the condition variable enough?

		No, you need them in conjunction. Imagine a scenario where you have multiple consumers to the same producer. A condition variable is used to make sure that we only consume from the queue when it is non-empty. However, without a mutex, after condition variable unblocks, since you’re not using a mutex, the rest of the code doesn’t guarantee that the queue is not empty. You can have a Race Condition again.


		Notify One vs. Notify All

		notify_one() wakes up only one of the waiting threads and unblock them (more efficient in scenarios where waking up a single thread is sufficient because it avoids unnecessarily waking up multiple threads)
		notify_all() wakes up all threads waiting on the condition variable. This is necessary in situations where multiple threads may be waiting for the same condition and all need to recheck the condition when it changes.

		*/
		cv.wait(lock, [] { return done || !messageQueue.empty(); });
		if (done && messageQueue.empty()) break;


		int msg = messageQueue.front();
		messageQueue.pop();
		lock.unlock(); // release lock before processing (important!)

		cout << "   [Consumer] Consumed message: " << msg << endl;

		// simulate processing delay
		this_thread::sleep_for(chrono::milliseconds(150));
	}
}

int main() {
	thread producer([] {
		for (int i = 1; i <= 10; ++i) {
			pushToMessageQueue(i);
			this_thread::sleep_for(chrono::milliseconds(100)); // simulate production delay
		}
		{
			unique_lock<mutex> lock(mtx);
			done = true;
		}
		cv.notify_all(); // wake up any waiting consumers
		cout << "Producer finished." << endl;
		}
	);

	thread consumer(consumeFromMessageQueue);

	producer.join();
	consumer.join();

	this_thread::sleep_for(chrono::seconds(2));

	cout << "Main thread exiting..." << endl;
	return 0;
}
