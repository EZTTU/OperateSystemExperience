//
//
//#include <unistd.h>
//#include "thread.h"
//
//unsigned long balance = 100;
//
//void Alipay_withdraw(int amt) {
//    if (balance >= amt) {
//        usleep(1); // unexpected delays
//        balance -= amt;
//    }
//}
//
//void Talipay(int id) {
//    Alipay_withdraw(100);
//}
//
//int main() {
//    create(Talipay);
//    create(Talipay);
//    join();
//    printf("balance = %lu\n", balance);
//}

#include "thread.h"

#define N 100000000

long sum = 0;

void Tsum(int id) {
    for (int i = 0; i < N; i++) {
        sum++;
    }
}

int main() {
    create(Tsum);
    create(Tsum);
    join();
    printf("sum = %ld\n", sum);
}