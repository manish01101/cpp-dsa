/*
Problem Statement: You are expected to implement a data structure which will give random numbers between 1 to N and you are not supposed to repeat a number in a window until all numbers b/w 1- n are exhausted in that window. 
Ex: N =3 possible outcomes: 1, 3,2,| 3,1,2 ... 
I provided a solution with two hashset with TC O(1) ans space O(n), but the interviewer was interested in a solution using Arrays, after thorough discussion I was able to solve it using array and creating sections in array by push_back and pop_back, builtin methods

*/
#include <iostream>
#include <vector>
#include <random>

class RandomGenerator {
private:
    std::vector<int> arr;
    int n;
    int curr;
    std::mt19937 rng{std::random_device{}()};

public:
    RandomGenerator(int n) : n(n), curr(0) {
        arr.reserve(n);
        for (int i = 1; i <= n; ++i)
            arr.push_back(i);
    }

    int next() {
        if (curr == n) curr = 0; // reset window

        std::uniform_int_distribution<int> dist(curr, n - 1);
        int randIndex = dist(rng);
        std::swap(arr[curr], arr[randIndex]);

        return arr[curr++]; // increment current boundary
    }
};

int main() {
    RandomGenerator rg(3);
    for (int i = 0; i < 10; ++i)
        std::cout << rg.next() << " ";
}
