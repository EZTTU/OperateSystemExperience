#include <c++/cstdlib>
#include <c++/cstdio>
#include <c++/cassert>
#include <pthread.h>

#define N_THREAD 64

// 线程状态的枚举
enum ThreadStatus {
    T_FREE = 0,
    T_LIVE,
    T_DEAD,
};

// 线程结构体定义
struct Thread {
    int id;                    // 线程 ID
    ThreadStatus status;       // 线程状态
    pthread_t thread;          // 线程标识
    void (*entry)(int);        // 线程执行函数，接收一个 int 参数
};

// 线程池和指向当前线程的指针
static struct Thread threadPool[N_THREAD];
static struct Thread* threadPtr = threadPool;

// 线程包装函数
void* threadWrapper(void* arg) {
    struct Thread* t = (struct Thread*)arg;  // 强制类型转换
    if (t != nullptr && t->entry != nullptr) {
        t->entry(t->id);  // 调用线程的执行函数
    }
    return nullptr;
}

// 创建新线程并将其加入线程池
void create(void (*fn)(int)) {
    // 检查线程池是否已满
    assert(threadPtr - threadPool < N_THREAD);

    // 初始化线程结构体
    threadPtr->id = (int)(threadPtr - threadPool + 1);  // 设置线程 ID
    threadPtr->status = T_LIVE;                         // 设置状态为活跃
    threadPtr->entry = fn;                              // 设置执行函数

    // 创建线程
    int err = pthread_create(&(threadPtr->thread), nullptr, threadWrapper, threadPtr);
    if (err) {
        fprintf(stderr, "Error creating thread: %d\n", err);  // 输出错误信息
        threadPtr->status = T_FREE;  // 设置状态为释放
        return;
    }

    // 移动指针到下一个线程
    threadPtr++;
}

// 等待所有线程结束并清理
void join() {
    for (struct Thread* t = threadPool; t < threadPtr; t++) {
        if (t->status == T_LIVE) {
            pthread_join(t->thread, nullptr);  // 等待线程结束
            t->status = T_DEAD;  // 设置状态为已结束
        }
    }
}

// 清理函数，在程序退出时调用
__attribute__((destructor)) void cleanup() {
    join();  // 调用 join 函数
}
