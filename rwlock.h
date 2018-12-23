#include "spinlock.h"
struct rwlock {
    struct spinlock slock;
    uint lock;
    uint reader_num;
};
