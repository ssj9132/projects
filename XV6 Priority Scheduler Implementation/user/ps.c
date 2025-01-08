#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/process.h"
#include "kernel/pstat.h"
#include "kernel/riscv.h"
#include "user.h"

int main(int argc, char *argv[])
{
    struct pstat p;

    if (getpinfo(&p) < 0)
    {
        return -1;
    }

    printf("NAME\t\tPID\tSTATE\t\tPRIORITY\n");

    for (int i = 0; i < NPROC; i++)
    {
        if (p.inuse[i])
        {
            char *state;

            if (p.state[i] == UNUSED)
            {
                state="UNUSED\t";
            }

            else if (p.state[i] == SLEEPING)
            {
                state="SLEEPING";
            }

            else if (p.state[i] == RUNNABLE)
            {
                 state="RUNNABLE";
            }

            else if (p.state[i] == RUNNING)
            {
                state="RUNNING\t";
            }

            else if (p.state[i] == ZOMBIE)
            {
                state= "ZOMBIE\t";
            }

            else if (p.state[i] == USED )
            {
                state= "USED\t" ; 
            }

            else
            {
                state = "UNKNOWN\t";
            }

            printf("%s\t\t%d\t%s\t%d\t\n", p.name[i], p.pid[i], state, p.real_priority[i]);
        }
    }
    return 0;
}