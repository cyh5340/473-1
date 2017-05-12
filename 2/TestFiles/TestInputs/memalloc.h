
void setup(int malloc_type, int mem_size, void* start_of_memory);
void *my_malloc(int size);
void my_free(void *ptr);
int num_free_bytes();
int num_holes();
#define FIRST_FIT       0
#define BEST_FIT        1
#define WORST_FIT       2
#define BUDDY_SYSTEM    3
