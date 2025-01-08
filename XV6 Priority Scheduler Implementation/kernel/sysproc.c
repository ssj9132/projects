#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "process.h"
#include "pstat.h"

extern struct process_control_block process_table[NPROC];

uint64 sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0; // not reached
}

uint64 sys_getpid(void)
{
  return myproc()->pid;
}

uint64 sys_fork(void)
{
  return fork();
}

uint64 sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64 sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64 sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (killed(myproc()))
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64 sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64 sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64 sys_setpriority(void)
{
  int pid;
  int priority;
  
  argint(0, &pid);
  argint(1, &priority);
  

  struct process_control_block *p;
  for(p = process_table; p < &process_table[NPROC]; p++ )
  {
    acquire(&p->lock);
    
    if((p->pid == pid) && (priority<=20 && priority>=-20))
    {
      p->real_priority = priority;
      release(&p->lock);
      
      return 0;
    }

    release(&p->lock);
  }
  return -1;

  
}

uint64 sys_seteffpriority(void)
{
  int pid;
  int priority;
  
  argint(0, &pid);
  argint(1, &priority);

  struct process_control_block *p;
  for(p = process_table; p < &process_table[NPROC]; p++ )
  {
    acquire(&p->lock);

    if((p->pid == pid) && (priority<=20 && priority>=-20))
    {
      p->effective_priority = priority;
      release(&p->lock);
      
      return 0;
    }

    release(&p->lock);
  }
    return -1;

  
}


uint64 sys_getpinfo(void)
{
    struct pstat p;
    uint64 dst;

    argaddr(0, &dst);

    for(int i = 0; i < NPROC; i++) 
    {
        acquire(&process_table[i].lock);
        
         strncpy(p.name[i], process_table[i].name, 16);
         p.pid[i] = process_table[i].pid;
         p.effective_priority[i] = process_table[i].effective_priority; //not really used as no scheduling part of it
         p.real_priority[i] = process_table[i].real_priority;
         p.state[i] = process_table[i].state;
         if(process_table[i].state == UNUSED) 
         {
            p.inuse[i] = 0;
         }  

        release(&process_table[i].lock);
    }
    
    if (either_copyout(1, dst, (void *)&p, sizeof(p)) < 0)
    {
      return -1;
    }    
    
    return 0;
}


