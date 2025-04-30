#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


#define USD_TO_INR 76.92
#define INR_TO_USD 0.013
#define USD_TO_EUR 0.85
#define EUR_TO_USD 1.18
#define EUR_TO_INR 96.33
#define INR_TO_EUR 0.0104

#define MAX_TASKS 100
#define MAX_TASK_LEN 64

struct task {
    char description[MAX_TASK_LEN];
    int done;  
};

struct task todo_list[MAX_TASKS];
int task_count = 0;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  
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

int sys_currency_convert(void) {
  char from_currency;
  char to_currency;
  int amount;  
  int result = 0;

  if (argint(0, (int*)&from_currency) < 0 ||
      argint(1, (int*)&to_currency) < 0 ||
      argint(2, &amount) < 0) {
      return -1;
  }

  if (from_currency == 'U' && to_currency == 'I') {
      result = amount * USD_TO_INR;
  } else if (from_currency == 'I' && to_currency == 'U') {
      result = amount * INR_TO_USD;
  } else if (from_currency == 'U' && to_currency == 'E') {
      result = amount * USD_TO_EUR;
  } else if (from_currency == 'E' && to_currency == 'U') {
      result = amount * EUR_TO_USD;
  } else if (from_currency == 'E' && to_currency == 'I') {
    result = amount * EUR_TO_INR;
  } else if (from_currency == 'I' && to_currency == 'E') {
    result = amount * INR_TO_EUR;
  }
  else {
      return -1; 
  }

  return result;
}

int sys_todo_add(void) {
  char *desc;
  if (argstr(0, &desc) < 0)
      return -1;
  if (task_count >= MAX_TASKS)
      return -1;

  safestrcpy(todo_list[task_count].description, desc, MAX_TASK_LEN);
  todo_list[task_count].done = 0;
  task_count++;
  return 0;
}

int sys_todo_list(void) {
  for (int i = 0; i < task_count; i++) {
      cprintf("%d. [%s] %s\n", i + 1, todo_list[i].done ? "Done" : "Pending", todo_list[i].description);
  }
  return 0;
}

int sys_todo_done(void) {
  int id;
  if (argint(0, &id) < 0)
      return -1;
  if (id < 1 || id > task_count)
      return -1;

  todo_list[id - 1].done = 1;
  return 0;
}