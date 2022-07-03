#include <ios>
#include <iostream>
#include  <thread>
#include <memory>
#include <mutex>

using namespace std;\
std::mutex mtx;
std::mutex coutMtx;

int main() {
    cout << boolalpha << endl; // Sets the boolalpha format flag for the str stream.
    cout << "hardware_concurrency() = " <<
    thread::hardware_concurrency() << endl;

    thread t1([] {  lock_guard<mutex> guard(coutMtx); cout << "t1 with id = " << this_thread::get_id() << endl; });
    thread t2([] {  lock_guard<mutex> guard(coutMtx); cout << "t2 with id = " << this_thread::get_id() << endl; }); 

    cout << endl;

    {   
        lock_guard<mutex> guard(mtx);
        swap(t1, t2); //这里有竞态发生,书籍并没有加锁，测试后，还存在竞态，怀疑是cout的问题，还有一个是同步的问题,没有输出后就直接给 t2 swap了。调度问题,就handware为1
    }

    {
        lock_guard<mutex> guard(coutMtx);
        cout << "FROM MAIN: id of t1 " << t1.get_id() << endl;
        cout << "FROM MAIN: id of t2 " << t2.get_id() << endl;

        cout << endl;

        cout << "FROM MAIN: id of main = " << this_thread::get_id() << endl;

        cout << endl;

        cout << "t1.joinable(): " << t1.joinable() << endl;

        cout << endl;
    }

    t1.join();
    t2.join();

    {
        lock_guard<mutex> guard(coutMtx);
        cout << endl;

        cout << "t1.joinable(): " << t1.joinable() << endl;

        cout << endl;
    }

}