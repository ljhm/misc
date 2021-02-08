// file:///Users/ljh/Downloads/cppreference.com/html_book/reference/en/cpp/thread/condition_variable.html

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;
using namespace std::chrono_literals;

mutex mut;
condition_variable cv;
bool notify1 = false;
bool notify2 = false;
vector<string> vec = {"hello"};
#define coutln cout << __func__ << ":" << __LINE__ << " "

void f1() {
    while (1) {

        {
            unique_lock<mutex> lk(mut);
            cv.wait(lk, []{return notify2;});
        }

        //modify vector
        vec[0] = "hello 111";
        coutln << vec[0] << endl;
        this_thread::sleep_for(1s);

        notify1 = true;
        cv.notify_one();
    }
}

void f2() {
    while (1) {
        notify2 = true;
        cv.notify_one();

        {
            unique_lock<mutex> lk(mut);
            cv.wait(lk, []{return notify1;});
        }

        //modify vector
        vec[0] = "hello 222";
        coutln << vec[0] << endl;
        this_thread::sleep_for(1s);
    }
}

int main() {
    coutln << vec[0] << endl;
    thread t1(f1), t2(f2);
    t1.join();
    t2.join();
}
