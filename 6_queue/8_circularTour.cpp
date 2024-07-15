#include<iostream>
#include<queue>
using namespace std;

struct petrolPump {
    int petrol;
    int distance;
};

int tour(petrolPump data[], int n) {
    int deficit = 0;
    int balance = 0;
    int start = 0;

    for (int i = 0; i < n; i++) {
        balance += data[i].petrol - data[i].distance;
        if (balance < 0) {
            //storing deficit value so that dont traverse twice
            deficit += balance;
            start = i + 1;
            //reassigning balance as zero
            balance = 0;
        }
    }
    //for preprocessed petrol pump data
    if (deficit + balance >= 0) return start;
    else return -1;
}

int main() {
    struct petrolPump data[4];
    for (int i = 0; i < 4; i++) {
        cin >> data[i].petrol >> data[i].distance;
    }

    // cout << "printing data: " << endl;
    // for(int i = 0; i<4; i++){
    //     cout << data[i].petrol << data[i].distance;
    // }
    cout << tour(data, 4) << endl;


}