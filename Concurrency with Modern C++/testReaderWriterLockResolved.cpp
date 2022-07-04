#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

std::map<std::string, int> teleBook { {"Dijkstra", 1972},
    {"Scott", 1976}, {"Ritchie", 1983} };

std::shared_timed_mutex teleBookMutex;

void addToTeleBook(const std::string& na, int tele) {
    std::lock_guard<std::shared_timed_mutex> writerLock(teleBookMutex);
    std::cout << "\nSTART UPDATE " << na;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    teleBook[na] = tele;
    std::cout << " ... ENDING UPDATE " << na << std::endl;
}

void printNumber(const std::string& na) {
    std::shared_lock<std::shared_timed_mutex> readerLock(teleBookMutex);

    auto searchEntry = teleBook.find(na);

    if ( searchEntry != teleBook.end() ) {
        std::cout << searchEntry->first << ": " << searchEntry->second << std::endl;
    }
    else {
        std::cout << na << "not found!" << std::endl;
    }
}

int main() {
    std::cout << std::endl;

    std::thread read1([] { printNumber("Scott"); });
    std::thread read2([] {printNumber("Ritchie"); });
    std::thread w1([] { addToTeleBook("Ritchie", 1968); });
    std::thread read3([] {printNumber("Dijkstra"); });
    std::thread read4([] {printNumber("Scott"); });
    std::thread w2([] { addToTeleBook("Bjarne", 1965); });
    std::thread read5([] {printNumber("Scott"); });
    std::thread read6([] {printNumber("Ritchie"); });
    std::thread read7([] {printNumber("Scott"); });
    std::thread read8([] {printNumber("Bjarne"); }); // Bjarne: 0有竞态,如果没有找到就会在读访问中创建一对("Bjarne", 0);
    read1.join();
    read2.join();
    read3.join();
    read4.join();
    read5.join();
    read6.join();
    read7.join();
    read8.join();
    w1.join();
    w2.join();

    std::cout << std::endl;

    std::cout << "\nThe new telephone book" << std::endl;
    for (auto teleIt : teleBook )
    {
        std::cout << teleIt.first << ": " << teleIt.second << std::endl;
    }

    std::cout << std::endl;
}