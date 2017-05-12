#include "473_mm.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
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
	int vm_size = 20*PAGE_SIZE;NUM_VM_PAGES = vm_size/PAGE_SIZE;
	int temp;
	FILE* f1 = fopen("test6.txt", "w");

	vm_ptr=(int*)memalign(PAGE_SIZE, vm_size);
	if(vm_ptr==NULL)
	{
		printf("FAILURE in virtual memory allocation\n");	
		return 0;
	}

	mm_init((void*)vm_ptr, vm_size, 10, PAGE_SIZE, 1);
	mm_log(f1);	

	/* virtual memory access starts */
	int i;


	for (i=0;i<=19;i++)
	{
        vm_ptr[8 + ((int)((i*PAGE_SIZE)/sizeof(int)))]=64;  // Write virtual page i
        mm_log(f1);
	}

	for (i=0;i<=19;i++)
	{
        temp = vm_ptr[8 + ((int)((i*PAGE_SIZE)/sizeof(int)))];  // Read virtual page i
        mm_log(f1);
	}	

	/* virtual memory access ends */

	free(vm_ptr);
	return 0;
}

