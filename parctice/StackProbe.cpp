#include "thread.h"

__thread char *base, *cur; // thread-local variables
__thread int id;

// objdump to see how thread-local variables are implemented
__attribute__((noinline)) void set_cur(void *ptr) {
    cur = static_cast<char*>(ptr); // 显式转换为 char*
}

__attribute__((noinline)) char *get_cur() {
    return cur;
}

void stackoverflow(int n) {
    set_cur(&n);
    if (n % 1024 == 0) {
        int sz = base - get_cur();
        printf("Stack size of T%d >= %d KB\n", id, sz / 1024);
    }
    stackoverflow(n + 1);
}

void Tprobe(int tid) {
    id = tid;
    base = static_cast<char*>(static_cast<void*>(&tid)); // 显式转换为 char*
    stackoverflow(0);
}

int main() {
    setbuf(stdout, NULL);
    for (int i = 0; i < 4; i++) {
        create(Tprobe);
    }
}
