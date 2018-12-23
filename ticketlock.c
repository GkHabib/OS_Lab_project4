#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "ticketlock.h"

struct ticketlock global_lock;

void initlock_t()
{
    global_lock.proc = 0;
    global_lock.ticket = 0;
    global_lock.turn = 0;
}


void acquire_t()
{
    uint ticket;
    pushcli(); 
    // if(global_lock.ticket != 0)
    //     panic("acquire");

    ticket = fetch_and_inc(&global_lock.ticket);
    while(global_lock.turn != ticket)
        ticket_sleep(&global_lock);

    global_lock.proc = myproc();
}

void release_t()
{
    // if(global_lock.ticket == 0)
    //     panic("release");

    global_lock.proc = 0;

    fetch_and_inc(&global_lock.turn);
    wakeup(&global_lock);
    popcli();
}
