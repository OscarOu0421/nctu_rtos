#  Lab 2 for uC/OS-II: EDF Scheduler

## Objective
- To implement an EDF scheduler in uC/OS-II

## MOdify List
- lab2/SOFTWARE/uCOS-II/lab2/BC45/SOURCE/TEST.C
- lab2/SOFTWARE/uCOS-II/SOURCE/OS_CORE.C
- lab2/SOFTWARE/uCOS-II/SOURCE/uCOS_II.H 

## Implementation
- Identify where/when scheduling decisions are made
  - OS_Sched, OSIntExit(), OSStart()
- Add proper deadline information to task information
- Add code to pickup a ready job with the earliest deadline at the re-scheduling points
