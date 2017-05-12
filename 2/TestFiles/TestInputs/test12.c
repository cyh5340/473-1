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
	pFile = fopen ("test12_output.txt","w");
    int size;
    int RAM_SIZE=1<<20;
    void* RAM=malloc(RAM_SIZE);//1024*1024
	setup(BUDDY_SYSTEM,RAM_SIZE,RAM);//Buddy System, Memory size=1024*1024, Start of memory=RAM

    //test 12
    size=60*1024;
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
    	fprintf(pFile, "start of the chunk a: %f K\n",(float)((int)a-(int)RAM)/1024);
    	fprintf(pFile, "End of the chunk a: %f K\n\n",(float)((int)a+size-(int)RAM)/1024);
    }
    size=60*1024;
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
    	fprintf(pFile, "start of the chunk b: %f K\n",(float)((int)b-(int)RAM)/1024);
    	fprintf(pFile, "End of the chunk b: %f K\n\n",(float)((int)b+size-(int)RAM)/1024);
    }

    size=60*1024;
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
    	fprintf(pFile, "start of the chunk c: %f K\n",(float)((int)c-(int)RAM)/1024);
    	fprintf(pFile, "End of the chunk c: %f K\n\n",(float)((int)c+size-(int)RAM)/1024);
    }

    size=60*1024;
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
    	fprintf(pFile, "start of the chunk d: %f K\n",(float)((int)d-(int)RAM)/1024);
    	fprintf(pFile, "End of the chunk d: %f K\n\n",(float)((int)d+size-(int)RAM)/1024);
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
	fprintf(pFile, "Freeing %s, size=%d\n"," a " , (int)(*(int *)((char*) a -4) ));
    my_free(a);
	if(num_holes()>0)
	{
		fprintf(pFile, "Average hole size = %.1lf [%d/%d]\n", (float)num_free_bytes()/num_holes(),num_free_bytes(), num_holes());
	}
	else
	{
		fprintf(pFile, "Total Free Bytes = %d, Num Holes = %d\n", num_free_bytes(), num_holes());
	}

    size=250*1024;
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
    	fprintf(pFile, "start of the chunk e: %f K\n",(float)((int)e-(int)RAM)/1024);
    	fprintf(pFile, "End of the chunk e: %f K\n\n",(float)((int)e+size-(int)RAM)/1024);
    }


    size=500*1024;
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
    	fprintf(pFile, "start of the chunk f: %f K\n",(float)((int)f-(int)RAM)/1024);
    	fprintf(pFile, "End of the chunk f: %f K\n\n",(float)((int)f+size-(int)RAM)/1024);
    }
    fclose (pFile);
    return 0;

}

