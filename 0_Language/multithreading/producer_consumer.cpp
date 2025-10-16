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
