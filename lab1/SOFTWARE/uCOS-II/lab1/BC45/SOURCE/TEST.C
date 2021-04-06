/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                           (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*                                               EXAMPLE #1
*********************************************************************************************************
*/

#include "includes.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE                 512       /* Size of each task's stacks (# of WORDs)            */
#define  N_TASKS                        3        /* Number of identical tasks                          */

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

        void  Task1(void *data); 
        void  Task2(void *data);                      /* Function prototypes of tasks                  */
        void  Task3(void *data);
static  void  TaskStartCreateTasks(void);

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

void  main (void)
{
    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

    OSInit();                                              /* Initialize uC/OS-II                      */

    PC_DOSSaveReturn();                                    /* Save environment to return to DOS        */
    PC_VectSet(uCOS, OSCtxSw);                             /* Install uC/OS-II's context switch vector */

    OSTaskCreate(Task1, (void *)0, &TaskStk[0][TASK_STK_SIZE - 1], 0);

    OSStart();                                             /* Start multitasking                       */
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                             CREATE TASKS
*********************************************************************************************************
*/

static  void  TaskStartCreateTasks (void)
{
    OSTaskCreate(Task2, (void *)0, &TaskStk[1][TASK_STK_SIZE - 1], 1);
    OSTaskCreate(Task3, (void *)0, &TaskStk[2][TASK_STK_SIZE - 1], 2);  
}

/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/

void  Task1 (void *pdata)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif

    INT16S     key;
    int start;      /*the start time    */
    int end;        /*the end time      */
    int toDelay;

    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);                           /* Install uC/OS-II's clock tick ISR        */
    PC_SetTickRate(1u);                      /* Reprogram tick rate                      */
    OS_EXIT_CRITICAL();

    TaskStartCreateTasks();

    pdata = pdata;
    start = OSTimeGet();
    OSTCBCur->compTime = 1;
    OSTCBCur->period = 3;
    while(1){

        if(OSTimeGet()<500){
            // printf("Task%d ",1);
            printf("%3d\t", OSTCBCur->PrintBuf.TimeTick);
            if(OSTCBCur->PrintBuf.event==1)
                printf("%10s", "Preempt\t");
            else    
                printf("%10s", "Complete\t");
            printf("%10d\t%10d\n", OSTCBCur->PrintBuf.FromTaskPrio, OSTCBCur->PrintBuf.ToTaskPrio);
        }
        while(OSTCBCur->compTime>0){}

        end = OSTimeGet();
        toDelay = (OSTCBCur->period) - (end-start);
        if(toDelay<0)
            printf("Task1 deadline\n");
        start += OSTCBCur->period;
        OSTCBCur->compTime = 1;

        if (PC_GetKey(&key) == TRUE) {                     /* See if key has been pressed              */
            if (key == 0x1B) {                             /* Yes, see if it's the ESCAPE key          */
                PC_DOSReturn();                            /* Return to DOS                            */
            }
        }
        OSTimeDly(toDelay);
    }
}
void  Task2 (void *pdata)
{
    int start;      /*the start time    */
    int end;        /*the end time      */
    int toDelay;
    pdata = pdata;
    start = OSTimeGet();
    OSTCBCur->compTime = 3;
    OSTCBCur->period = 6;
    while(1){

        if(OSTimeGet()<500){
            // printf("Task%d ",2);
            printf("%3lu\t", OSTCBCur->PrintBuf.TimeTick);
            if(OSTCBCur->PrintBuf.event==1)
                printf("%10s", "Preempt\t");
            else    
                printf("%10s", "Complete\t");
            printf("%10hhu\t%10hhu\n", OSTCBCur->PrintBuf.FromTaskPrio, OSTCBCur->PrintBuf.ToTaskPrio);
        }
        while(OSTCBCur->compTime>0){}

        end = OSTimeGet();
        toDelay = (OSTCBCur->period) - (end-start);
        if(toDelay<0)
            printf("Task2 deadline\n");
        start += OSTCBCur->period;
        OSTCBCur->compTime = 3;

        OSTimeDly(toDelay);
    }
}
void  Task3 (void *pdata)
{
    int start;      /*the start time    */
    int end;        /*the end time      */
    int toDelay;
    pdata = pdata;
    start = OSTimeGet();
    OSTCBCur->compTime = 4;
    OSTCBCur->period = 9;
    while(1){

        if(OSTimeGet()<500){
            // printf("Task%d ",2);
            printf("%3lu\t", OSTCBCur->PrintBuf.TimeTick);
            if(OSTCBCur->PrintBuf.event==1)
                printf("%10s", "Preempt\t");
            else    
                printf("%10s", "Complete\t");
            printf("%10hhu\t%10hhu\n", OSTCBCur->PrintBuf.FromTaskPrio, OSTCBCur->PrintBuf.ToTaskPrio);
        }
        while(OSTCBCur->compTime>0){}

        end = OSTimeGet();
        toDelay = (OSTCBCur->period) - (end-start);
        start += OSTCBCur->period;
        OSTCBCur->compTime = 4;
        if(toDelay<0){
            printf("Task3 deadline\n");
        }
        else{
            OSTimeDly(toDelay);
        }
    }
}