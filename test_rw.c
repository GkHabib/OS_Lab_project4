#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

#define NUMOFCHILDS 9

int main(int argc, char const *argv[])
{
    int pid;

    rwinit();
    
    pid = fork();
    for (int i=0; i<NUMOFCHILDS; i++)
    {
        if(pid > 0) pid =  fork();
    }
    if (pid < 0)
    {
        write(2, "fork error!\n", 12);
    }
    else if (pid == 0)
    {
        write(1, "child adding to shared number...\n", 33);
        rwtest(5);
        // printf(1, "child adding to shared number\n");
    }
    else 
    {
        for (int i=0; i<NUMOFCHILDS; i++)
        {
            wait();
        }
        write(1, "program finished!\n", 18);
        // printf(1, "program finished\n");
    }
    return 0;
}
