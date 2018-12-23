#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "rwlock.h"

struct rwlock global_lock;


void initrwlock()
{
    initlock(&(global_lock.slock), "rwlock");
    global_lock.lock = 0;
    global_lock.reader_num = 0;
}


void acquire_read()
{
    acquire(&(global_lock.slock));
    pushcli();   
    global_lock.reader_num++;
    if(global_lock.reader_num == 1)
    {
        global_lock.lock = 1;
    }
    release(&(global_lock.slock));
}


void acquire_write()
{
    while(xchg(&(global_lock.lock), 1) != 0);
    pushcli();
}


void release_read()
{
    acquire(&(global_lock.slock));
    global_lock.reader_num--;
    if(global_lock.reader_num == 0)
    {
        global_lock.lock = 0;
    }
    release(&(global_lock.slock));
    popcli();
}

void release_write()
{
    global_lock.lock = 0;
    popcli();
}
