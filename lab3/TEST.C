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
#define  N_TASKS                       3        /* Number of identical tasks                          */

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_TCB        *ptcb;
OS_EVENT      *r1, *r2;
INT8U         err1, err2;
int             i;


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

        void  Task1(void *data); 
        void  Task2(void *data);                      /* Function prototypes of tasks                  */
        void  Task3(void *data);
        void  Print(void);
        void  ArgumentSet(void);

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

    OSTaskCreate(Task1, (void *)0, &TaskStk[0][TASK_STK_SIZE - 1], 3);
    OSTaskCreate(Task2, (void *)0, &TaskStk[1][TASK_STK_SIZE - 1], 4);
    OSTaskCreate(Task3, (void *)0, &TaskStk[2][TASK_STK_SIZE - 1], 5); 
    ArgumentSet(); 
    r1 = OSMutexCreate(1, &err1);
    r2 = OSMutexCreate(2, &err2);

    OSStart();                                             /* Start multitasking                       */
}
/*$PAGE*/
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
    int arrive;     /*  arrive time   */
    int toDelay;
    int useR1, useR2;
    int prio;
    pdata = pdata;
    arrive = 0;

    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);                           /* Install uC/OS-II's clock tick ISR        */
    PC_SetTickRate(1u);                      /* Reprogram tick rate                      */
    OS_EXIT_CRITICAL();

    while(1){
        if (PC_GetKey(&key) == TRUE) {                     /* See if key has been pressed              */
            if (key == 0x1B) {                             /* Yes, see if it's the ESCAPE key          */
                PC_DOSReturn();                            /* Return to DOS                            */
            }
        }
        OSTimeDly(8);

        OS_ENTER_CRITICAL();
        Print();
        OS_EXIT_CRITICAL();

        start = OSTimeGet();
        useR1 = 0;
        useR2 = 0;
        while(OSTCBCur->compTime>0){
            if(OSTCBCur->compTime==4&&useR1==0){
                prio = OSTCBCur->OSTCBPrio;
                OSMutexPend(r1, 5, &err1);
                OS_ENTER_CRITICAL();
                buf[pos][0] = OSTimeGet();
                buf[pos][1] = 2;    //2:lock
                buf[pos][2] = 1;    //1:r1
                buf[pos][3] = prio;
                buf[pos][4] = OSTCBCur->OSTCBPrio;
                pos = (pos+1)==row_size ? 0 : pos+1;
                useR1 = 1;
                OS_EXIT_CRITICAL();
            }
            if(OSTCBCur->compTime==2&&useR2==0){
                prio = OSTCBCur->OSTCBPrio;
                OSMutexPend(r2, 5, &err2);
                OS_ENTER_CRITICAL();
                buf[pos][0] = OSTimeGet();
                buf[pos][1] = 2;    //2:lock
                buf[pos][2] = 2;    //2:r2
                buf[pos][3] = prio;
                buf[pos][4] = OSTCBCur->OSTCBPrio;
                pos = (pos+1)==row_size ? 0 : pos+1;
                useR2 = 1;
                OS_EXIT_CRITICAL();
            }
        }
        prio = OSTCBCur->OSTCBPrio;
        OSMutexPost(r1);
        OS_ENTER_CRITICAL();
        buf[pos][0] = OSTimeGet();
        buf[pos][1] = 3;    //3:unlock
        buf[pos][2] = 1;    //1:r1
        buf[pos][3] = prio;
        buf[pos][4] = OSTCBCur->OSTCBPrio;
        pos = (pos+1)==row_size ? 0 : pos+1;
        useR1 = 0;
        OS_EXIT_CRITICAL();

        prio = OSTCBCur->OSTCBPrio;
        OSMutexPost(r2);
        OS_ENTER_CRITICAL();
        buf[pos][0] = OSTimeGet();
        buf[pos][1] = 3;    //3:unlock
        buf[pos][2] = 2;    //2:r2
        buf[pos][3] = prio;
        buf[pos][4] = OSTCBCur->OSTCBPrio;
        pos = (pos+1)==row_size ? 0 : pos+1;
        useR2 = 0;
        OS_EXIT_CRITICAL();

        OS_ENTER_CRITICAL();
        end = OSTimeGet();
        toDelay = (OSTCBCur->period) - (end-arrive);
        arrive += OSTCBCur->period;

        OSTCBCur->compTime = 1;

        if(toDelay<0)
            printf("Task1 deadline\n");
        else
            OSTimeDly(toDelay);
        OS_EXIT_CRITICAL();
    }
}
void  Task2 (void *pdata)
{
    int start;      /*  start time      */
    int end;        /*  end time        */
    int arrive;     /*  arrive time     */
    int toDelay;
    int useR2;
    int prio;
    pdata = pdata;
    arrive = 0;
    while(1){
        // Print();
        OSTimeDly(4);
        start = OSTimeGet();
        useR2 = 0;
        while(OSTCBCur->compTime>0){
            if(OSTCBCur->compTime==4&&useR2==0){
                prio = OSTCBCur->OSTCBPrio;
                OSMutexPend(r2, 5, &err2);
                OS_ENTER_CRITICAL();
                buf[pos][0] = OSTimeGet();
                buf[pos][1] = 2;    //2:lock
                buf[pos][2] = 2;    //2:r2
                buf[pos][3] = prio;
                buf[pos][4] = OSTCBCur->OSTCBPrio;
                pos = (pos+1)==row_size ? 0 : pos+1;
                useR2 = 1;
                OS_EXIT_CRITICAL();
            }
        }
        prio = OSTCBCur->OSTCBPrio;
        OSMutexPost(r2);
        OS_ENTER_CRITICAL();
        buf[pos][0] = OSTimeGet();
        buf[pos][1] = 3;    //3:unlock
        buf[pos][2] = 2;    //2:r2
        buf[pos][3] = prio;
        buf[pos][4] = OSTCBCur->OSTCBPrio;
        pos = (pos+1)==row_size ? 0 : pos+1;
        useR2 = 0;
        OS_EXIT_CRITICAL();

        OS_ENTER_CRITICAL();
        end = OSTimeGet();
        toDelay = (OSTCBCur->period) - (end-arrive);
        arrive += OSTCBCur->period;

        OSTCBCur->compTime = 3;

        if(toDelay<0)
            printf("Task2 deadline\n");
        else
            OSTimeDly(toDelay);
        OS_EXIT_CRITICAL();
    }
}
void  Task3 (void *pdata)
{
    int start;      /*  start time      */
    int end;        /*  end time        */
    int arrive;     /*  arrive time     */
    int toDelay;
    int useR1;
    int prio;
    pdata = pdata;
    arrive = 0;
    while(1){
        // Print();
        start = OSTimeGet();
        useR1 = 0;
        while(OSTCBCur->compTime>0){
            if(OSTCBCur->compTime==7&&useR1==0){
                prio = OSTCBCur->OSTCBPrio;
                OSMutexPend(r1, 5, &err1);
                OS_ENTER_CRITICAL();
                buf[pos][0] = OSTimeGet();
                buf[pos][1] = 2;    //2:lock
                buf[pos][2] = 1;    //1:r1
                buf[pos][3] = prio;
                buf[pos][4] = OSTCBCur->OSTCBPrio;
                pos = (pos+1)==row_size ? 0 : pos+1;
                useR1 = 1;
                OS_EXIT_CRITICAL();
            }
        }
        prio = OSTCBCur->OSTCBPrio;
        OSMutexPost(r1);
        OS_ENTER_CRITICAL();
        buf[pos][0] = OSTimeGet();
        buf[pos][1] = 3;    //3:unlock
        buf[pos][2] = 1;    //1:r1
        buf[pos][3] = prio;
        buf[pos][4] = OSTCBCur->OSTCBPrio;
        pos = (pos+1)==row_size ? 0 : pos+1;
        useR1 = 0;
        OS_EXIT_CRITICAL();

        OS_ENTER_CRITICAL();
        end = OSTimeGet();
        toDelay = (OSTCBCur->period) - (end-arrive);
        arrive += OSTCBCur->period;

        OSTCBCur->compTime = 3;

        if(toDelay<0)
            printf("Task3 deadline\n");
        else
            OSTimeDly(toDelay);
        OS_EXIT_CRITICAL();
    }
}
void Print(void){
    if(print_pos<pos){
        for(i=print_pos; i<pos; i++){
            if(buf[i][1]==0||buf[i][1]==1){
                printf("%d\t", buf[i][0]);
                if(buf[i][1]==0)    printf("Preempt\t");
                else                printf("Complete\t");
                printf("%d\t%d\n", buf[i][2], buf[i][3]);
            }else if(buf[i][1]==2||buf[i][1]==3){
                printf("%d\t", buf[i][0]);
                if(buf[i][1]==2)    printf("lock\t");
                else                printf("unlock\t");
                if(buf[i][2]==1)    printf("R1\t");
                else                printf("R2\t");
                printf("(Prio=%d changes to=%d)\n", buf[i][3], buf[i][4]);
            }
        }
    }
    else{
        for(i=print_pos; i<row_size; i++){
            if(buf[i][1]==0||buf[i][1]==1){
                printf("%d\t", buf[i][0]);
                if(buf[i][1]==0)    printf("Preempt\t");
                else                printf("Complete\t");
                printf("%d\t%d\n", buf[i][2], buf[i][3]);
            }else if(buf[i][1]==2||buf[i][1]==3){
                printf("%d\t", buf[i][0]);
                if(buf[i][1]==2)    printf("lock\t");
                else                printf("unlock\t");
                if(buf[i][2]==1)    printf("R1\t");
                else                printf("R2\t");
                printf("(Prio=%d changes to=%d)\n", buf[i][3], buf[i][4]);
            }
        }
        for(i=0; i<pos; i++){
            if(buf[i][1]==0||buf[i][1]==1){
                printf("%d\t", buf[i][0]);
                if(buf[i][1]==0)    printf("Preempt\t");
                else                printf("Complete\t");
                printf("%d\t%d\n", buf[i][2], buf[i][3]);
            }else if(buf[i][1]==2||buf[i][1]==3){
                printf("%d\t", buf[i][0]);
                if(buf[i][1]==2)    printf("lock\t");
                else                printf("unlock\t");
                if(buf[i][2]==1)    printf("R1\t");
                else                printf("R2\t");
                printf("(Prio=%d changes to=%d)\n", buf[i][3], buf[i][4]);
            }
        }
    }
    print_pos = pos;
}
void ArgumentSet(void){
    ptcb = OSTCBList;
    while(ptcb->OSTCBPrio==3 || ptcb->OSTCBPrio==4 || ptcb->OSTCBPrio==5){
        // printf("Priority: %d set argument\n", ptcb->OSTCBPrio);
        if(ptcb->OSTCBPrio==3){
            ptcb->compTime = 6;
            ptcb->period = 30;
        }
        else if(ptcb->OSTCBPrio==4){
            ptcb->compTime = 6;
            ptcb->period = 30;
        }
        else if(ptcb->OSTCBPrio==5){
            ptcb->compTime = 9;
            ptcb->period = 30;
        }
        ptcb = ptcb->OSTCBNext;
    }

    row_size = 20;
    col_size = 5;
    pos = 0;
    print_pos = 0;
    buf = (int**)malloc(sizeof(int*)*row_size);
    for(i=0; i<row_size; i++)
        buf[i] = (int*)malloc(sizeof(int)*col_size);
}