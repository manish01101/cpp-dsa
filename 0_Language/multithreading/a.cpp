
#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

void findEven(ull start, ull end) {
  for (ull i = start; i <= end; i++) {
    if (!(i & 1)) {
      evenSum += i;
    }
  }
}
void findOdd(ull start, ull end) {
  for (ull i = start; i <= end; i++) {
    if ((i & 1)) {
      oddSum += i;
    }
  }
}

int main() {
  ull start = 0, end = 1900000000;

  auto startTime = high_resolution_clock::now();

  // thread t(function ptr, ---, ---)
  std::thread t1(findEven, start, 950000000);
  std::thread t3(findEven, 950000000, end);
  std::thread t2(findOdd, start, 950000000);
  std::thread t4(findOdd, 950000000, end);

  // sub thread t1, t2 will have to join with main thread
  t1.join(); t2.join();
  t3.join(); t4.join();

  // without threading
  // findEven(start, end);
  // findOdd(start, end);

  auto endTime = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(endTime - startTime);

  cout << "evensum: " << evenSum << endl;
  cout << "oddsum: " << oddSum << endl;

  cout << duration.count() << "in ms" << endl;
  cout << duration.count() / 1000.0 << "in s" << endl;

  return 0;
}

// g++ -std=c++11 a.cpp
// g++ -std=c++11 -pthread a.cpp