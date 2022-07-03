#include <atomic>
#include <memory>
#include <thread>
#include <memory.h>
#include <iostream>

int main()
{
    std::shared_ptr<int> ptr = std::make_shared<int>(2011);

    // for (auto i = 0; i < 10; i++) {
    //     std::thread([ptr]{
    //         std::shared_ptr<int> localPtr(ptr);
    //         localPtr =  std::make_shared<int>(2014);
    //     }).detach();
    // }

    // for (auto i = 0; i < 10; i++) {
    //     std::thread([&ptr]{//会有数据竞争，未定义的行为
    //         std::shared_ptr<int> localPtr(ptr);
    //         localPtr =  std::make_shared<int>(2014);
    //     }).detach();
    // }
    
    for (auto i = 0; i < 10; i++) {
        std::thread([&ptr]{
            std::shared_ptr<int> localPtr(ptr);
            std::atomic_store(&ptr, localPtr); //解决数据竞争
        }).detach();
    }
    
    return 0;
}