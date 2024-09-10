#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

#include <Networking/Socket.h>

using namespace std;

void print_time();

int main() {
    print_time();
    return 0;
}

void print_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&currentTime);

    std::cout << std::put_time(localTime, "%Y년 %m월 %d일 %H시 %M분 %S초") << std::endl;
}