#include <unistd.h>
#include "thread.h"

int x = 0;

void multiThreadHello(int id) {
    printf("thread is %d\n", id);
    usleep(id * 100000);
    printf("Hello from thread #%c\n", "123456789ABCDEF"[x++]);
}

int main() {
    for (int i = 0; i < 10; i++) {
        create(multiThreadHello);
    }
}
