////////////////////////////////////////////////////////////////////////////
//
// File             : 473_mm.c
// Description      : Construct and compare two page replacement algorithms to manage the limited physical memory
//
// Author           : Crystal Ho 
// Last Modified    : @date
//

// Headers
#include <unistd.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include "473_mm.h"

// Macros
#define FIFO    1
#define CLOCK   2
int s; //n_seg
int m; //framesize
void* v; //header
int page; //pagesize
int *array; //frame
int nf;
int nw;
int ns;
int* ar;//history
int c;//counter for history
int cc;//counter for frame (which is first)
int* cl;//
int* rw;//read/write record for write back
int py; //policy
void segfault_sigaction(int, siginfo_t *, void *);
unsigned long mm_nsigsegvs()
{
	return s;
}
void mm_init(void* vm, int vm_size, int n_frames, int page_size , int policy )
{
	//record keeping; frame; write back; reference for clock
	ar=calloc(100, sizeof(int));
	array= calloc(n_frames, sizeof(int));
	rw=calloc(n_frames, sizeof(int));
	cl=calloc(100, sizeof(int));
	//counter for results
	ns=0;
	nf=0;
	nw=0;
	c=0;
	cc=0;
	//set to global
	py=policy;
	m=n_frames;
	v=vm;
	page=page_size;
	//signal handler
	struct sigaction sa;
	memset(&sa, 0, sizeof(sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction=segfault_sigaction;
	sa.sa_flags=SA_SIGINFO;
	//set signal to PROT_NONE
	mprotect(vm, vm_size, PROT_NONE);

	sigaction(SIGSEGV, &sa, NULL);
}
void segfault_sigaction(int signal, siginfo_t *si, void *arg){
//	printf("\n\nsegfault at %p\n", si->si_addr);
	int p;
	int i=0, j=0, n=0, a=0;
	//find page number
	p=(((int)(si->si_addr)-(int)(v))/page)+1;

	//see if it's in the frame
	for(i=0; i<m; i++){if(array[i]==p){n=1;}}

	//when it's not in the frame yet, read
	if(n==0){
		if(array[m-1]!=0){
			//if clock
			if(py==2){
				while(cl[array[cc]!=0]){
					if(cc=m){cc=0;}
					if(cl[array[cc+a]]!=0){
						cl[array[cc]]=0;
						cc++;
					}
				}
			}
			mprotect(v+((array[cc]-1)*page), page,PROT_NONE);
			if(rw[cc]==1){
				nw++;
				rw[cc]=0;
			}
			ar[array[cc]]++;
		}
		array[cc]=p;
		if(py==2){
			if(cl[p]==1){cl[p]=0;}
			if(cl[p]==0){cl[p]=1;}
		}	
		cc++;
		if(cc==m){cc=0;}
		nf++;
		ns++;
		mprotect(v+((p-1)*page), page,PROT_READ);
	}
	//when it's already in the frame, write
	if(n==1){
		for(i=0;i<m;i++){if(array[i]==p){rw[i]=1;}}
		//if clock
		if(py==2){if(cl[p]==1){cl[p]=0;}}
		ns++;
		mprotect((void*)(v+(p-1)*page), page,PROT_READ | PROT_WRITE);
	}
	s++;
}
int mm_report_npage_evicts(int i)
{
	return ar[i+1];
}
int mm_report_nframe_evicts(int i)
{
	return 0l;
}

unsigned long mm_report_npage_faults()
{
	return nf;
}

unsigned long mm_report_nwrite_backs()
{
	return nw;
}
