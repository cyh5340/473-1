/**
 * 
 * File             : scheduler.c
 * Description      : This is a stub to implement all your scheduling schemes
 *
 * Author(s)        : @author
 * Last Modified    : @date
*/

// Include Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <time.h>

#include <math.h>
#include <pthread.h>

void init_scheduler(int sched_type );
int schedule_me(float currentTime, int tid, int remainingTime, int tprio );
int num_preemeptions(int tid);
float total_wait_time(int tid);

struct thread{
	float cT;
	int id;
	int rT;
	int prio;
	pthread_cond_t t;
//	struct thread* next;
	float w; //for total wait time;
	int p; //for total preemption;
	int work; //1 if working 0 if not
};
struct thread threadList[100];
#define FCFS    0
#define SRTF    1
#define PBS     2
#define MLFQ    3
//define a structure for keeping records for the threads
int threadExists(int id){
	int i=0;
	for(i=0; i<100; i++){
		if(threadList[i].id==id){return 0;}
	}
	return -1;
}
//global variable
int scheduler_type;
void init_scheduler(int sched_type ) {
	scheduler_type = sched_type;
//	threadList = malloc(100*sizeof(struct thread));
	//I gave up link list, I really cant....
}

int schedule_me(float currentTime, int tid, int remainingTime, int tprio ) {
	pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&m);
	//but before that, make sure we need to run cases:
	int i=0, a=0;
	if(remainingTime=0){
		for(a=0; a<100; a++){break;}
		threadList[a].w=currentTime-threadList[a].cT;
		threadList[a].rT=0;
		threadList[a].work=0;
	}
	//then, if adding existed thread
	for(i=0; i<100; i++){
		if(threadList[i].id==tid){break;}
	}
	if(i!=100){currentTime+=1.0;}
	//adding new thread
	if(i=100){
		int k=0;
		for(k=0;k<100;k++){if(threadExists(threadList[k].id)==-1){break;}}
		threadList[k].id=tid;
		threadList[k].cT=currentTime;
		currentTime=ceil(currentTime);
		threadList[k].work=1;
		i=k;
	}
	//all the same whether it exist or not
	if(scheduler_type!=0){threadList[i].cT=currentTime;}
	threadList[i].rT=remainingTime;
	threadList[i].prio=tprio;
	threadList[i].t=(pthread_cond_t)PTHREAD_COND_INITIALIZER;
       if(scheduler_type==0){
        //case FCFS:
                int MIN=0;
                for(i=1;threadList[i].id!=NULL; i++){
                        if(threadList[i].cT<threadList[MIN].cT&&threadList[i].work==1){MIN=i;}
                        pthread_cond_wait(&threadList[i].t, &m);
                }
                pthread_cond_signal(&threadList[MIN].t);
                threadList[MIN].w=currentTime-threadList[MIN].cT;
        }
       //case SRTF:
        if(scheduler_type==1){
                int i=0;
                int MIN=0;
                //MIN for the least remaining time's id
                for(i=1;threadList[i].id!=NULL;i++){
                        if (threadList[i].rT < threadList[MIN].rT&&threadList[i].work==1){
                                threadList[MIN].p+=1;
                                MIN=i;
                        }
                        pthread_cond_wait(&threadList[i].t, &m);
                }
                pthread_cond_signal(&threadList[MIN].t);
                threadList[MIN].w=currentTime-threadList[MIN].cT;
                //unlock the shortest remaining time
        }
        if(scheduler_type==2){
        //case PBS:
        //priority based scheduling
                int MIN=0; //for the priority
                int i=0;
                for(i=1;threadList[i].id!=NULL; i++){
                        if(threadList[i].prio < threadList[MIN].prio&&threadList[i].work==1){
                                threadList[MIN].p++;
                                MIN=i;
                        }
                        pthread_cond_wait(&threadList[i].t, &m);
                }
                pthread_cond_signal(&threadList[MIN].t);
                threadList[MIN].w=currentTime-threadList[MIN].cT;
        }
	//	case MLFQ:
	if(scheduler_type==3){
	}

	pthread_mutex_unlock(&m);
	return currentTime;	
}
int num_preemeptions(int tid){
        int result=-1;
        int i=0;
        for(i=0;threadList[i].id!=NULL;i++){
                if(threadList[i].id==tid){result=threadList[i].p;}
        }
        return result;
}

float total_wait_time(int tid){
        float wait=-0.1;
        int i=0;
        for(i=0;threadList[i].id!=NULL; i++){
                if(threadList[i].id==tid){wait=threadList[i].w;}
        }
        return wait;
}


