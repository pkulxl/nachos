// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// testnum is set in main.cc
int testnum = 1;
    Thread *t =  new Thread("thread_0");
    Thread *t1 = new Thread("thread_1");
    Thread *t2 = new Thread("thread_2");
    Thread *t3 = new Thread("thread_3");
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void SimpleThread_3(int arg)
{
    int num;
    printf("---enter SimpleThread\n");
    for (num = 0; num < 5; num++) {
	printf("-------thread_%d  looped %d times\n",currentThread->get_tid()  ,num);
        // currentThread->Yield();
    }
}
void SimpleThread_2(int arg)
{
    int num;
    printf("---enter SimpleThread_2\n");
    for (num = 0; num < 5; num++) {
	printf("-------thread_%d looped %d times\n",currentThread->get_tid() ,num);
    if (num == 1)
    {
      t3->Fork(SimpleThread_3,1);
    }  
        // currentThread->Yield();
    }
}
void 
SimpleThread_1(int arg)
{
    int num;
    /* modify*/
   // printf("---enter SimpleThread_1\n");
    /**/
    for (num = 0; num < 5; num++) {
	printf("-------thread_%d  looped %d times\n",currentThread->get_tid() ,num);
    if (num == 1)
    {
      t2->Fork(SimpleThread_2,1);
    }  
        // currentThread->Yield();
    }
}
void
SimpleThread(int arg)
{
    int num;
    /* modify*/
  //  printf("---enter SimpleThread\n");
    /**/
    for (num = 0; num < 7; num++) {
	printf("-------thread_%d  looped %d times\n",currentThread->get_tid() ,num);
    if (num == 3)
    {
      t1->Fork(SimpleThread_1,1);
      //t2->Fork(SimpleThread_2,1);
    }
    interrupt->SetLevel(IntOff);
    interrupt->SetLevel(IntOn);
        // currentThread->Yield();
    }
}
void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");
    // t->set_prio(5);
    // t1->set_prio(4);
    // t2->set_prio(3);
    // t3->set_prio(2);
    t->Fork(SimpleThread,1);
    // t1->Fork(SimpleThread,1);
    // t2->Fork(SimpleThread,1);
    // t3->Fork(SimpleThread,1);
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------
void 
Simple(int arg)
{
    int num;
    for (num = 1;num<8;num++)
    {
    printf("-------thread_%d looped %d times\n",currentThread->get_tid(),num);
     interrupt->SetLevel(IntOff);
     interrupt->SetLevel(IntOn);
    }
}
void 
ThreadTest2()
{
   // printf("2\n");
     DEBUG('t',"Entering ThreadTest2");
    //  t->set_prio(10);
    //  t1->set_prio(8);
    //  t2->set_prio(6);
     t->Fork(Simple,1);
    //  t1->Fork(Simple,1);
    //  t2->Fork(Simple,1);     
}
void 
Simple3(int arg)
{
    int num;
    for (num = 1;num<4;num++)
    {
    printf("-------thread_%d looped %d times\n",currentThread->get_tid(),num);
     interrupt->SetLevel(IntOff);
     interrupt->SetLevel(IntOn);
     currentThread->Yield();
    }
}
void ThreadTest3()
{
   DEBUG('t',"Entering ThreadTest3");
   t->Fork(Simple3,1);
   t1->Fork(Simple3,1);
}
// void 
// print_status(int arg)
// {
//    // printf("threadID 0 status : running\n");  //main线程理解成一直在运行，手动输出其运行信息
//     printf("threadID %d status : runnning\n",currentThread->get_tid());
//     int j = currentThread->get_tid();
//     for (int i = 1;i<128;i++)
//     {
//         if (i!=j && ThreadID[i]==1)
//         {
//             printf("threadID %d status : ready\n",i);
//         }
//     }
//     printf("\n");
// }
// void 
// ThreadTest3()
// {
//     DEBUG('t',"Entering ThreadTest3");
//     Thread *t1 = new Thread("forkded thread");
//     Thread *t2 = new Thread("forkded thread");
//     Thread *t3 = new Thread("forkded thread");
//     t1->Fork(print_status,1);
//     t2->Fork(print_status,1);
//     t3->Fork(print_status,1);
// }


//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    case 2:
    ThreadTest2();
    break;
    case 3:
    ThreadTest3();
    break;
    default:
	printf("No test specified.\n");
	break;
    }
}

