# Lab 1 for uC/OS-II: Periodic Task Emulation

## Objectives
- To implement periodic tasks
- To observe the scheduling behaviors
  - Fixed priority scheduling

## Task Sets
- Two sets of periodic tasks
  - Task set 1 = { t1(1,3), t2(3,6) }
  - Task set 2 = { t1(1,3), t2(3,6), t3(4,9) }
  - Tasks all arrive at the same time
  - Show context switch behaviors
  - Show deadline violations if there is any

## Modify List
- lab1/SOFTWARE/uCOS-II/lab1/BC45/SOURCE/TEST.C
- lab1/SOFTWARE/uCOS-II/SOURCE/OS_CORE.C
- lab1/SOFTWARE/uCOS-II/SOURCE/uCOS_II.H

## Implementation
### I. OSTimeTick()
- Defined in OS_CORE.C, called every time when a clock interrupt arrives
- Add a piece of code in OSTimeTick to decrement the compTime counter in the running task’s os_tcb
  - The current task has consumed 1 tick
### II. OSIntExit()
- Defined in OS_CORE.C
- This function will manage the scheduling after the system has come back from the calling of ISR
- We need to print out the “preempt” event here
### III. OS_Sched()
- Defined in OS_CORE.C
- OS_Sched() is called when a task is voluntarily giving up its possession of the CPU
- We need to print out the “complete” event here
### IV. OSStart()
- Defined in OS_CORE.C
- This is function will try to find the task with the highest priority and schedule it to run.
- Called only once when the system executing tasks for the very first time
