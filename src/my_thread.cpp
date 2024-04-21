#include "my_thread.h"
#include <cstdint>
#include <iostream>
#include <thread>
void test1(int i) {
    std::cout << i;
    return;
}

auto main() -> std::int32_t {
    my_thread::thread s(test1, 1);
    _sleep(1000);
    return 0;
}
