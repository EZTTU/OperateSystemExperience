#include <iostream>

#include "parctice/thread.h"

void threadTask(int id, char symbol) {
    while (true) {
        std::cout << symbol;
    }
}

int main() {
    create([](int id) { threadTask(id, 'a'); });
    create([](int id) { threadTask(id, 'b'); });
    create([](int id) { threadTask(id, 'c'); });
    create([](int id) { threadTask(id, 'd'); });

    return 0;
}

// wget -Uri https://jyywiki.cn/pages/OS/2022/demos/thread.h -Outfile thread.h
