class FooBar {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    bool isFooPrinted = false;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; ++i) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] { return !isFooPrinted; }); // wait until bar() printed
            printFoo();
            isFooPrinted = true;
            cv.notify_all(); // wake bar()
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; ++i) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] { return isFooPrinted; }); // wait until foo() printed
            printBar();
            isFooPrinted = false;
            cv.notify_all(); // wake foo()
        }
    }
};
