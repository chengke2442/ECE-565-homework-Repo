#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

const int stride = 16;
int num_elements;
int num_traversals;
uint64_t *array;

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;
  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

#if 0
void init_array() {
  int i;
  for (i=0; i < num_elements; i++) {
    array[i*stride] = (i+1)*stride;
  }
  array[(num_elements-1)*stride] = 0;
}
#endif


void init_array() {
  int i, j;
  uint64_t tmp;

  for (i=0; i < num_elements; i++) {
    array[i*stride] = i*stride;
  }

  i = num_elements;
  while (i > 1) {
    i--;
    j = rand() % i;
    tmp = array[i*stride];
    array[i*stride] = array[j*stride];
    array[j*stride] = tmp;
  }
}


int main(int argc, char *argv[]) {
  int i;
  uint64_t index = 0;
  struct timespec start_time, end_time;
 
 
  num_elements = atoi(argv[1]);
  num_traversals = atoi(argv[2]);
  array = (uint64_t*)malloc(num_elements * sizeof(uint64_t) * stride);
  int temp1 = 0;
  int temp2 = 0;
  init_array();

  int total_iters = num_elements * num_traversals;
  
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  for (i=0; i<total_iters; i++) {
    for (int i = 0;i<num_elements;i++)
      {
	// a.
	//array[i] = i;

	// b.
	//array[i] = i;
	//temp1 = array[i];

	// c.
	temp1 = array[i];
	array[i] = i;
	temp2 = array[i];    
    
   
      }
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double elapsed_ns = calc_time(start_time, end_time);
  // printf("Time = %f\n", elapsed_ns);
  printf("bandwidth = %f GB/s\n", (((uint64_t)num_elements * (uint64_t)num_traversals * 8*3))/elapsed_ns);
  //printf("end index = %lu\n", index);

  free(array);
  return 0;
}
