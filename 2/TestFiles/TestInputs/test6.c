#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "memalloc.h"
#include <stdbool.h>
//***********************************************************************************
	 FILE * pFile;
int main(int argc, char ** argv)
{
	 pFile = fopen ("test6_output.txt","w");
    int size;
    int RAM_SIZE=1<<20;//1024*1024
    void* RAM=malloc(RAM_SIZE);//1024*1024
	setup(FIRST_FIT,RAM_SIZE,RAM);//First Fit, Memory size=1024*1024, Start of memory=RAM
//test 6
    size=20*1024;
	fprintf(pFile, "Allocating %s, size=%d\n"," void* a " ,  size );
	void* a=my_malloc(size);//We have 4 bytes header to save the size of that chunk in memory so the output starts at 4
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}
    if ((int)a==-1)
        fprintf(pFile, "This size can not be allocated!");
    else
    {
    	fprintf(pFile, "start of the chunk a: %d\n",(int)(a-RAM));
    	fprintf(pFile, "End of the chunk a: %d\n\n",(int)(a+size-RAM));
    }

    size=30*1024;
	fprintf(pFile, "Allocating %s, size=%d\n"," void* b " ,  size );
    void* b=my_malloc(size);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}
    if ((int)b==-1)
        fprintf(pFile, "This size can not be allocated!");
    else
    {
    	fprintf(pFile, "start of the chunk b: %d\n",(int)(b-RAM));
    	fprintf(pFile, "End of the chunk b: %d\n\n",(int)(b+size-RAM));
    }

    size=30*1024;
	fprintf(pFile, "Allocating %s, size=%d\n"," void* c " ,  size );
	void* c=my_malloc(size);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}
    if ((int)c==-1)
        fprintf(pFile, "This size can not be allocated!");
    else
    {
    	fprintf(pFile, "start of the chunk c: %d\n",(int)(c-RAM));
    	fprintf(pFile, "End of the chunk c: %d\n\n",(int)(c+size-RAM));
    }

    size=30*1024;
	fprintf(pFile, "Allocating %s, size=%d\n"," void* d " ,  size );
	void* d=my_malloc(size);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}
    if ((int)d==-1)
        fprintf(pFile, "This size can not be allocated!");
    else
    {
    	fprintf(pFile, "start of the chunk d: %d\n",(int)(d-RAM));
    	fprintf(pFile, "End of the chunk d: %d\n\n",(int)(d+size-RAM));
    }



    size=40*1024;
	fprintf(pFile, "Allocating %s, size=%d\n"," void* e " ,  size );
	void* e=my_malloc(size);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}
    if ((int)e==-1)
        fprintf(pFile, "This size can not be allocated!");
    else
    {
    	fprintf(pFile, "start of the chunk e: %d\n",(int)(e-RAM));
    	fprintf(pFile, "End of the chunk e: %d\n\n",(int)(e+size-RAM));
    }

	fprintf(pFile, "Freeing %s, size=%d\n"," d " , (int)(*(int *)((char*) d -4) ));
	my_free(d);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}
	fprintf(pFile, "Freeing %s, size=%d\n"," b " , (int)(*(int *)((char*) b -4) ));
	my_free(b);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}
	fprintf(pFile, "Freeing %s, size=%d\n"," c " , (int)(*(int *)((char*) c -4) ));
	my_free(c);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}


    size=80*1024;
	fprintf(pFile, "Allocating %s, size=%d\n"," void* f " ,  size );
	void* f=my_malloc(size);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}
    if ((int)f==-1)
        fprintf(pFile, "This size can not be allocated!");
    else
    {
    	fprintf(pFile, "start of the chunk f: %d\n",(int)(f-RAM));
    	fprintf(pFile, "End of the chunk f: %d\n\n",(int)(f+size-RAM));
    }

    fclose (pFile);
	return 0;
}

