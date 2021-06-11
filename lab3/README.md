# Lab 3 for uC/OS-II: Ceiling Priority Protocol

## Objective
- To implement Ceiling Priority Protocol for ucOS’s mutex locks

## MOdify List
- lab3/SOFTWARE/uCOS-II/lab3/BC45/SOURCE/TEST.C
- lab3/SOFTWARE/uCOS-II/SOURCE/OS_CORE.C
- lab3/SOFTWARE/uCOS-II/SOURCE/uCOS_II.H 
- lab3/SOFTWARE/uCOS-II/SOURCE/OS_MUTEX.C

## Ceiling Priority Protocol
- Highest Locker’s Priority Protocol
- The priority of the mutex lock is higher than the priorities of all the tasks sharing the lock
- Differently, when a task acquires a mutex lock, the task’s priority boosts to the priority of the lock

## Implementation
### I. OSMutexPend()
- Boost the locker’s priority to the mutex priority
### II. OSMutexPost()
- Restore the original priority of the locker
