#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit(0);
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait(null);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//return the memory size of the current process
int
sys_memsize(void)
{
  return myproc()->sz;
}

//@TODO: check what value to send
int
sys_policy(void)
{
  int poly;

  if(argint(0, &poly) < 0)
    return -1;
  return policy(poly);
}

int
sys_set_ps_priority(void)
{
  int prio;

  if(argint(0, &prio) < 0)
    return -1;
  return set_ps_priority(prio);
}


int
sys_proc_info(void)
{
  struct perf* perf;

  if(argptr(0, ((void*)&perf),sizeof(*perf)) < 0)
      return -1;
  return proc_info(perf);
  //@TODO: how to put information into perf struct?

}

int
sys_set_cfs_priority(void)
{
  int prio;

  if(argint(0, &prio) < 0)
    return -1;
  return set_cfs_priority(prio);
}
