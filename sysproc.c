#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
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
  return proc->pid;
}

addr_t
sys_sbrk(void)
{
  addr_t addr;
  addr_t n;

  argaddr(0, &n);
  addr = proc->sz;
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
    if(proc->killed){
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

#define MMAP_FAILED ((~0lu))
  addr_t
sys_mmap(void)
{
  int fd, flags;
  if(argint(0,&fd) < 0 || argint(1,&flags) < 0)
    return MMAP_FAILED;

  // TODO: your implementation
  //eager flag called
  if(flags == 0)
  {
    //get file struct
    struct file *f = proc->ofile[fd];
    //hold the string
    char hold_c;

    int hold = fileread(f, &hold_c , sizeof(f->readable)); 
    //CHECK
    cprintf("Eager was called and we got %c !", f->readable);

    return MMAP_FAILED;
  }
  //Lazy flag called
  else if(flags == 1)
  {
    //cprintf("sys_map is here to pirnt BOI %d lazy was called", fd);
    return MMAP_FAILED;
  }
  else
    return MMAP_FAILED;

  //return MMAP_FAILED;
}

  int
handle_pagefault(addr_t va)
{
  // TODO: your code here
  //int handled = mappages(proc->pgdir, &va, proc->sz, (addr_t)proc->mmaptop, );
  return 0;
}
