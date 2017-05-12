#include "473_mm.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>


int NUM_VM_PAGES=0;
void report_per_page_evict_data(FILE *f1)
{
	//starts from 0
	int i = 0;
	for(i = 0; i < NUM_VM_PAGES; i++)
	{
		fprintf(f1, "%d,",mm_report_npage_evicts(i));
	}
}
void mm_log(FILE *f1)
{
	fprintf(f1, "%ld %ld ", mm_report_npage_faults(), mm_report_nwrite_backs());	
	report_per_page_evict_data(f1);
	fprintf(f1, "%ld", mm_nsigsegvs());
	fprintf(f1, "\n");
}
int main ()
{
	int* vm_ptr;
	int PAGE_SIZE = sysconf(_SC_PAGE_SIZE);
	//printf("%d\n", PAGE_SIZE);
	int vm_size = 16*PAGE_SIZE;
	NUM_VM_PAGES = vm_size/PAGE_SIZE;
	int temp;
	FILE* f1 = fopen("test1.txt", "w");

	vm_ptr=memalign(PAGE_SIZE, vm_size);
	if(vm_ptr==NULL)
	{
		printf("FAILURE in virtual memory allocation\n");	
		return 0;
	}

	mm_init((void*)vm_ptr, vm_size, 4, PAGE_SIZE, 1);
	mm_log(f1);	

	/* virtual memory access starts */
	
	temp = vm_ptr[8];					// Read virtual page 1
	mm_log(f1);												 
	vm_ptr[8 + ((int)((1*PAGE_SIZE)/sizeof(int)))] = 72; 	// Write virtual page 2
	mm_log(f1);												 
	vm_ptr[16] = 12;					// Write virtual page 1 
	mm_log(f1);												 
	temp = vm_ptr[8 + ((int)((2*PAGE_SIZE)/sizeof(int)))];	// Read virtual page 3
	mm_log(f1);												 
	temp = vm_ptr[8 + ((int)((3*PAGE_SIZE)/sizeof(int)))];	// Read virtual page 4
	mm_log(f1);												 
	temp = vm_ptr[24];					// Read virtual page 1 
	mm_log(f1);												 
	temp = vm_ptr[8 + ((int)((4*PAGE_SIZE)/sizeof(int)))];	// Read virtual page 5
	mm_log(f1);												 
	vm_ptr[32] = 64;					// Write virtual page 1  
	mm_log(f1);												 
	temp = vm_ptr[16 + ((int)((1*PAGE_SIZE)/sizeof(int)))]; // Read virtual page 2
	mm_log(f1);												 

	/* virtual memory access ends */

	free(vm_ptr);
	fclose(f1);
	return 0;
}

