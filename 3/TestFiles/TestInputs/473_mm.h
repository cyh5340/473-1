#ifndef _473_MM_H
#define _473_MM_H
#include <stdio.h>

/*
'mm_init()' initializes the memory management system. 
'vm' denotes the pointer to the start of virtual address space, 
'vm_size' denotes the size of the virtual address space, 
'n_frames' denotes the number of physical pages available in the system, 
'page_size' denotes the size of both virtual and physical pages, 
'policy' can take values 1 or 2 -- 1 indicates fifo replacement policy and 2 indicates clock replacement policy. 
*/
void mm_init(void* vm, int vm_size, int n_frames, int page_size, int policy); 

/*
'mm_report_npage_faults' should return the total number of page faults of the entire system (across all virtual pages). 
*/
unsigned long mm_report_npage_faults(); 

/*
'mm_report_nwrite_backs' should return the total number of write backs of the entire system (across all virtual pages). 
*/
unsigned long mm_report_nwrite_backs();
unsigned long mm_nsigsegvs();
extern int NUM_VM_PAGES;


#endif

