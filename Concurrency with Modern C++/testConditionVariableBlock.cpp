#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;

// bool dataReady{false}; 去掉谓语，存在未唤醒和伪唤醒的情况
// 未唤醒
// 该现象是发送方在接收方到达其等待状态之前发送通知，结果是通知丢失了。
// C++标准将条件变量描述为同步机制：“条件变量类是同步原语，可用于阻塞一个线程，或同时阻塞多个线 程……”所以通知丢失了，接收者就会持续等待
// 伪唤醒
// 还有一种情况，就会没有发通知，但接收方会被唤醒。使用POSIX Threads和 Windows API
// 时，都会出现这样的现象。伪唤醒的真相，很可能是本来就没有处于休眠状态。
// 这意味着，在被唤醒的线程有机会运行之前，另一个线程早就等候多时了。
void doTheWork() {
    std::cout << "Processing shared data. " << std::endl;
}

void waitingForWork() {
    std::cout << "Worker: Waiting for work. " << std::endl;
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck); 
    doTheWork();
    std::cout << "Work done " << std::endl;
}

void setDataReady() {
    std::cout << "Sender: Data is ready.\n";
    cv.notify_one();
}

int main()
{
    std::cout << "\n";

    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();
}