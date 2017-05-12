/*****************************************************************
 *
 * File             : my_memory.c
 * Description      :
 *
 * Author           : @author(s)
 * Last Modified    : @date
 *
**/
// Include files
#include <stdio.h>
#include <stdlib.h>
#include "memalloc.h"
struct size{
	char* add;
	int sz;
	int h;
};
int hole=1;
struct size s[10];
char* array;
int* record;
int mem;
int fr=0;
int rs;
int f;//for the total freebytes
int mt;//for malloc_type
void setup( int malloc_type, int mem_size, void* start_of_memory ) {
	mt=malloc_type;
	array=malloc(sizeof(start_of_memory));
	array=start_of_memory;//storing the header address
	record=malloc(sizeof(int)*mem_size);
	//set the original values all to 0 to show it's unused
	f=mem_size;
	mem=mem_size;
}

void *my_malloc(int size) {
	int i=0;//for indexs
	int j=0;//for size
	int r;//return value
	//first fit
	if(mt==0){
		if(size>f){return (void*)-1;}
		f=f-size-4;
		int h=0;//head
		while(record[i]){
			//search for spaces
			if(record[i]!=1){
				if(i-h>=size+4){break;}
				i++;
			}
			if(record[i]==1){
				while(record[i]==1){i++;}
				h=i;
			}
		}
		//mark as used
		int a=0;
		while(s[a].add!=0){a++;}	
		s[a].add=array+h+4;
		s[a].sz=size;
		s[a].h=h;
		int b=0;
		for(b=0;b<size+4;b++){record[h+b]=1;}
		void *ar = (void*)( (int*)(array+h) );
		*( (int*)(array+h) ) = size;
		return array+h+4;
	}
	//best fit
	if(mt==1){
		if(size>f){return (void*)-1;}
	f=f-size-4;
		int min=mem;//for the minimum space to use
		int minr=0;
		for(i=0;i<mem;i++){
			//search for spaces
			r=i;
			while(record[i]!=1){i++;}
			if(min>=(i-r)&&(i-r)>=size+4){minr=r;min=i-r;}
		}
		int a=0;
		while(s[a].add!=0&&s[a].sz>0){a++;}	
		s[a].add=array+minr+4;
		s[a].sz=size;
		s[a].h=minr;
		for(a=0;a<size+4;a++){record[minr+a]=1;}
		void *ar = (void*)( (int*)(array+minr) );
		*( (int*)(array+minr) ) = size;
		return array+minr+4;
	}

	//worst fit
	if(mt==2){
		if(size>f){return (void*)-1;}
	f=f-size-4;
		int max=0;//for the maximum space to use
		int maxr=0;
		for(i=0;i<mem;i++){
			//search for spaces
			r=i;
			while(record[i]!=1){i++;}
			if(max<=(i-r)&&(i-r)>=size+4){maxr=r;max=i-r;}
		}
		int a=0;
		while(s[a].add!=0&&s[a].sz>0){a++;}	
		s[a].add=array+maxr+4;
		s[a].sz=size;
		s[a].h=maxr;
		for(a=0;a<size+4;a++){record[a+maxr]=1;}
		void *ar = (void*)( (int*)(array+maxr) );
		*( (int*)(array+maxr) ) = size;
		return array+maxr+4;
	}

	//buddy system
	if(mt==3){
		int s2=2;
		while(s2<=size){s2*=2;}
		if(s2>f){return (void*)-1;}
		f=f-s2;
		int min=mem;//for the minimum space to use
		int minr=0;
		int j=2;
		//first case
		if(record[1]!=1){
			minr=0;
			if(fr!=1){
				for(j=1;j*2<=mem;j*=2){
					if(j*2>=s2){record[j*2]=2;}
				}
				record[0]=2;
			}
			//if there's no more blocks, add some
			if(rs==1){
				int m=mem/4;
				while(record[m+mem/2]!=2){m/=2;break;}
				record[2*m+mem/2]=2;
			}
		}
	
		else{
			for(j=2;j*2<=mem;j*=2){
				//search for spaces
				if(record[j+1]!=1&&record[j]==2&&min>(j*2-j)&&(j*2-j)>=s2){
					minr=j;
					min=j*2-j;
				}
			}
		}
		
		record[minr+1]=1;
		//if it's freed then reused, no longer have to add one more
//		rs=0;
		fr=0;
	
		int a=0;
		while(s[a].add!=0){a++;}	
		s[a].add=array+minr+4;
		s[a].sz=s2;
		s[a].h=minr;
		void *ar = (void*)( (int*)(array+minr) );
		*( (int*)(array+minr) ) = s2;
		return array+minr+4;
	}



return (void*)-1;
}

void my_free(void *ptr) {
	int a=0;
	while(ptr!=s[a].add){a++;}
	f+=s[a].sz+4;
	int b=0;
	int h=s[a].h;
	if(mt!=3){
		for(b=0; b<(s[a].sz+4); b++){if(record[h+b]==1){record[h+b]=0;}}
	}
	else{
		record[h+1]=0;
		f=f-4;
		int j=128;
		int i=1;
		for(j=2;j*2<mem;j*=2){
			if(h==j){break;}			
		}
		if(j*2<mem&&record[j*2+1]!=1){record[j*2]==0;}//if its adjoint to another empty block, merge it
		if(record[j/2+1]!=1){record[j/2]=0;}
	}
	fr++;	
	s[a].add=NULL;
}

int num_free_bytes() {
return f;
}

int num_holes() {
	int i=0;
	int r=0;
if(mt!=3){
	for(i=0;i<mem;i++){
		//search for spaces
		while(record[i]==1){i++;}
		if(record[i]!=2&&record[i]!=1&&record[i-1]==1){r++;}
	}
}
else{
	int j=128;
	//base case
	if(record[1]!=1){r++;}
	for(j=2;j*2<=mem;j*=2){
		//search for spaces
		if(record[j+1]!=1&&record[j]==2){
			r++;	
			//takes at leat 2 to merge gaps
			if(fr>=1){while((j*2)<=mem&&record[j+1]!=1){j*=2;}}
		
		}
	}
	//cannot be 0
	if(r==0){r=1;rs=1;}
	if(rs==1&&fr>=1&&r<2){r++;}
	//if it was previously added one to make it not 0:
}
return r;
}
