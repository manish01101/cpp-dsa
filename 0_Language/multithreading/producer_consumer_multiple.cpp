#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <vector>

using namespace std;

mutex mtx;
condition_variable cv;
queue<int> messageQueue;

bool done = false;
int activeProducers = 0; // counts how many producers are still producing

void pushToMessageQueue(int producerId, int msg) {
	unique_lock<mutex> lock(mtx);
	messageQueue.push(msg);
	cout << "[Producer " << producerId << "] Produced message: " << msg << endl;
	cv.notify_one(); // wake up one waiting consumer
}

void producerTask(int id, int count) {
	{
		lock_guard<mutex> lock(mtx);
		activeProducers++;
	}

	for (int i = 1; i <= count; ++i) {
		pushToMessageQueue(id, id * 100 + i);
		this_thread::sleep_for(chrono::milliseconds(100 + id * 20)); // different speeds
	}

	{
		unique_lock<mutex> lock(mtx);
		activeProducers--;
		if (activeProducers == 0) {
			done = true;
			cv.notify_all(); // wake all consumers to finish
		}
	}

	cout << "[Producer " << id << "] Finished.\n";
}

void consumeFromMessageQueue(int consumerId) {
	while (true) {
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, [] { return done || !messageQueue.empty(); });

		if (done && messageQueue.empty()) {
			break; // no more work to do
		}

		int msg = messageQueue.front();
		messageQueue.pop();
		lock.unlock(); // release before processing

		cout << "   [Consumer " << consumerId << "] Consumed message: " << msg << endl;
		this_thread::sleep_for(chrono::milliseconds(150)); // simulate work
	}

	cout << "   [Consumer " << consumerId << "] Exiting.\n";
}

int main() {
	const int numProducers = 3;
	const int numConsumers = 2;
	const int messagesPerProducer = 5;

	vector<thread> producers;
	vector<thread> consumers;

	// Start consumers first
	for (int i = 0; i < numConsumers; ++i) {
		consumers.emplace_back(consumeFromMessageQueue, i + 1);
	}

	// Start producers
	for (int i = 0; i < numProducers; ++i) {
		producers.emplace_back(producerTask, i + 1, messagesPerProducer);
	}

	// Join all producers
	for (auto& p : producers) p.join();

	// Join all consumers
	for (auto& c : consumers) c.join();

	cout << "\nAll producers and consumers finished. Main exiting.\n";
	return 0;
}
