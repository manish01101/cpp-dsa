#include<iostream>
#include<thread>
#include<semaphore>

using namespace std;

void printNum(int n) {
	cout << n << " ";
}

class ZeroEvenOddSemaphore {
private:
	int n;
	counting_semaphore<1> zeroSem{ 1 };
	counting_semaphore<1> oddSem{ 0 };
	counting_semaphore<1> evenSem{ 0 };
public:
	ZeroEvenOddSemaphore(int n) {
		this->n = n;
	}

	// printNumber(x) outputs "x", where x is an integer.
	void zero(function<void(int)> printNumber) {
		for (int i = 1; i <= n; ++i) {
			zeroSem.acquire();
			printNumber(0);
			if (i % 2 == 1) oddSem.release();
			else evenSem.release();
		}
	}

	void even(function<void(int)> printNumber) {
		for (int i = 2; i <= n; i += 2) {
			evenSem.acquire();
			printNumber(i);
			zeroSem.release();
		}
	}

	void odd(function<void(int)> printNumber) {
		for (int i = 1; i <= n; i += 2) {
			oddSem.acquire();
			printNumber(i);
			zeroSem.release();
		}
	}
};
class ZeroEvenOdd {
private:
	int n;
	mutex mtx;
	condition_variable cv;
	string turn = "zero";

public:
	ZeroEvenOdd(int n) {
		this->n = n;
	}

	// printNumber(x) outputs "x", where x is an integer.
	void zero(function<void(int)> printNumber) {
		for (int i = 1; i <= n; ++i) {
			unique_lock<mutex> lock(mtx);
			cv.wait(lock, [&] {return turn == "zero";});
			printNum(0);
			if (i % 2 == 1) turn = "odd";
			else turn = "even";
			cv.notify_all();
			lock.unlock();
		}
	}

	void even(function<void(int)> printNumber) {
		for (int i = 2; i <= n; i += 2) {
			unique_lock<mutex> lock(mtx);
			cv.wait(lock, [&] {return turn == "even";});
			printNum(i);
			turn = "zero";
			cv.notify_all();
			lock.unlock();
		}
	}

	void odd(function<void(int)> printNumber) {
		for (int i = 1; i <= n; i += 2) {
			unique_lock<mutex> lock(mtx);
			cv.wait(lock, [&] {return turn == "odd";});
			printNum(i);
			turn = "zero";
			cv.notify_all();
			lock.unlock();
		}
	}
};

int main() {
	int n = 5;
	ZeroEvenOdd obj(n);

	// creating threads
	thread t1(&ZeroEvenOdd::zero, &obj, printNum);
	thread t2(&ZeroEvenOdd::even, &obj, printNum);
	thread t3(&ZeroEvenOdd::odd, &obj, printNum);

	// wait for all to finish
	t1.join();
	t2.join();
	t3.join();

	cout << endl;
	return 0;
}